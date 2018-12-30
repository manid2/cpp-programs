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

void CTrainTestHOG::get_images(const cv::String & dirName,
                               std::vector<cv::Mat> & imgList,
                               bool showImages) {

}

void CTrainTestHOG::get_cropped_faces(std::vector<cv::Mat> & imgList) {

}

void CTrainTestHOG::get_preprocessed_faces(
    std::vector<cv::Mat> & croppedFacesList) {

}

void CTrainTestHOG::get_ftfv_dataset(cv::String ft, cv::String fv) {

}

void CTrainTestHOG::get_ft_dataset(cv::String ft) {

}

void CTrainTestHOG::computeHOGs(const std::vector<cv::Mat> & imgList,
                                std::vector<cv::Mat> & imgHogList) {

}

void CTrainTestHOG::convert_to_ml(const std::vector<cv::Mat> & train_samples,
                                  cv::Mat& trainData) {

}

int CTrainTestHOG::Run() {
  return 0;
}

}  // namespace PFF
