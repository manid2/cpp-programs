/*
 * main.cpp
 *
 *  Created on: 13-Jul-2019
 *      Author: Mani Kumar
 */

#include <CorrectSpell.h>

using namespace PFF;

// Client program which uses the application code
int execute(int argc, char **argv) {
  char str_default[] = "Hello";
  char *str = argc == 2 ? argv[1] : str_default;

  std::string s(str);
  CorrectTheSpelling cts(s);
  if (cts.checkSpelling())
    std::cout << "-> correct word: " << cts.getCorrectedWord() << std::endl;

  return 0;
}

int main(int argc, char **argv) {
   return execute(argc, argv);
} // end
