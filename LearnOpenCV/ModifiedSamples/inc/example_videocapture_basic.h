/*
 * example_videocapture_basic.h
 *
 *  Created on: 30-Dec-2018
 *      Author: manid2
 */

#ifndef LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_VIDEOCAPTURE_BASIC_H_
#define LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_VIDEOCAPTURE_BASIC_H_

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

namespace PFF {

int Run();

static int execute(int argc, char **argv) {
  return Run();
}

}  // namespace PFF

#endif /* LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_VIDEOCAPTURE_BASIC_H_ */
