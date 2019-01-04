/*
 * example_cpp_train_HOG.h
 *
 *  Created on: 30-Dec-2018
 *      Author: manid2
 */

#ifndef LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_CPP_TRAIN_HOG_H_
#define LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_CPP_TRAIN_HOG_H_

#include "logger.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/objdetect.hpp"

#include <iostream>
#include <set>
#include <numeric>      // std::accumulate

#define FFR_DATASET_PATH "FFR_DATASET_PATH"

namespace PFF {

// TODO: should be an enum, to handle different errors differently
typedef int ErrorCode;

typedef std::set<cv::String> fv_t;
typedef std::map<cv::String, fv_t> ft_t;

class CTrainTestHOG {
 public:
  const std::string _className;
  CTrainTestHOG();
  virtual ~CTrainTestHOG();

  ErrorCode get_images(const cv::String & dirName, std::vector<cv::Mat> & imgList,
                  bool showImages = false);
  ErrorCode get_cropped_faces(std::vector<cv::Mat> & imgList);
  ErrorCode get_preprocessed_faces(std::vector<cv::Mat> & croppedFacesList);
  ErrorCode get_ftfv_dataset(cv::String ft, cv::String fv,
                        std::vector<cv::Mat>& trainData,
                        std::vector<cv::Mat>& predData,
                        std::vector<int>& trainLabels,
                        std::vector<int>& predLabels);
  ErrorCode get_ft_dataset(cv::String ft, std::vector<cv::Mat>& trainData,
                      std::vector<cv::Mat>& predData,
                      std::vector<int>& trainLabels,
                      std::vector<int>& predLabels);
  ErrorCode computeHOGs(std::vector<cv::Mat> & imgHogList);
  ErrorCode convert_to_ml(const std::vector<cv::Mat> & train_samples,
                     cv::Mat& trainData);
  ErrorCode get_prediction_accuracy(const std::vector<int>& pLables,
                               const std::vector<int>& rLables,
                               float &accuracy);

  /* entry point into this class operations */
  int Run(int run_times = 1);
  void enablePrediction(void) /*const*/ {
    this->isPredict = true;
  }
  void saveModel(void) /*const*/ {
    this->isSaveModel = true;
  }

 private:
  void initLists(void);
  void initSVM(void);

 private:
  fv_t m_AgeList;
  fv_t m_EmotionList;
  fv_t m_GenderList;
  ft_t m_FeatureList;

  bool isPredict;
  bool isSaveModel;

  cv::Size m_hogImgSize;
  //cv::HOGDescriptor m_HOG;
  cv::Ptr<cv::ml::SVM> m_pSVM;
  cv::CascadeClassifier m_faceCascade;
};

static int execute(int argc, char **argv) {
  CTrainTestHOG ttHog;
  ttHog.enablePrediction();
  ttHog.saveModel();
  return ttHog.Run(1);
}

}  // namespace PFF

#endif /* LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_CPP_TRAIN_HOG_H_ */
