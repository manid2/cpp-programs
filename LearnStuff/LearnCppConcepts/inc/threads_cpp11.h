/*
 * threads_cpp11.h
 *
 *  Created on: 23-Aug-2018
 *      Author: mani
 */

#ifndef LEARNSTUFF_LEARNCPPCONCEPTS_INC_THREADS_CPP11_H_
#define LEARNSTUFF_LEARNCPPCONCEPTS_INC_THREADS_CPP11_H_

// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <condition_variable>

using namespace std;

namespace PFF {

/*class threads_cpp11 {
 public:
 threads_cpp11();
 virtual ~threads_cpp11();
 };*/

void PrintOdd(int num);
void PrintEven(int num);

#define n 5 // to avoid multiple definition error

static int execute(int argc, char **argv) {
  std::thread t1(PrintOdd, n);
  std::thread t2(PrintEven, n);
  t1.join();
  t2.join();
  return 0;
}

} /* namespace PFF */

#endif /* LEARNSTUFF_LEARNCPPCONCEPTS_INC_THREADS_CPP11_H_ */
