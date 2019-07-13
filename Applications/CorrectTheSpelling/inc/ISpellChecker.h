/*
 * ISpellChecker.h
 *
 *  Created on: 13-Jul-2019
 *      Author: manid2
 */

#ifndef APPLICATIONS_CORRECTTHESPELLING_INC_ISPELLCHECKER_H_
#define APPLICATIONS_CORRECTTHESPELLING_INC_ISPELLCHECKER_H_

#include <cstddef>

namespace PFF {

/**
 * Interface for spell checkers
 */
class ISpellChecker {
 public:
  ISpellChecker(){};
  virtual ~ISpellChecker(){};

  virtual bool run(char const* str, size_t size)=0;
};

} /* namespace PFF */

#endif /* APPLICATIONS_CORRECTTHESPELLING_INC_ISPELLCHECKER_H_ */
