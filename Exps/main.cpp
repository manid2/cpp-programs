/*
 * main.cpp
 *
 *  Created on: 09-May-2018
 *      Author: Mani Kumar
 */

#include <lpdfcommon.h>

#include <cstdio>

#ifdef LPDF_BUILD_AS_EXE

using namespace LilPDF;

int main(int argc, char **argv) {
  return execute(argc, argv);
}  // end

#endif // LPDF_BUILD_AS_EXE
