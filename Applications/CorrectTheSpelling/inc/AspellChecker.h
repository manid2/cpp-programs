/*
 * AspellChecker.h
 *
 *  Created on: 13-Jul-2019
 *      Author: manid2
 */

#ifndef APPLICATIONS_CORRECTTHESPELLING_INC_ASPELLCHECKER_H_
#define APPLICATIONS_CORRECTTHESPELLING_INC_ASPELLCHECKER_H_

#include <ISpellChecker.h>
#include <aspell.h>  // for spell check
#include <iostream>

namespace PFF {

/**
 * Uses Gnu Aspell lib to check the spelling
 */
class AspellChecker: public ISpellChecker {
public:
  AspellChecker();
  virtual ~AspellChecker();

  bool run(char const* str, size_t size);

private:
  AspellConfig *config;
  AspellSpeller *checker;
  AspellCanHaveError *error;
};

} /* namespace PFF */

#endif /* APPLICATIONS_CORRECTTHESPELLING_INC_ASPELLCHECKER_H_ */
