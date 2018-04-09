//============================================================================
// Name        : main.cpp
// Author      : Mani Kumar
// Version     :
// Copyright   : Free2Copy
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "cjpegdecoder.h"

using namespace std;
using namespace mani_JPEG;

int main(int argc, char **argv) {
  cout << "!!! Mani Kumar testing libjpeg code - start !!!" << endl;

  CJpegDecoder decoder("lena.jpg", "lena.raw");
  decoder.decode();

  cout << "!!! Mani Kumar testing libjpeg code - stop !!!" << endl;
  return 0;
}
