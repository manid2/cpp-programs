/*
 * example_cpp_train_HOG.h
 *
 *  Created on: 30-Dec-2018
 *      Author: manid2
 */

#ifndef LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_CPP_TRAIN_HOG_H_
#define LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_CPP_TRAIN_HOG_H_

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/objdetect.hpp"

#include <iostream>
#include <time.h>

#define FFR_DATASET_PATH "FFR_DATASET_PATH"

namespace PFF {

class CTrainTestHOG {
 public:
  CTrainTestHOG();
  virtual ~CTrainTestHOG();

  void get_images(const cv::String & dirName, std::vector<cv::Mat> & imgList,
                  bool showImages);
  void get_cropped_faces(std::vector<cv::Mat> & imgList);
  void get_preprocessed_faces(std::vector<cv::Mat> & croppedFacesList);
  void get_ftfv_dataset(cv::String ft, cv::String fv);
  void get_ft_dataset(cv::String ft);

  void computeHOGs(const std::vector<cv::Mat> & imgList,
                   std::vector<cv::Mat> & imgHogList);
  void convert_to_ml(const std::vector<cv::Mat> & train_samples,
                     cv::Mat& trainData);

  int Run(void);

 private:
  void initLists(void);

 private:
  std::vector<cv::String> m_AgeList;
  std::vector<cv::String> m_EmotionList;
  std::vector<cv::String> m_GenderList;
  std::map<cv::String, std::vector<cv::String> > m_FeatureList;
};

static int execute(int argc, char **argv) {
  CTrainTestHOG ttHog;
  return ttHog.Run();
}

}  // namespace PFF

#endif /* LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_CPP_TRAIN_HOG_H_ */
