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
//# define ENABLE_DEBUG_MODE
#endif // ENABLE_DEBUG_MODE

namespace PFF {

CTrainTestHOG::CTrainTestHOG()
    : _className(FUNC_NAME) {
  DEBUGLF("enter\n");
  //-- test models flow
  this->isTestModels = false;
  this->isShowImage = false;

  // should recognize all features by default
  m_features.insert(PFF::Age);
  m_features.insert(PFF::Emotion);
  m_features.insert(PFF::Gender);

  // putText params
  m_fontFace = cv::FONT_HERSHEY_SIMPLEX;
  m_fontScale = 0.75f;
  m_fontColor = Scalar(240, 40, 240);
  m_lineType = 8;

  //-- train models flow
  this->isPredict = false;
  this->isSaveModel = false;
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
  m_pSVM->setKernel(SVM::LINEAR);
  m_pSVM->setType(SVM::C_SVC);  // n-class classification
  m_pSVM->setC(2.67);
  m_pSVM->setGamma(5.383);
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

      if (showImages) {
        cv::imshow("image", img);
        cv::waitKey(1);
      }
      imgList.push_back(img);
    }DEBUGLD("\t\t\tImage list size=[%ld]\n", imgList.size());
  } catch (cv::Exception& e) {
    errCode = EXIT_FAILURE;
    DEBUGLE("\t*** An exception occurred=[%s] ***\n", e.what());
  } catch (...) {
    errCode = EXIT_FAILURE;
    DEBUGLE("\t*** An unknown exception occurred ***\n");
  }DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::get_cropped_faces(std::vector<cv::Mat> & imgList) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  std::vector<cv::Mat> cropped_faces;
  //-- for each img
  for (size_t i = 0; i < imgList.size(); ++i) {
    cv::Mat &img = imgList.at(i);
    cv::equalizeHist(img, img);
    std::vector<Rect> faces_r;
    m_faceCascade.detectMultiScale(img, faces_r);
    //-- for each face in img
    for (size_t i = 0; i < faces_r.size(); ++i) {
      cropped_faces.push_back(img(faces_r[i]));
    }
  }
  imgList.swap(cropped_faces);
  DEBUGLD("\t\t\tCropped Faces in Image list=[%ld]\n", imgList.size());DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::get_preprocessed_faces(
    std::vector<cv::Mat> & croppedFacesList) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  for (size_t i = 0; i < croppedFacesList.size(); ++i) {
    cv::Mat &cFace = croppedFacesList.at(i);
    cv::resize(cFace, cFace, cv::Size(64, 64));
  }DEBUGLD("\t\t\tPre-Processed Faces in Image list=[%ld]\n",
      croppedFacesList.size());DEBUGLF("exit\n");
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
    }DEBUGLD("\t\t\timgList.size()=[%ld]\n", imgList.size());
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
    }DEBUGLD("\t\t\ti=[%d], trainData.size()=[%ld], trainLabels.size()=[%ld]\n",
        i, trainData.size(), trainLabels.size());
    for (; i < imgList.size(); ++i) {
      predData.push_back(imgList.at(i));
      predLabels.push_back(label);
    }DEBUGLD("\t\t\ti=[%d], predData.size()=[%ld], predLabels.size()=[%ld]\n",
        i, predData.size(), predLabels.size());
  } while (0);DEBUGLF("exit\n");
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
    DEBUGLW("\t\t\tFeature value=[%s]\n", fv.c_str());
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
  DEBUGLW("\t\t\ttrainData.size()=[%ld], trainLabels.size()=[%ld]\n",
          trainData.size(), trainLabels.size());
  DEBUGLW("\t\t\tpredData.size()=[%ld], predLabels.size()=[%ld]\n",
          predData.size(), predLabels.size());
  /*for (size_t i = 0; i < trainData.size(); ++i) {
   cout << "i=" << i << " trainData.size: " << trainData.at(i).size() << endl;
   }*/
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::computeHOGs(std::vector<cv::Mat> & imgHogList) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  HOGDescriptor hog;
  vector<Mat> hogMats;
  vector<float> descriptors;
  for (auto img : imgHogList) {
    //cout << "img.size(): " << img.size() << " ";
    //m_HOG.compute(img, descriptors);
    hog.winSize = img.size() / 8 * 8;
    hog.compute(img, descriptors);
    //descriptors.resize(64);
    cv::Mat descriptors_mat(Mat(descriptors).clone());
    /*cout << "descriptors.size(): " << descriptors.size() << " ";
     cout << "descriptors_mat.size(): " << descriptors_mat.size() << endl;*/
    hogMats.push_back(descriptors_mat);
  }
  imgHogList.swap(hogMats);
  DEBUGLD("\t\t\timgHogList.size()=[%ld]\n", imgHogList.size());DEBUGLF("exit\n");
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
    }DEBUGLD("\t\t\ttrainData.rows=[%d]\n", trainData.rows);
  } while (0);DEBUGLF("exit\n");
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

