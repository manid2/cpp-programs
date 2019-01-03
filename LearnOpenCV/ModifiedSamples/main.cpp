/*
 * main.cpp
 *
 *  Created on: 20-Mar-2018
 *      Author: Mani Kumar
 */

//#include <example_videocapture_basic.h>
#include <example_cpp_train_HOG.h>

using namespace std;
using namespace PFF;

using namespace FFR; // for debug info

int main(int argc, char **argv)
{
  std::string _className(FUNC_NAME);
  DEBUGLF("enter\n");
  int ret = 0;
  ret = execute(argc, argv);
  DEBUGLF("exit\n");
  return ret;
}
