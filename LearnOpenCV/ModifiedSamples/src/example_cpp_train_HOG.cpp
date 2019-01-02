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
  vector<String> files;
  cv::glob(dirName, files);
  for (size_t i = 0; i < files.size(); ++i) {
    Mat img = cv::imread(files[i], cv::IMREAD_GRAYSCALE);  // load the image in gray
    if (img.empty())            // invalid image, skip it.
    {
      cout << files[i] << " is invalid!" << endl;
      continue;
    }

    /*if (showImages) {
     imshow("image", img);
     waitKey(1);
     }*/
    imgList.push_back(img);
  }
}

void CTrainTestHOG::get_cropped_faces(std::vector<cv::Mat> & imgList) {
  std::vector<cv::Mat> cropped_faces;
  //-- for each img
  for (auto img : imgList) {
    cv::equalizeHist(img, img);
    std::vector<Rect> faces_r;
    m_faceCascade.detectMultiScale(img, faces_r);
    //-- for each face in img
    for (size_t i = 0; i < faces_r.size(); ++i) {
      cropped_faces.push_back(img(faces_r[i]));
    }
  }
  imgList.swap(cropped_faces);
}

void CTrainTestHOG::get_preprocessed_faces(
    std::vector<cv::Mat> & croppedFacesList) {
  for (auto cFace : croppedFacesList) {
    cv::resize(cFace, cFace, cv::Size(50, 50));
  }
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

  std::random_shuffle(imgList.begin(), imgList.end());  // optional
  int trainPart = imgList.size() * 0.8;  // 80% for training
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
  fv_t &featureValueList = m_FeatureList.find(ft)->second;
  for (auto fv : featureValueList) {
    std::vector<cv::Mat> _trainData;
    std::vector<cv::Mat> _predData;
    std::vector<int> _trainLabels;
    std::vector<int> _predLabels;
    this->get_ftfv_dataset(ft, fv, _trainData, _predData, _trainLabels,
                           _predLabels);
    trainData.insert(trainData.end(), _trainData.begin(), _trainData.end());
    predData.insert(predData.end(), _predData.begin(), _predData.end());
    trainLabels.insert(trainLabels.end(), _trainLabels.begin(),
                       _trainLabels.end());
    predLabels.insert(predLabels.end(), _predLabels.begin(), _predLabels.end());
  }
}

void CTrainTestHOG::computeHOGs(std::vector<cv::Mat> & imgHogList) {
  vector<Mat> hogMats;
  vector<float> descriptors;
  for (auto img : imgHogList) {
    m_HOG.compute(img, descriptors);
    hogMats.push_back(Mat(descriptors).clone());
  }
  imgHogList.swap(hogMats);
}

/*
* Convert training/testing set to be used by OpenCV Machine Learning algorithms.
* TrainData is a matrix of size (#samples x max(#cols,#rows) per samples), in 32FC1.
* Transposition of samples are made if needed.
*/
void CTrainTestHOG::convert_to_ml(const std::vector<cv::Mat> & train_samples,
                                  cv::Mat& trainData) {
  //-- Convert hog features data to ml data
  const int rows = (int) train_samples.size();
  const int cols = (int) std::max(train_samples[0].cols, train_samples[0].rows);
  Mat tmp(1, cols, CV_32FC1);  //< used for transposition if needed
  trainData = Mat(rows, cols, CV_32FC1);

  for (size_t i = 0; i < train_samples.size(); ++i) {
    CV_Assert(train_samples[i].cols == 1 || train_samples[i].rows == 1);
    if (train_samples[i].cols == 1) {
      cv::transpose(train_samples[i], tmp);
      tmp.copyTo(trainData.row((int) i));
    } else if (train_samples[i].rows == 1) {
      train_samples[i].copyTo(trainData.row((int) i));
    }
  }
}

void CTrainTestHOG::get_prediction_accuracy(const std::vector<int>& pLables,
                                            const std::vector<int>& rLables,
                                            float& accuracy) {
  // pred labels and result labels must be of same size
  int misMatchCount = 0;
  for (size_t i = 0; i < rLables.size(); ++i) {
    if (rLables.at(i) != pLables.at(i))
      misMatchCount++;
  }
  int correct = rLables.size() - misMatchCount;
  accuracy = correct * 100.0f / rLables.size();
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
      // compute HOG for each pre-processed face
      this->computeHOGs(predData);
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
