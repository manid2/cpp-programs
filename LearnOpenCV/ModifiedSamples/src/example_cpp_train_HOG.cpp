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

using namespace FFR;

#ifndef ENABLE_DEBUG_MODE
# define ENABLE_DEBUG_MODE
#endif // ENABLE_DEBUG_MODE

namespace PFF {

CTrainTestHOG::CTrainTestHOG()
    : _className(FUNC_NAME) {
  DEBUGLF("enter\n");
  this->initLists();
  this->m_faceCascade.load(
      cv::format("%s/haarcascade_frontalface_default.xml",
                 getenv(FFR_DATASET_PATH)));
  this->initSVM();
  DEBUGLF("exit\n");
}

CTrainTestHOG::~CTrainTestHOG() {
  // TODO: write cleanup code here
}

void CTrainTestHOG::initLists(void) {
  DEBUGLF("enter\n");
#ifdef ENABLE_DEBUG_MODE
  //m_AgeList = {"adult", "child", "old", "teen"};
  //m_EmotionList = {"anger", "contempt", "happy", "neutral", "sad", "surprise"};
  m_GenderList = {"male", "female"};
  m_FeatureList = { /*{"Age", m_AgeList}, {"Emotion", m_EmotionList},*/{"Gender", m_GenderList}};
#else
  m_AgeList = {"adult", "child", "old", "teen"};
  m_EmotionList = {"anger", "contempt", "happy", "neutral", "sad", "surprise"};
  m_GenderList = {"male", "female"};
  m_FeatureList = { {"Age", m_AgeList}, {"Emotion", m_EmotionList}, {"Gender", m_GenderList}};
#endif
  DEBUGLF("exit\n");
}

void CTrainTestHOG::initSVM() {
  DEBUGLF("enter\n");
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
  m_pSVM->setType(SVM::C_SVC);  // C_SVC; // EPSILON_SVR; // may be also NU_SVR; // do n-class classification
  DEBUGLF("exit\n");
}

ErrorCode CTrainTestHOG::get_images(const cv::String & dirName,
                                    std::vector<cv::Mat> & imgList,
                                    bool showImages) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  vector<String> files;
  try {
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
    DEBUGLD("\t\t\tImage list size=[%ld]\n", imgList.size());
  } catch (cv::Exception& e) {
    errCode = EXIT_FAILURE;
    DEBUGLE("\t*** An exception occurred=[%s] ***\n", e.what());
  } catch (...) {
    errCode = EXIT_FAILURE;
    DEBUGLE("\t*** An unknown exception occurred ***\n");
  }
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::get_cropped_faces(std::vector<cv::Mat> & imgList) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
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
  DEBUGLD("\t\t\tCropped Faces in Image list=[%ld]\n", imgList.size());
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::get_preprocessed_faces(
    std::vector<cv::Mat> & croppedFacesList) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  for (auto cFace : croppedFacesList) {
    cv::resize(cFace, cFace, cv::Size(128, 128));
  }
  DEBUGLD("\t\t\tPre-Processed Faces in Image list=[%ld]\n",
          croppedFacesList.size());
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::get_ftfv_dataset(cv::String ft, cv::String fv,
                                          std::vector<cv::Mat>& trainData,
                                          std::vector<cv::Mat>& predData,
                                          std::vector<int>& trainLabels,
                                          std::vector<int>& predLabels) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    cv::String folderName = cv::format("%s/%s/%s", getenv(FFR_DATASET_PATH),
                                       ft.c_str(), fv.c_str());
    DEBUGLD("\t\t\tGetting dataset from=[%s]\n", folderName.c_str());
    std::vector<cv::Mat> imgList;
    this->get_images(folderName, imgList);
    this->get_cropped_faces(imgList);
    this->get_preprocessed_faces(imgList);

    //-- return on empty img list to prevent seg fault
    if (imgList.empty()) {
      errCode = EXIT_FAILURE;
      DEBUGLE("Error img list is empty!\n");
      break;
    }
    DEBUGLD("\t\t\timgList.size()=[%ld]\n", imgList.size());
    std::random_shuffle(imgList.begin(), imgList.end());  // optional
    int trainPart = imgList.size() * 0.8;  // 80% for training
    int predPart = imgList.size() - trainPart;  // 20% for predicting
    DEBUGLD("\t\t\ttrainPart=[%d], predPart=[%d]\n", trainPart, predPart);
    trainData.reserve(trainPart);
    predData.reserve(predPart);
    ft_t::iterator ft_iter = m_FeatureList.find(ft);
    fv_t::iterator fv_iter = ft_iter->second.find(fv);
    int label = std::distance(ft_iter->second.begin(), fv_iter);
    DEBUGLD("\t\t\tlabel=[%d]\n", label);

