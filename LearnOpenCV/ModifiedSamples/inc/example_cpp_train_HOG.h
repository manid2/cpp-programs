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

#define FFR_DATA_PATH "FFR_DATA_PATH"

namespace PFF {

// TODO: should be an enum, to handle different errors differently
typedef int ErrorCode;

typedef std::set<cv::String> fv_t;
typedef std::map<cv::String, fv_t> ft_t;

// TODO: REFACTOR - remove duplicate code and reorganize
//-- test single image flow
//! Feature types
enum Feature {
  Feature_Undefined = -1,
  Age = 0,
  Emotion,
  Gender
};

typedef std::set<PFF::Feature> FeaturesSet;

//! to avoid feature-result mismatch issue, we use a pair
typedef std::pair<PFF::Feature, std::string> ResultPair;
//! set of feature-result per face
typedef std::set<ResultPair> ResultsPairSet;
//! results per image, equals no of faces in the image
typedef std::vector<ResultsPairSet> ResultsVec;

#define TO_STR(e) #e

static std::string enum2str(Feature f) {
  std::string en;

#define CASE(fe)\
  case fe:\
     en = TO_STR(fe);\
     break;

  switch (f) {
    CASE(Age)
    CASE(Emotion)
    CASE(Gender)
  }
#undef CASE
//#undef TO_STR

  return en;
}

class CTrainTestHOG {
 public:
  const std::string _className;
  CTrainTestHOG();
  virtual ~CTrainTestHOG();

  ErrorCode get_images(const cv::String & dirName,
                       std::vector<cv::Mat> & imgList, bool showImages = false);
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
  void enablePrediction(void) /*const*/{
    this->isPredict = true;
  }
  void saveModel(void) /*const*/{
    this->isSaveModel = true;
  }

  //-- test models flow
  bool isTestModels;
  bool isShowImage;
  std::string m_inFile;
  std::string m_outFile;

  FeaturesSet m_features;
  int m_fontFace;
  double m_fontScale;
  cv::Scalar m_fontColor;
  int m_lineType;

  ResultsVec m_resultsVec;
  std::vector<cv::Ptr<cv::ml::StatModel> > m_pSVMModels;

  ErrorCode testModelsOnSingleImage(void);
  ErrorCode readImageFromFile(const std::string& fileName, cv::Mat& img_i,
                              cv::Mat& img_o);
  ErrorCode readImage(cv::Mat& img);
  ErrorCode detectFace(cv::Mat& frame, std::vector<cv::Rect>& faces,
                       cv::Mat& frame_gray);
  ErrorCode recognizeFeatures(const FeaturesSet& features, ResultsVec& results,
                              cv::Mat& frame_gray,
                              std::vector<cv::Rect>& faces);
  ErrorCode drawResults(cv::Mat& frame, const std::vector<cv::Rect>& faces,
                        const FeaturesSet& features, const ResultsVec& results);
  ErrorCode computeHOG(const cv::Mat& img, cv::Mat& hogMat);
  ErrorCode convertToML(const cv::Mat& hogMat, cv::Mat& mlMat);

 private:
  void initLists(void);
  void initSVM(void);

  ErrorCode loadSVM(const FFR::String& _fn, int i = 0);

 private:
  fv_t m_AgeList;
  fv_t m_EmotionList;
  fv_t m_GenderList;
  ft_t m_FeatureList;

  //-- train models flow
  bool isPredict;
  bool isSaveModel;

  cv::Size m_hogImgSize;
  //cv::HOGDescriptor m_HOG;
  cv::Ptr<cv::ml::SVM> m_pSVM;
  cv::CascadeClassifier m_faceCascade;
};

static void help() {
  std::cout
      << "\n"
      << "This program demonstrates how to train, save, and predict n-class classifier SVM models using HOG features.\n"
      << "\n"
      << "NOTE: The dataset folder structure is arranged as described in my blog for Data Organization\n"
      << "Blog link: https://manid2.github.io/tutorials/how-to-train-opencv-4-svm/#data-organization\n"
      << "\n"
      << "Usage:\n"
      << "\n"
      << "export FFR_DATASET_PATH=<path_to_ffr_dataset>\n"
      << "\n"
      << "To train the SVM models"
      << "\n"
      << "\t./train_hog --train --predict --save"
      << "\n"
      << "\n"
      << "To test the SVM models on a single image"
      << "\n"
      << "\t./train_hog --test --in=<path_to_image> --out=<path_to_output> --show"
      << "\n" << "\n" << "Using OpenCV version " << CV_VERSION << "\n"
      << std::endl;
}

static int execute(int argc, char **argv) {
  cv::CommandLineParser parser(argc, argv, "{help h||}"
                               "{train||}"
                               "{predict||}"
                               "{save||}"
                               "{test||}"
                               "{in||}"
                               "{out||}"
                               "{show||}");
  CTrainTestHOG ttHog;
  //-- if train models flow
  if (parser.has("train")) {
    if (parser.has("predict"))
      ttHog.enablePrediction();
    if (parser.has("save"))
      ttHog.saveModel();
  }
  //-- if test models on a single image flow
  else if (parser.has("test")) {
    ttHog.isTestModels = true;
    std::string inFile(parser.get<std::string>("in"));
    if (inFile.empty()) {
      std::cout << "!!! enter input image file path !!!\n";
      return 0;
    }
    ttHog.m_inFile = inFile;
    std::string outFile(parser.get<std::string>("out"));
    if (outFile.empty()) {
      outFile = inFile;
      outFile.insert(0, "out_");
      std::cout << "outFile path is empty using default file path=[" << outFile
                << "]\n";
    }
    ttHog.m_outFile = outFile;
    ttHog.isShowImage = parser.has("show") ? true : false;
  } else /*(parser.has("help"))*/{
    PFF::help();
    return 0;
  }

  return ttHog.Run(1);
}

}  // namespace PFF

#endif /* LEARNOPENCV_MODIFIEDSAMPLES_INC_EXAMPLE_CPP_TRAIN_HOG_H_ */
