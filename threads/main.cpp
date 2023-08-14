/*
 * main.cpp
 *
 *  Created on: 25-Nov-2019
 *      Author: Mani Kumar
 */

#include <threads_cpp11.h>

using namespace PFF;

int execute(int argc, char **argv) {
  const int NUM_COUNT = 5;
  std::thread t1(PrintOdd, NUM_COUNT);
  std::thread t2(PrintEven, NUM_COUNT);
  t1.join();
  t2.join();
  return 0;
}

int main(int argc, char **argv) {
   return execute(argc, argv);
}