    int i = 0;
    for (; i < trainPart; ++i) {
      trainData.push_back(imgList.at(i));
      trainLabels.push_back(label);
    }
    DEBUGLD("\t\t\ti=[%d], trainData.size()=[%ld], trainLabels.size()=[%ld]\n",
            i, trainData.size(), trainLabels.size());
    for (; i < imgList.size(); ++i) {
      predData.push_back(imgList.at(i));
      predLabels.push_back(label);
    }
    DEBUGLD("\t\t\ti=[%d], predData.size()=[%ld], predLabels.size()=[%ld]\n", i,
            predData.size(), predLabels.size());
  } while (0);
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::get_ft_dataset(cv::String ft,
                                        std::vector<cv::Mat>& trainData,
                                        std::vector<cv::Mat>& predData,
                                        std::vector<int>& trainLabels,
                                        std::vector<int>& predLabels) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  fv_t &featureValueList = m_FeatureList.find(ft)->second;
  for (auto fv : featureValueList) {
    DEBUGLD("\t\t\tFeature value=[%s]\n", fv.c_str());
    std::vector<cv::Mat> _trainData;
    std::vector<cv::Mat> _predData;
    std::vector<int> _trainLabels;
    std::vector<int> _predLabels;
    errCode = this->get_ftfv_dataset(ft, fv, _trainData, _predData,
                                     _trainLabels, _predLabels);
    if (errCode != EXIT_SUCCESS)
      break;
    trainData.insert(trainData.end(), _trainData.begin(), _trainData.end());
    predData.insert(predData.end(), _predData.begin(), _predData.end());
    trainLabels.insert(trainLabels.end(), _trainLabels.begin(),
                       _trainLabels.end());
    predLabels.insert(predLabels.end(), _predLabels.begin(), _predLabels.end());
  }
  m_hogImgSize = trainData[0].size() / 8 * 8;
  m_HOG.winSize = m_hogImgSize;
  DEBUGLD("\t\t\ttrainData.size()=[%ld], trainLabels.size()=[%ld]\n",
          trainData.size(), trainLabels.size());
  DEBUGLD("\t\t\tpredData.size()=[%ld], predLabels.size()=[%ld]\n",
          predData.size(), predLabels.size());
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::computeHOGs(std::vector<cv::Mat> & imgHogList) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  vector<Mat> hogMats;
  vector<float> descriptors;
  for (auto img : imgHogList) {
    if (img.cols >= m_hogImgSize.width && img.rows >= m_hogImgSize.height) {
      Rect r = Rect((img.cols - m_hogImgSize.width) / 2,
                    (img.rows - m_hogImgSize.height) / 2, m_hogImgSize.width,
                    m_hogImgSize.height);
      m_HOG.compute(img(r), descriptors, Size(8, 8), Size(0, 0));
      hogMats.push_back(Mat(descriptors).clone());
    }
  }
  imgHogList.swap(hogMats);
  DEBUGLD("\t\t\timgHogList.size()=[%ld]\n", imgHogList.size());
  DEBUGLF("exit\n");
  return errCode;
}

/*
 * Convert training/testing set to be used by OpenCV Machine Learning algorithms.
 * TrainData is a matrix of size (#samples x max(#cols,#rows) per samples), in 32FC1.
 * Transposition of samples are made if needed.
 */
ErrorCode CTrainTestHOG::convert_to_ml(
    const std::vector<cv::Mat> & train_samples, cv::Mat& trainData) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    if (train_samples.empty()) {
      errCode = EXIT_FAILURE;
      break;
    }
    //-- Convert hog features data to ml data
    const int rows = (int) train_samples.size();
    const int cols = (int) std::max(train_samples[0].cols,
                                    train_samples[0].rows);
    Mat tmp(1, cols, CV_32FC1);  //< used for transposition if needed
    trainData = Mat(rows, cols, CV_32FC1);

    try {
      for (size_t i = 0; i < train_samples.size(); ++i) {
        DEBUGLD(
            "\t\t\ttrain_samples[%ld].cols=[%d], train_samples[%ld].rows=[%d]\n",
            i, train_samples[i].cols, i, train_samples[i].rows);
        CV_Assert(train_samples[i].cols == 1 || train_samples[i].rows == 1);
        if (train_samples[i].cols == 1) {
          cv::transpose(train_samples[i], tmp);
          tmp.copyTo(trainData.row((int) i));
        } else if (train_samples[i].rows == 1) {
          train_samples[i].copyTo(trainData.row((int) i));
        }
      }
    } catch (cv::Exception& e) {
      errCode = EXIT_FAILURE;
      DEBUGLE("\t*** An exception occurred=[%s] ***\n", e.what());
    } catch (...) {
      errCode = EXIT_FAILURE;
      DEBUGLE("\t*** An unknown exception occurred ***\n");
    }
    DEBUGLD("\t\t\ttrainData.rows=[%d]\n", trainData.rows);
  } while (0);
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::get_prediction_accuracy(
    const std::vector<int>& pLables, const std::vector<int>& rLables,
    float& accuracy) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  // pred labels and result labels must be of same size
  int misMatchCount = 0;
  for (size_t i = 0; i < rLables.size(); ++i) {
    if (rLables.at(i) != pLables.at(i))
      misMatchCount++;
  }
  int correct = rLables.size() - misMatchCount;
  accuracy = correct * 100.0f / rLables.size();
  DEBUGLF("exit\n");
  return errCode;
}

