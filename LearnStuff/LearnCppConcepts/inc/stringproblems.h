/*
 * stringproblems.h
 *
 *  Created on: 25-Aug-2018
 *      Author: mani
 */

#ifndef LEARNSTUFF_LEARNCPPCONCEPTS_INC_STRINGPROBLEMS_H_
#define LEARNSTUFF_LEARNCPPCONCEPTS_INC_STRINGPROBLEMS_H_

#include <iostream>

#include <string>
#include <string.h>

namespace PFF {

/*
 class StringProblems {
 public:
  StringProblems();
  virtual ~StringProblems();
 };
 */

typedef std::string string;

string find_n_replace(string str_i, string str_f, string str_r);
const char* find_n_replace(const char* str_i, const char* str_f,
                           const char* str_r);

//--
void str_append(const char* src, const char** dst, size_t len, size_t init_len);
long str_find(const char* str_i, const char* str_f, size_t init_len);

static int execute(int a, char** v) {
  string str_i("I am happy, am, am, am.");
  string str_f("am");
  string str_r("dasba");

  std::cout << "in : [" << str_i << "]" << std::endl;
  string str_o(find_n_replace(str_i, str_f, str_r));
  std::cout << "out: [" << str_o << "]" << std::endl;
}

} /* namespace PFF */

#endif /* LEARNSTUFF_LEARNCPPCONCEPTS_INC_STRINGPROBLEMS_H_ */
