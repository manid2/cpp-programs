/*
 * threads_cpp11.h
 *
 *  Created on: 25-Nov-2019
 *      Author: Mani Kumar
 */

#ifndef _LEARNCPPCONCEPTS_THREADS_THREADS_CPP11_H_
#define _LEARNCPPCONCEPTS_THREADS_THREADS_CPP11_H_

// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <condition_variable>

using namespace std;

namespace PFF {

void PrintOdd(int num);
void PrintEven(int num);

} /* namespace PFF */

#endif /* _LEARNCPPCONCEPTS_THREADS_THREADS_CPP11_H_ */
