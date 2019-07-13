/*
 * correct_spell.h
 *
 *  Created on: 13-Jul-2019
 *      Author: Mani Kumar
 */

#ifndef APPLICATIONS_CORRECTTHESPELLING_INC_CORRECTSPELL_H_
#define APPLICATIONS_CORRECTTHESPELLING_INC_CORRECTSPELL_H_

#include <ISpellChecker.h>
#include <SpellCheckerFactory.h>

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>  // std::next_permutation

namespace PFF {

/**
 * Application code:
 * This class encapsulates the data and operations required to verify the
 * correct spelling of a given word in English.
 *
 * NOTE:
 * This class is made to be very simple for use in my blogs.
 * Hence I have ignored the spell checker's configurations and options.
 */
class CorrectTheSpelling {
public:
  // c'tor
  CorrectTheSpelling(void);
  CorrectTheSpelling(std::string const& str);
  CorrectTheSpelling(char const *str);
  CorrectTheSpelling(char const *str, size_t size);

  // d'tor
  virtual ~CorrectTheSpelling();

  // API
  //! check spelling
  bool checkSpelling(void);
  bool checkSpelling(std::string const& str);
  bool checkSpelling(char const *str);
  bool checkSpelling(char const *str, size_t size);

  // getters
  std::string getCorrectedWord(void) const { return this->correctWord; }

private:
  std::string word;
  std::string correctWord;
  std::shared_ptr<ISpellChecker> spellChecker;
};

// Client program which uses the application code
static int execute(int argc, char **argv) {
  char str_default[] = "Hello";
  char *str = argc == 2 ? argv[1] : str_default;

  std::string s(str);
  CorrectTheSpelling cts(s);
  if (cts.checkSpelling())
    std::cout << "-> correct word: " << cts.getCorrectedWord() << std::endl;

  return 0;
}

}  // namespace PFF

#endif /* CORRECTTHESPELLING_INC_CORRECT_SPELL_H_ */
