/*
 * AspellChecker.cpp
 *
 *  Created on: 13-Jul-2019
 *      Author: manid2
 */

#include <AspellChecker.h>

namespace PFF {

AspellChecker::AspellChecker() :
    checker(0), config(0) {
  // aspell config options
  this->config = new_aspell_config();
  aspell_config_replace(this->config, "lang", "en_GB");
  aspell_config_replace(this->config, "ignore-case", "true");

  this->error = new_aspell_speller(this->config);

  if (aspell_error_number(this->error) != 0)
    puts(aspell_error_message(this->error));
  else
    this->checker = to_aspell_speller(this->error);
  //std::cout << "initialized aspell!" << std::endl;
}

AspellChecker::~AspellChecker() {
  if (this->config) {
    delete_aspell_config(this->config);
    this->config = 0;
  }
  if (this->checker) {
    delete_aspell_speller(this->checker);
    this->checker = 0;
  }
  /* NOTE: explicit delete of AspellCanHaveError* results in double delete
   * memory corruption seg fault. Hence commented.
   */
  /* if (this->error) {
    delete_aspell_can_have_error(this->error);
    this->error = 0;
  }*/
}

bool AspellChecker::run(char const* str, size_t size) {
  bool isCorrect = false;
  int correct = aspell_speller_check(this->checker, str, size);
  switch (correct) {
  case 1: /* success */
    isCorrect = true;
    break;
  case -1: /* some error! */
  case 0: /* the word is not in the dictionary! */
  default: /* do nothing! */
    ;
  }
  return isCorrect;
}

} /* namespace PFF */
