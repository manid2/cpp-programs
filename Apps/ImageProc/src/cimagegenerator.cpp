/*
 * cimagegenerator.cpp
 *
 *  Created on: 04-May-2018
 *      Author: Mani Kumar
 */

#include <cimagegenerator.h>

#include <iostream>

using namespace cv;

namespace PFF {

std::string enum2string(ePaperSize ps) {
  std::string str("ePSUnknown");

#define CASE(x)\
    case x:\
      str = #x;\
      break;

  switch (ps) {
    CASE(eA3)
    CASE(eA4)
    CASE(eA5)
    CASE(eLT)
    CASE(eLD)
    CASE(eB4)
    CASE(eB5)
    default:
      break;
  }
#undef CASE

  return str.substr(1);
}

std::string enum2string(eImgRes res) {
  std::string str("eResUnknown");

#define CASE(x)\
    case x:\
      str = std::to_string(x);\
      break;

  switch (res) {
    CASE(eRes100dpi)
    CASE(eRes150dpi)
    CASE(eRes200dpi)
    CASE(eRes300dpi)
    CASE(eRes400dpi)
    CASE(eRes600dpi)
    default:
      break;
  }
#undef CASE

  return str;
}

CImageGenerator::CImageGenerator()
    : paperSize(ePSUnknown),
      rsln(eResUnknown) {
}

CImageGenerator::~CImageGenerator() {
}

Scalar CImageGenerator::getRandomColor(RNG& rng) {
  int icolor = (unsigned) rng;
  return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

int execute(int argc, char **argv) {
  // pre-proc cmd line args
  printf(" execute enter\n");

  char wndname[] = "RND_Image";
  const int NUMBER = 100;
  const int DELAY = 0;
  int lineType = CV_AA;

  std::string var_name(enum2string(eA4));
  std::cout << var_name << std::endl;

  var_name += "_" + enum2string(eRes200dpi) + "DPI_" + "W";
  std::cout << var_name << std::endl;

#if 0
  CImageGenerator imgGen;

#if 0
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
  }while (0);
#endif

  printf(" execute exit\n");
  return 0;
}

} /* namespace LilPDF */
