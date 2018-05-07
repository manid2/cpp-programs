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

#include <map>

namespace PFF {

//! Resolutions
enum eImgRes {
  eResUnknown,
  eRes100dpi = 100,
  eRes150dpi = 150,
  eRes200dpi = 200,
  eRes300dpi = 300,
  eRes400dpi = 400,
  eRes600dpi = 600
};

//! Paper sizes
enum ePaperSize {
  ePSUnknown,
  eA3,
  eA4,
  eA5,
  eLT,
  eLD,
  eB4,
  eB5
};

//! image properties
struct stImgProps {
  eImgRes res;
  ePaperSize ps;

  stImgProps()
      : res(eResUnknown),
        ps(ePSUnknown) {
  }

  stImgProps(ePaperSize p, eImgRes r)
      : res(r),
        ps(p) {
  }

  bool operator <(const stImgProps& p) const {
    if (this->ps < p.ps && this->res < p.res)
      return true;
    else
      return false;
  }
};

//! image dimensions
struct stImgDims {
  int width;
  int height;

  stImgDims()
      : width(0),
        height(0) {
  }

  stImgDims(int w, int h)
      : width(w),
        height(h) {
  }
};

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
  //! map of img props to img dims
  std::map<stImgProps, stImgDims> img_props_dims_map;
};

using namespace cv;

static int execute(int argc, char **argv) {
  // pre-proc cmd line args
  printf(" execute enter\n");

  char wndname[] = "RND_Image";
  const int NUMBER = 100;
  const int DELAY = 0;
  int lineType = CV_AA;

  CImageGenerator imgGen;

#if 1
  imgGen.img_props_dims_map.insert(
      std::make_pair(stImgProps(eA4, eRes200dpi), stImgDims(1646, 2331)));

  int width = imgGen.img_props_dims_map[stImgProps(eA4, eRes200dpi)].width;
  int height = imgGen.img_props_dims_map[stImgProps(eA4, eRes200dpi)].height;
#else
  int width = 1000;
  int height = 700;
#endif

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

    cv::line(image, pt1, pt2, imgGen.getRandomColor(rng), rng.uniform(1, 10),
         lineType);

    //cv::imshow(wndname, image);
    //if (cv::waitKey(DELAY) >= 0)
    {
      cv::imwrite("rnd_img_1.jpg", image);
      break;
    }
  } while (0);

  printf(" execute exit\n");
  return 0;
}

} /* namespace PFF */

#endif /* APPS_IMAGEPROC_INC_CIMAGEGENERATOR_H_ */
