/*
 * competitiveprograms.h
 *
 *  Created on: 31-Jul-2018
 *      Author: mani
 */

#ifndef EXPS_INC_COMPETITIVEPROGRAMS_H_
#define EXPS_INC_COMPETITIVEPROGRAMS_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

namespace PFF {

class CompetitivePrograms {
 public:
  CompetitivePrograms();
  virtual ~CompetitivePrograms();

  void pipe2commaSeparatedValues(void);
};

} /* namespace PFF */

static int execute(int a, char **v) {
  PFF::CompetitivePrograms cp;
  cp.pipe2commaSeparatedValues();
  return 0;
}

#endif /* EXPS_INC_COMPETITIVEPROGRAMS_H_ */
