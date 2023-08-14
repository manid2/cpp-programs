/*
 * main.cpp
 *
 *  Created on: 25-Nov-2019
 *      Author: Mani Kumar
 */

#include <vtable.h>

using namespace PFF;

int execute(int argc, char **argv) {
  RuntimeBehaviour rb;
  rb.runtimePolymorphismDemo();
  return 0;
}

int main(int argc, char **argv) {
   return execute(argc, argv);
} // end