int CTrainTestHOG::Run(int run_times) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    for (auto ft : m_FeatureList) {
      DEBUGLD("\tFeature type=[%s]\n", ft.first.c_str());
      std::vector<float> predictionAccuracyList;
      predictionAccuracyList.reserve(run_times);

      for (int run = 0; run < run_times; ++run) {
        DEBUGLD("\t\tRun=[%d]\n", run);
        vector<Mat> trainData, predData;
        vector<int> trainLabels, predLabels;
        // get pre-processed face data
        errCode = this->get_ft_dataset(ft.first, trainData, predData,
                                       trainLabels, predLabels);
        if (errCode != EXIT_SUCCESS) {
          DEBUGLE("Error in getting dataset for the feature type=[%s]\n",
                  ft.first.c_str());
          break;
        }
        // compute HOG for each pre-processed face
        errCode = this->computeHOGs(trainData);
        if (errCode != EXIT_SUCCESS) {
          DEBUGLE("Error in computing HOGs for the feature type=[%s]\n",
                  ft.first.c_str());
          break;
        }
        // convert HOG feature vectors to SVM data
        Mat ml_train_data;
        errCode = this->convert_to_ml(trainData, ml_train_data);
        if (errCode != EXIT_SUCCESS) {
          DEBUGLE("Error in converting to ml for the feature type=[%s]\n",
                  ft.first.c_str());
          break;
        }
        trainLabels.resize(ml_train_data.rows);
        // train svm
        DEBUGLD("\t\tTraining SVM - begin\n");
        m_pSVM->train(ml_train_data, ROW_SAMPLE, trainLabels);
        DEBUGLD("\t\tTraining SVM - end\n");

        // save the model
        cv::String svmModelFileName = cv::format("%s/cv4_svm_%s_model.yml",
                                                 getenv(FFR_DATASET_PATH),
                                                 ft.first.c_str());
        m_pSVM->save(svmModelFileName.c_str());
        DEBUGLD("\t\tSaved SVM model=[%s]\n", svmModelFileName.c_str());

        // test the model
        // compute HOG for each pre-processed face
        errCode = this->computeHOGs(predData);
        if (errCode != EXIT_SUCCESS) {
          DEBUGLE("Error in computing HOGs for the feature type=[%s]\n",
                  ft.first.c_str());
          break;
        }
        // convert HOG feature vectors to SVM data
        Mat ml_pred_data;
        vector<int> resultLabels;
        errCode = this->convert_to_ml(predData, ml_pred_data);
        if (errCode != EXIT_SUCCESS) {
          DEBUGLE("Error in converting to ml for the feature type=[%s]\n",
                  ft.first.c_str());
          break;
        }
        predLabels.resize(ml_pred_data.rows);
        //resultLabels.resize(ml_pred_data.rows);
        // test svm
        DEBUGLD("\t\tTesting SVM - begin\n");
        m_pSVM->predict(ml_pred_data, resultLabels);
        DEBUGLD("\t\tTesting SVM - end\n");

        // check the accuracy
        float accuracy = 0.0f;
        this->get_prediction_accuracy(predLabels, resultLabels, accuracy);
        DEBUGLD("\t\tPrediction accuracy=[%lf]\n", accuracy);
        predictionAccuracyList.push_back(accuracy);
      }
      // print the mean accuracy
      float sum_of_accuracies = std::accumulate(predictionAccuracyList.begin(),
                                                predictionAccuracyList.end(),
                                                0.0);
      float mean_accuracy = sum_of_accuracies / predictionAccuracyList.size();
      DEBUGLD("\t\tMean prediction accuracy=[%lf]\n", mean_accuracy);
    }
  } while (0);
  DEBUGLF("exit\n");
  return errCode;
}

}  // namespace PFF
