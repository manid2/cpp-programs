/*
 * cimagegenerator.cpp
 *
 *  Created on: 04-May-2018
 *      Author: Mani Kumar
 */

#include <cimagegenerator.h>

using namespace cv;

namespace PFF {

CImageGenerator::CImageGenerator() {
  // TODO Auto-generated constructor stub

}

CImageGenerator::~CImageGenerator() {
  // TODO Auto-generated destructor stub
}

Scalar CImageGenerator::getRandomColor(RNG& rng) {
  int icolor = (unsigned) rng;
  return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

} /* namespace LilPDF */
