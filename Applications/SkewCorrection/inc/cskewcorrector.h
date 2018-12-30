/*
 * cskewcorrector.h
 *
 *  Created on: 19-Jul-2018
 *      Author: Mani Kumar
 */

#ifndef OPENCV_STUFF_INC_CSKEWCORRECTOR_H_
#define OPENCV_STUFF_INC_CSKEWCORRECTOR_H_

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace PFF {

/*
 * Class to detect and correct the skew in an image.
 */
class CSkewCorrector {
 public:
  CSkewCorrector(const char*);
  CSkewCorrector(std::string);
  virtual ~CSkewCorrector();
  void compute_skew(void);

 public:
  cv::Mat m_img;
  std::string m_fileName;
};

extern int execute(int argc, char **argv);

} /* namespace PFF */

#endif /* OPENCV_STUFF_INC_CSKEWCORRECTOR_H_ */