ErrorCode CTrainTestHOG::readImageFromFile(const std::string& fileName,
                                            cv::Mat& img_i, cv::Mat& img_o) {
  DEBUGLF("enter\n");
  ErrorCode err = 0;
  do {  // for common error handling
    cv::Mat img = cv::imread(fileName);  // load image in default
    img_i = img;
    this->readImage(img);
    img_o = img;
    // currently using this just for unit testing, will extend in future
  } while (0);
  DEBUGLF("exit\n");
  return err;
}

ErrorCode CTrainTestHOG::readImage(cv::Mat& img) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    // Detect faces in the image
    cv::Mat frame_gray;
    std::vector<Rect> faces;
    errCode = this->detectFace(img, faces, frame_gray);

    // Recognize facial features
    m_resultsVec = ResultsVec(faces.size());
    this->recognizeFeatures(m_features, m_resultsVec, frame_gray, faces);

    // Draw the results on the original image
    this->drawResults(img, faces, m_features, m_resultsVec);
  } while (0);
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::detectFace(cv::Mat& frame,
                                    std::vector<cv::Rect>& faces,
                                    cv::Mat& frame_gray) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    // Pre-process input frame for face detection
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    // Detect faces
    this->m_faceCascade.detectMultiScale(frame_gray, faces);
  } while (0);
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::recognizeFeatures(const FeaturesSet& features,
                                           ResultsVec& results,
                                           cv::Mat& frame_gray,
                                           std::vector<cv::Rect>& faces) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    cv::Mat face_mat;  // dont modify frame_gray
    for (size_t fa = 0; fa < faces.size(); fa++) {
      // 1. crop the face from the frame
      face_mat = frame_gray(faces.at(fa));

      // 2. resize to 64,64
      cv::resize(face_mat, face_mat, cv::Size(64, 64));

      // 3. get HOG fv
      cv::Mat hogMat;
      this->computeHOG(face_mat, hogMat);

      // 4. convert hog to ml for SVM
      cv::Mat mlMat;
      this->convertToML(hogMat, mlMat);

      // 4. make predictions for each feature
      // TODO
    }
  } while (0); DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::drawResults(cv::Mat& frame,
                                     const std::vector<cv::Rect>& faces,
                                     const FeaturesSet& features,
                                     const ResultsVec& results) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    for (size_t fa = 0; fa < faces.size(); fa++) {
      // 1. Draw ellipses around the faces
      const Rect& face_rect = faces.at(fa);
      Point center(face_rect.x + face_rect.width * 0.5,
                   face_rect.y + face_rect.height * 0.5);
      ellipse(frame, center,
              Size(face_rect.width * 0.5, face_rect.height * 0.5), 0, 0, 360,
              Scalar(255, 0, 0), 4, 8, 0);
      // 2. Draw features results text near the faces
      int li = 0;
      // for each face in the results vector iterate through the results pair set
      for (auto res_pair : results.at(fa)) {
        // extract results data here
        const PFF::Feature& f = res_pair.first;
        const std::string& res = res_pair.second;

        // put text on the frame
        putText(frame, format("%-10s: %s", enum2str(f).c_str(), res.c_str()),
                Point(face_rect.x, face_rect.y + li), m_fontFace, m_fontScale,
                m_fontColor, 2);
        li += 22;
      }
    }
  } while (0); DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::computeHOG(const cv::Mat& img, cv::Mat& hogMat) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    vector<float> descriptors;
    cv::HOGDescriptor hog;
    hog.winSize = img.size() / 8 * 8;
    hog.compute(img, descriptors);
    hogMat = Mat(descriptors).clone();
  } while (0);
  DEBUGLF("exit\n");
  return errCode;
}

