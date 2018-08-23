/*
 * threads_cpp11.cpp
 *
 *  Created on: 23-Aug-2018
 *      Author: mani
 */

#include <threads_cpp11.h>

namespace PFF {

/*threads_cpp11::threads_cpp11() {
 // TODO Auto-generated constructor stub

 }

 threads_cpp11::~threads_cpp11() {
 // TODO Auto-generated destructor stub
 }*/

std::mutex mu;
std::condition_variable cond;

int count = 1;

void PrintOdd(int num) {
  for (int i = 0; i < num; i++) {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, []() {return (count%2 == 1);});
    cout << "Thread_A: " << count << endl;
    count++;
    locker.unlock();
    cond.notify_all();
  }
}

void PrintEven(int num) {
  for (int i = 0; i < num; i++) {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, []() {return (count%2 == 0);});
    cout << "Thread_B: " << count << endl;
    count++;
    locker.unlock();
    cond.notify_all();
  }
}

} /* namespace PFF */
