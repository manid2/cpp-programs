/*
 * correct_spell.cpp
 *
 *  Created on: 13-Jul-2019
 *      Author: Mani Kumar
 */

#include <CorrectSpell.h>

using namespace std;

namespace PFF {

CorrectTheSpelling::CorrectTheSpelling(void) {
}

CorrectTheSpelling::CorrectTheSpelling(string const& str) :
    word(str) {
}

CorrectTheSpelling::CorrectTheSpelling(char const *str) :
    word(str) {
}

CorrectTheSpelling::CorrectTheSpelling(char const *str, size_t n) :
    word(str, n) {
}

CorrectTheSpelling::~CorrectTheSpelling() {
}

bool CorrectTheSpelling::checkSpelling(void) {
  return this->checkSpelling(this->word.c_str(), this->word.size());
}

bool CorrectTheSpelling::checkSpelling(std::string const& str) {
  return this->checkSpelling(str.c_str(), str.size());
}

bool CorrectTheSpelling::checkSpelling(char const *str) {
  size_t s = 0;
  for (; str[s]; ++s) {
  }
  return this->checkSpelling(str, s);
}

bool CorrectTheSpelling::checkSpelling(char const *str, size_t size) {
  bool isCorrect = false;

  // check if input is ok
  if (!str || size > 10) {
    std::cerr << "input error: str=[" << hex << str << "], size=[" << dec
        << size << "]!" << std::endl;
    isCorrect = false;
    return isCorrect;
  }

  // initialize spell checker
  SpellCheckerFactory f;
  this->spellChecker = f.getSpellChecker();

  // execute spell checker
  std::string s(str, size);
  // sort string into ascending order,
  // so we get all the permutations using std::next_permutation
  std::sort(s.begin(), s.end());
  do {
    //std::cout << " " << s << endl;
    if (this->spellChecker->run(s.c_str(), s.size())) {
      this->correctWord = s;
      isCorrect = true;
      //std::cout << "-> correct word: " << s << std::endl;
      break;
    }
  } while (std::next_permutation(s.begin(), s.end()));
  return isCorrect;
}

}  // namespace PFF
