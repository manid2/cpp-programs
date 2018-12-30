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
#include <set>
#include <numeric>      // std::accumulate

#define FFR_DATASET_PATH "FFR_DATASET_PATH"

namespace PFF {

typedef std::set<cv::String> fv_t;
typedef std::map<cv::String, fv_t> ft_t;

class CTrainTestHOG {
 public:
  CTrainTestHOG();
  virtual ~CTrainTestHOG();

  void get_images(const cv::String & dirName, std::vector<cv::Mat> & imgList,
                  bool showImages = false);
  void get_cropped_faces(std::vector<cv::Mat> & imgList);
  void get_preprocessed_faces(std::vector<cv::Mat> & croppedFacesList);
  void get_ftfv_dataset(cv::String ft, cv::String fv,
                        std::vector<cv::Mat>& trainData,
                        std::vector<cv::Mat>& predData,
                        std::vector<int>& trainLabels,
                        std::vector<int>& predLabels);
  void get_ft_dataset(cv::String ft, std::vector<cv::Mat>& trainData,
                      std::vector<cv::Mat>& predData,
                      std::vector<int>& trainLabels,
                      std::vector<int>& predLabels);
  void computeHOGs(std::vector<cv::Mat> & imgHogList);
  void convert_to_ml(const std::vector<cv::Mat> & train_samples,
                     cv::Mat& trainData);
  void get_prediction_accuracy(const std::vector<int>& pLables,
                               const std::vector<int>& rLables,
                               float &accuracy);

  int Run(int run_times = 1);
  void enablePrediction(void) {
    isPredEnabled = true;
  }
  bool isPredictionEnabled(void) {
    return this->isPredEnabled;
  }

 private:
  void initLists(void);
  void initSVM(void);

 private:
  fv_t m_AgeList;
  fv_t m_EmotionList;
  fv_t m_GenderList;
  ft_t m_FeatureList;

  bool isPredEnabled;

  cv::HOGDescriptor m_HOG;
  cv::Ptr<cv::ml::SVM> m_pSVM;
  cv::CascadeClassifier m_faceCascade;
};

static int execute(int argc, char **argv) {
  CTrainTestHOG ttHog;
  return ttHog.Run(2);
}

}  // namespace PFF

#endif /* LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_CPP_TRAIN_HOG_H_ */
