/*
 * cskewcorrector.cpp
 *
 *  Created on: 19-Jul-2018
 *      Author: Mani Kumar
 */

#include <cskewcorrector.h>
#include <vector>
#include <iostream>

namespace PFF {

CSkewCorrector::CSkewCorrector(const char* fileName) {
  m_fileName = fileName;
}

CSkewCorrector::CSkewCorrector(std::string fileName) {
  m_fileName = fileName;
}

CSkewCorrector::~CSkewCorrector() {
}

/*
 * Code for this function is taken from
 * http://felix.abecassis.me/2011/09/opencv-detect-skew-angle/
 */
void CSkewCorrector::compute_skew() {
  std::cout << "[debug_log], m_fileName = " << m_fileName << std::endl;

  // Load in grayscale.
  cv::Mat src = cv::imread(m_fileName.c_str(), 0);

  if (!src.data) {
    std::cout << (" No image data \n ");
    return;
  }

  cv::Size size = src.size();
  std::cout << "[debug_log], mat size = " << size << std::endl;

  // Make objects white and the background black,
  cv::bitwise_not(src, src);

  std::vector<cv::Vec4i> lines;
  cv::HoughLinesP(src, lines, 1, CV_PI / 180, 100, size.width / 2.f, 20);
  std::cout << "[debug_log], after HoughLinesP()" << std::endl;

  cv::Mat disp_lines(size, CV_8UC1, cv::Scalar(0, 0, 0));
  double angle = 0.;
  unsigned nb_lines = lines.size();
  for (unsigned i = 0; i < nb_lines; ++i) {
    cv::line(disp_lines, cv::Point(lines[i][0], lines[i][1]),
             cv::Point(lines[i][2], lines[i][3]), cv::Scalar(255, 0, 0));
    angle += atan2((double) lines[i][3] - lines[i][1],
                   (double) lines[i][2] - lines[i][0]);
  }
  angle /= nb_lines;  // mean angle, in radians.
  cv::imwrite("out_img.jpg", disp_lines);
  std::cout << "[debug_log], after imwrite()" << std::endl;

  std::cout << "File " << m_fileName << ": " << angle * 180 / CV_PI
            << std::endl;
}

int execute(int argc, char **argv) {
  if (argc == 2) {
    CSkewCorrector skc(argv[1]);
    skc.compute_skew();
  } else {
    CSkewCorrector skc("1.jpg");
    skc.compute_skew();
  }
  return 0;
}

} /* namespace PFF */
