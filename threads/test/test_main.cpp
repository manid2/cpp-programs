/*
 * test_main.cpp
 *
 *  Created on: 07-May-2021
 *      Author: Mani Kumar
 */

#include <threads_cpp11.h>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
//#include <gcov.h>

using namespace PFF;

int execute(int argc, char **argv) {
  const int NUM_COUNT = 5;
  std::thread t1(PrintOdd, NUM_COUNT);
  std::thread t2(PrintEven, NUM_COUNT);
  t1.join();
  t2.join();
  return 0;
}

// extern gcov flush
extern "C" void __gcov_flush(void);

/*
 * handle signal and exit cleanly
 */
void sig_handler(int sig) {
  switch(sig){
    case SIGINT:
    case SIGTERM:
    case SIGUSR1:
      printf("received signal=[%d]\n", sig);
      break;
    default:
      printf("received unexpected signal=[%d]!!!\n", sig);
      return;
  }
  printf("dumping gcov data files i.e. .gcda files\n");
  __gcov_flush();
  printf("exiting process\n");
  _exit(sig);
}

/*
 * test code main func
 *
 * created specifically to add signal handlers and dump gcov data files
 * as gcov generates data files only on process exit.
 */
int main(int argc, char **argv) {
   int ret = 0; // TODO: use macros
   signal(SIGINT, sig_handler); // Register SIGINT
   signal(SIGTERM, sig_handler); // Register SIGTERM
   signal(SIGUSR1, sig_handler); // Register SIGUSR1
   ret = execute(argc, argv);
   return ret;
}