ErrorCode CTrainTestHOG::convertToML(const cv::Mat& hogMat, cv::Mat& mlMat) {
  DEBUGLF("enter\n");
  ErrorCode err = EXIT_SUCCESS;
  do {  // for common error handling
    if (hogMat.empty()) {
      err = EXIT_FAILURE;
      break;
    }
    //-- Convert hog features data to ml data
    const int cols = (int) std::max(hogMat.cols, hogMat.rows);
    Mat tmp(1, cols, CV_32FC1);  //< used for transposition if needed
    mlMat = Mat(1, cols, CV_32FC1);
    try {
      CV_Assert(hogMat.cols == 1 || hogMat.rows == 1);
      if (hogMat.cols == 1) {
        cv::transpose(hogMat, tmp);
        tmp.copyTo(mlMat.row((int) 0));
      } else if (hogMat.rows == 1) {
        hogMat.copyTo(mlMat.row((int) 0));
      }
    } catch (cv::Exception& e) {
      err = EXIT_FAILURE;
      DEBUGLE("\t*** An exception occurred=[%s] ***\n", e.what());
    } catch (...) {
      err = EXIT_FAILURE;
      DEBUGLE("\t*** An unknown exception occurred ***\n");
    }
    //DEBUGLD("\t\t\tmlMat.cols=[%d], mlMat.type()=[%d]\n", mlMat.cols, mlMat.type());
  } while (0);
  DEBUGLF("exit\n");
  return err;
}

ErrorCode CTrainTestHOG::testModelsOnSingleImage() {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    if (this->m_inFile.empty()) {
      DEBUGLE("!!! enter input image file path !!!\n");
      break;
    }
    if (this->m_outFile.empty()) {
      this->m_outFile = this->m_inFile;
      this->m_outFile.insert(0, "out_");
      DEBUGLW("outFile path is empty using default file path=[%s]\n",
              this->m_outFile.c_str());
    }
    DEBUGLW("*** input params - begin ***\n");
    DEBUGLW("inFile  path is file path=[%s]\n", this->m_inFile.c_str());
    DEBUGLW("outFile path is file path=[%s]\n", this->m_outFile.c_str());
    DEBUGLW("show output image=[%s]\n", this->isShowImage ? "yes" : "no");
    DEBUGLW("*** input params - end ***\n");

    // TODO, YTI below steps
    //-- load the svm models

    //-- read input image from file and write output image
    cv::Mat img_i, img_o;
    this->readImageFromFile(this->m_inFile, img_i, img_o);
    if(this->isShowImage) {
      // TODO: show out image
    }
    // save output image
  } while (0);
  DEBUGLF("exit\n");
  return errCode;
}

int CTrainTestHOG::Run(int run_times) {
  DEBUGLF("enter\n");
  ErrorCode errCode = EXIT_SUCCESS;
  do {  // for common error handling
    //-- test models on a single image flow
    if (this->isTestModels) {
      DEBUGLE("test models on a single image flow\n");
      errCode = this->testModelsOnSingleImage();
      if (errCode != EXIT_SUCCESS) {
        DEBUGLE("Error in testing svm models on single image\n");
      }
      break;
    }
    //-- train models flow (default)
    DEBUGLE("train models flow (default)\n");
    for (auto ft : m_FeatureList) {
      DEBUGLW("\tFeature type=[%s]\n", ft.first.c_str());
      std::vector<float> predictionAccuracyList;
      predictionAccuracyList.reserve(run_times);

      for (int run = 0; run < run_times; ++run) {
        DEBUGLW("\t\tRun=[%d]\n", run);
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
        DEBUGLW("\t\tTraining SVM - begin\n");
        m_pSVM->train(ml_train_data, ROW_SAMPLE, trainLabels);
        DEBUGLW("\t\tTraining SVM - end\n");

        if (this->isSaveModel) {
          // save the model
          cv::String svmModelFileName = cv::format("%s/cv4_svm_%s_model.xml",
                                                   getenv(FFR_DATASET_PATH),
                                                   ft.first.c_str());
          m_pSVM->save(svmModelFileName.c_str());
          DEBUGLW("\t\tSaved SVM model=[%s]\n", svmModelFileName.c_str());
        }

        if (this->isPredict) {
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
          DEBUGLW("\t\tTesting SVM - begin\n");
          Mat responses_mat;
          m_pSVM->predict(ml_pred_data, responses_mat);
          for (size_t i = 0; i < ml_pred_data.rows; ++i) {
            resultLabels.push_back(responses_mat.at<int>(i));
          }
          DEBUGLW("\t\tTesting SVM - end\n");

          // check the accuracy
          float accuracy = 0.0f;
          this->get_prediction_accuracy(predLabels, resultLabels, accuracy);
          DEBUGLW("\t\tPrediction accuracy=[%lf]\n", accuracy);
          predictionAccuracyList.push_back(accuracy);
        }
      }
      if (this->isPredict) {
        // print the mean accuracy
        float sum_of_accuracies = std::accumulate(
            predictionAccuracyList.begin(), predictionAccuracyList.end(), 0.0);
        float mean_accuracy = sum_of_accuracies / predictionAccuracyList.size();
        DEBUGLW("\t\tMean prediction accuracy=[%lf]\n", mean_accuracy);
      }
    }
  } while (0);DEBUGLF("exit\n");
  return errCode;
}

}  // namespace PFF
