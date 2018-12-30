/*
 * example_cpp_train_HOG.cpp
 *
 *  Created on: 30-Dec-2018
 *      Author: manid2
 */

#include "example_cpp_train_HOG.h"

using namespace cv;
using namespace cv::ml;
using namespace std;

namespace PFF {

CTrainTestHOG::CTrainTestHOG() {
  this->initLists();
  this->m_faceCascade.load(
      cv::format("%s/haarcascade_frontalface_default.xml",
                 getenv(FFR_DATASET_PATH)));
  this->initSVM();
  this->isPredEnabled = false;
}

CTrainTestHOG::~CTrainTestHOG() {
  // TODO: write cleanup code here
}

void CTrainTestHOG::initLists(void) {
  m_AgeList = {"adult", "child", "old", "teen"};
  m_EmotionList = {"anger", "contempt", "happy", "neutral", "sad", "surprise"};
  m_GenderList = {"male", "female"};
  m_FeatureList = { {"Age", m_AgeList}, {"Emotion", m_EmotionList}, {"Gender", m_GenderList}};
}

void CTrainTestHOG::initSVM() {
  m_pSVM = SVM::create();
  /* Default values to train SVM */
  m_pSVM->setCoef0(0.0);
  m_pSVM->setDegree(3);
  m_pSVM->setTermCriteria(
      TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 1000, 1e-3));
  m_pSVM->setGamma(0);
  m_pSVM->setKernel(SVM::LINEAR);
  m_pSVM->setNu(0.5);
  m_pSVM->setP(0.1);  // for EPSILON_SVR, epsilon in loss function?
  m_pSVM->setC(0.01);  // From paper, soft classifier
  m_pSVM->setType(SVM::EPS_SVR);  // C_SVC; // EPSILON_SVR; // may be also NU_SVR; // do regression task
}

void CTrainTestHOG::get_images(const cv::String & dirName,
                               std::vector<cv::Mat> & imgList,
                               bool showImages) {

}

void CTrainTestHOG::get_cropped_faces(std::vector<cv::Mat> & imgList) {

}

void CTrainTestHOG::get_preprocessed_faces(
    std::vector<cv::Mat> & croppedFacesList) {

}

void CTrainTestHOG::get_ftfv_dataset(cv::String ft, cv::String fv,
                                     std::vector<cv::Mat>& trainData,
                                     std::vector<cv::Mat>& predData,
                                     std::vector<int>& trainLabels,
                                     std::vector<int>& predLabels) {
  cv::String folderName = cv::format("%s/%s/%s", getenv(FFR_DATASET_PATH),
                                     ft.c_str(), fv.c_str());
  std::vector<cv::Mat> imgList;
  this->get_images(folderName, imgList);
  this->get_cropped_faces(imgList);
  this->get_preprocessed_faces(imgList);

  /* std::random_shuffle(imgList.begin(), imgList.end());*/  // optional
  int trainPart = imgList.size() * 0.8;
  trainData.reserve(trainPart);
  predData.reserve(imgList.size() - trainPart);
  ft_t::iterator ft_iter = m_FeatureList.find(ft);
  fv_t::iterator fv_iter = ft_iter->second.find(fv);
  int label = std::distance(ft_iter->second.begin(), fv_iter);

  int i = 0;
  for (; i < trainPart; ++i) {
    trainData.push_back(imgList.at(i));
    trainLabels.push_back(label);
  }
  for (; i < imgList.size(); ++i) {
    predData.push_back(imgList.at(i));
    predLabels.push_back(label);
  }
}

void CTrainTestHOG::get_ft_dataset(cv::String ft,
                                   std::vector<cv::Mat>& trainData,
                                   std::vector<cv::Mat>& predData,
                                   std::vector<int>& trainLabels,
                                   std::vector<int>& predLabels) {

}

void CTrainTestHOG::computeHOGs(std::vector<cv::Mat> & imgHogList) {

}

void CTrainTestHOG::convert_to_ml(const std::vector<cv::Mat> & train_samples,
                                  cv::Mat& trainData) {

}

void CTrainTestHOG::get_prediction_accuracy(const std::vector<int>& pLables,
                                            const std::vector<int>& rLables,
                                            float& accuracy) {

}

int CTrainTestHOG::Run(int run_times) {
  for (auto ft : m_FeatureList) {
    std::vector<float> predictionAccuracyList;
    predictionAccuracyList.reserve(run_times);

    for (int run = 0; run < run_times; ++run) {
      vector<Mat> trainData, predData;
      vector<int> trainLabels, predLabels;
      // get pre-processed face data
      this->get_ft_dataset(ft.first, trainData, predData, trainLabels,
                           predLabels);
      // compute HOG for each pre-processed face
      this->computeHOGs(trainData);
      // convert HOG feature vectors to SVM data
      Mat ml_train_data;
      this->convert_to_ml(trainData, ml_train_data);
      // train svm
      cout << "***** Training SVM - begin *****";
      m_pSVM->train(ml_train_data, ROW_SAMPLE, trainLabels);
      cout << "***** Training SVM - end *****";

      // save the model
      cv::String svmModelFileName = cv::format("%s/cv4_svm_%s_model.yml",
                                               getenv(FFR_DATASET_PATH),
                                               ft.first.c_str());
      m_pSVM->save(svmModelFileName.c_str());

      // test the model
      // convert HOG feature vectors to SVM data
      Mat ml_pred_data;
      vector<int> resultLabels;
      this->convert_to_ml(predData, ml_pred_data);
      // test svm
      cout << "***** Testing SVM - begin *****";
      m_pSVM->predict(ml_pred_data, resultLabels);
      cout << "***** Testing SVM - end *****";

      // check the accuracy
      float accuracy = 0.0f;
      this->get_prediction_accuracy(predLabels, resultLabels, accuracy);
      cout << "Prediction accuracy: " << accuracy << endl;
      predictionAccuracyList.push_back(accuracy);
    }
    // print the mean accuracy
    float sum_of_accuracies = std::accumulate(predictionAccuracyList.begin(),
                                              predictionAccuracyList.end(),
                                              0.0);
    float mean_accuracy = sum_of_accuracies / predictionAccuracyList.size();
    cout << "Mean prediction accuracy: " << mean_accuracy << endl;
  }
  return 0;
}

}  // namespace PFF
