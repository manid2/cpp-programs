# Modified samples for OpenCV

## Example Cpp train HOG

There are not enough tutorials or sample codes online to train a SVM
model in C++. There is just one sample provided in the official
opencv repo to train the SVM with HOG, [train_HOG.cpp][l1]. It uses
**Support Vector Regression** to detect people in a video or a list of images.

Hence modified this sample to use SVM with HOG features as **n-class
classifier**.

The prediction accuracy results log for training the SVM with HOG using OpenCV 4.0 is, [prediction_accuracy_log][l2].

### Sample input image

![Harry Potter sample input image][hp_in]

### Result output image

![Harry Potter result output image][hp_out]

<!-- images in the post -->
[hp_in]: data/harry_potter_test_img_1.jpg  "sample inpit image"
[hp_out]: data/result_harry_potter_test_img_1.jpg  "result output image"

> *NOTE: Due to long hair for all three people in the image it is detecting the gender as 'female' which is a false positive. In machine learning algorithms the false positives are always common given the input sample image has ambiguous features.*

<!-- Links in the post -->
[l1]: https://github.com/opencv/opencv/blob/master/samples/cpp/train_HOG.cpp
[l2]: https://github.com/manid2/ProgramsForFun/blob/master/LearnOpenCV/ModifiedSamples/cv4_hog_svm_success_log.txt

