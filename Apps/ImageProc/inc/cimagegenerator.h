/*
 * cimagegenerator.h
 *
 *  Created on: 04-May-2018
 *      Author: Mani Kumar
 */

#ifndef APPS_IMAGEPROC_INC_CIMAGEGENERATOR_H_
#define APPS_IMAGEPROC_INC_CIMAGEGENERATOR_H_

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace PFF {

/*
 * Generates a random image for testing
 */
class CImageGenerator {
 public:
  CImageGenerator();
  virtual ~CImageGenerator();

 public:
  cv::Scalar getRandomColor(cv::RNG& rng);
  void drawLine(void);

 public:
  cv::Mat m_image;
};

using namespace cv;

static int execute(int argc, char **argv) {
  // pre-proc cmd line args
  printf(" execute enter\n");

  char wndname[] = "RND_Image";
  const int NUMBER = 100;
  const int DELAY = 0;

  int lineType = CV_AA;  // change it to 8 to see non-antialiased graphics
  int width = 1000, height = 700;
  int x1 = -width / 2;
  int x2 = width * 3 / 2;
  int y1 = -height / 2;
  int y2 = height * 3 / 2;
  cv::RNG rng(0xFFFFFFFF);

  cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);
  do {

    Point pt1, pt2;
    pt1.x = rng.uniform(x1, x2);
    pt1.y = rng.uniform(y1, y2);
    pt2.x = rng.uniform(x1, x2);
    pt2.y = rng.uniform(y1, y2);

    CImageGenerator imgGen;
    cv::line(image, pt1, pt2, imgGen.getRandomColor(rng), rng.uniform(1, 10),
         lineType);

    cv::imshow(wndname, image);
    if (cv::waitKey(DELAY) >= 0) {
      cv::imwrite("rnd_img_1.jpg", image);
      break;
    }
  } while (0);

  printf(" execute exit\n");
  return 0;
}

} /* namespace PFF */

#endif /* APPS_IMAGEPROC_INC_CIMAGEGENERATOR_H_ */
