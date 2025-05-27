# 손글씨 숫자 예상하기 / onnx 모델 딥러닝
```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
using namespace cv;
using namespace dnn;
using namespace std;

int main() {
    // 모델 경로 및 이미지 경로 설정
    string modelPath = "./mnist-8.onnx";
    string imagePath = "./8.png";

    // ONNX 모델 로드
    Net net = readNetFromONNX(modelPath);

    // 이미지 로드 및 전처리
    Mat img = imread(imagePath, IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "이미지를 불러올 수 없습니다: " << imagePath << endl;
        return -1;
    }
    resize(img, img, Size(28, 28));
    img.convertTo(img, CV_32F, 1.0 / 255);
    Mat blob = blobFromImage(img);  // (1, 1, 28, 28)

    // 입력 및 추론
    net.setInput(blob);
    Mat output = net.forward();  // 출력: (1, 10)

    // 결과 분석
    Point classId;
    double confidence;
    minMaxLoc(output, 0, &confidence, 0, &classId);
    cout << "예측된 숫자: " << classId.x << " (신뢰도: " << confidence << ")" << endl;

    return 0;
}
```
# decltype
```cpp
#include <iostream>

int main()
{
	int a = 5;
	double b = 2.4;

	decltype(a+b) result; // 변수의 형을 재설정한다. 계산 값의 형태를 추정할 수 없을 때 사용.
    // int + double 이면 double로 재설정
	result = a + b; // resulte는 double
	return 0;
}
```
# constexpr
```cpp
#include <iostream>

constexpr int sq(int n) // 런타임 시간에 const 값을 초기화한다.
{
	return n * n;
}

int main()
{
	constexpr int len = sq(4); // const 값이므로 수정 X
	int arr[len]; // constexpr을 구현함으로서 배열의 길이를 런타임 시간에 지정할 수 있음
		
	return 0;
}
```
# 
```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <map>
#include <cmath>

using namespace cv;
using namespace std;

// 코사인 유사도 계산 함수
float cosineSimilarity(const Mat& a, const Mat& b) {
    return a.dot(b) / (norm(a) * norm(b));
}

// 얼굴 특징 추출 함수
Mat extractFeature(cv::dnn::Net& recognizer, const Mat& face) {
    Mat blob = dnn::blobFromImage(face, 1.0 / 255.0, Size(112, 112), Scalar(), true, false);
    recognizer.setInput(blob);
    return recognizer.forward().clone();  // clone() 추가로 안전하게 사용
}

int main() {
    // 얼굴 검출 모델 로드 (Caffe)
    dnn::Net detector = dnn::readNetFromCaffe(
        "./deploy.prototxt",
        "./res10_300x300_ssd_iter_140000_fp16.caffemodel");

    if (detector.empty()) {
        cerr << "Error loading detector model!" << endl;
        return -1;
    }

    // 얼굴 인식 모델 로드 (ONNX)
    dnn::Net recognizer = dnn::readNetFromONNX("./face_recognition_sface_2021dec.onnx");
    if (recognizer.empty()) {
        cerr << "Error loading recognizer model!" << endl;
        return -1;
    }

    // 1. 등록 얼굴 DB (이름 → 특징 벡터)
    map<string, Mat> faceDB;
    vector<pair<string, string>> registration = {
        {"jc2", "./jc2.jpg"},
        {"jcw1", "./jcw1.jpg"}
    };

    for (auto& [name, imgPath] : registration) {
        Mat img = imread(imgPath);
        if (img.empty()) {
            cerr << "Could not load: " << imgPath << endl;
            continue;
        }

        // 얼굴 검출
        Mat blob = dnn::blobFromImage(img, 1.0, Size(300, 300), Scalar(104, 177, 123));
        detector.setInput(blob);
        Mat detections = detector.forward();
        Mat detMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

        for (int i = 0; i < detMat.rows; ++i) {
            float confidence = detMat.at<float>(i, 2);
            if (confidence > 0.5f) {
                int x1 = static_cast<int>(detMat.at<float>(i, 3) * img.cols);
                int y1 = static_cast<int>(detMat.at<float>(i, 4) * img.rows);
                int x2 = static_cast<int>(detMat.at<float>(i, 5) * img.cols);
                int y2 = static_cast<int>(detMat.at<float>(i, 6) * img.rows);
                Rect faceRect(Point(x1, y1), Point(x2, y2));
                Mat face = img(faceRect).clone();

                faceDB[name] = extractFeature(recognizer, face);
                break;
            }
        }
    }

    // 2. 테스트 이미지 로딩
    Mat testImg = imread("./jc1.jpg");  // 경로 수정
    if (testImg.empty()) {
        cerr << "Failed to load test image!" << endl;
        return -1;
    }

    // 얼굴 검출
    Mat blob = dnn::blobFromImage(testImg, 1.0, Size(300, 300), Scalar(104, 177, 123));
    detector.setInput(blob);
    Mat detections = detector.forward();
    Mat detMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

    for (int i = 0; i < detMat.rows; ++i) {
        float confidence = detMat.at<float>(i, 2);
        if (confidence > 0.5f) {
            int x1 = static_cast<int>(detMat.at<float>(i, 3) * testImg.cols);
            int y1 = static_cast<int>(detMat.at<float>(i, 4) * testImg.rows);
            int x2 = static_cast<int>(detMat.at<float>(i, 5) * testImg.cols);
            int y2 = static_cast<int>(detMat.at<float>(i, 6) * testImg.rows);
            Rect faceRect(Point(x1, y1), Point(x2, y2));
            Mat face = testImg(faceRect).clone();

            // 특징 추출
            Mat testFeature = extractFeature(recognizer, face);

            // DB와 유사도 비교
            string matched = "Unknown";
            float maxSim = 0.0f;

            for (auto& [name, regFeature] : faceDB) {
                float sim = cosineSimilarity(testFeature, regFeature);
                if (sim > maxSim && sim > 0.6f) {
                    maxSim = sim;
                    matched = name;
                }
            }

            rectangle(testImg, faceRect, Scalar(0, 255, 0), 2);
            putText(testImg, matched, Point(x1, y1 - 10), FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 0, 255), 2);
        }
    }

    imshow("Face Recognition", testImg);
    imwrite("./result.jpg", testImg);  // 결과 저장도 추가
    waitKey(0);
    return 0;
}
```
# 오류찾기
```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <map>
#include <cmath>

using namespace cv;
using namespace std;

// 코사인 유사도 계산 함수
float cosineSimilarity(const Mat& a, const Mat& b) {
    return a.dot(b) / (norm(a) * norm(b));
}

// 얼굴 특징 추출 함수
Mat extractFeature(cv::dnn::Net& recognizer, const Mat& face) {
    Mat blob = dnn::blobFromImage(face, 1.0 / 255.0, Size(112, 112), Scalar(), true, false);
    recognizer.setInput(blob);
    return recognizer.forward().clone();  // clone() 추가로 안전하게 사용
}

int main() {
    // 얼굴 검출 모델 로드 (Caffe)
    dnn::Net detector =
        dnn::readNetFromCaffe("./deploy.prototxt", "./res10_300x300_ssd_iter_140000.caffemodel");

    if (detector.empty()) {
        cerr << "Error loading detector model!" << endl;
        return -1;
    }

    // 얼굴 인식 모델 로드 (ONNX)
    dnn::Net recognizer = dnn::readNetFromONNX("./face_recognition_sface_2021dec.onnx");
    if (recognizer.empty()) {
        cerr << "Error loading recognizer model!" << endl;
        return -1;
    }

    // 1. 등록 얼굴 DB (이름 → 특징 벡터)
    map<string, Mat> faceDB;
    vector<pair<string, string>> registration = {
        {"Ko", "./ko.jpg"},
        {"Shim", "./shim.jpg"}
    };

    for (auto& [name, imgPath] : registration) {
        Mat img = imread(imgPath);
        if (img.empty()) {
            cerr << "Could not load: " << imgPath << endl;
            continue;
        }

        // 얼굴 검출
        Mat blob = dnn::blobFromImage(img, 1.0, Size(300, 300), Scalar(104, 177, 123));
        detector.setInput(blob);
        Mat detections = detector.forward();
        Mat detMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

        for (int i = 0; i < detMat.rows; ++i) {
            float confidence = detMat.at<float>(i, 2);
            if (confidence > 0.5f) {
                int x1 = static_cast<int>(detMat.at<float>(i, 3) * img.cols);
                int y1 = static_cast<int>(detMat.at<float>(i, 4) * img.rows);
                int x2 = static_cast<int>(detMat.at<float>(i, 5) * img.cols);
                int y2 = static_cast<int>(detMat.at<float>(i, 6) * img.rows);
                Rect faceRect(Point(x1, y1), Point(x2, y2));
                Mat face = img(faceRect).clone();

                faceDB[name] = extractFeature(recognizer, face);
                break;
            }
        }
    }

    // 2. 테스트 이미지 로딩
    Mat testImg = imread("./shim1.jpg");  // 경로 수정
    if (testImg.empty()) {
        cerr << "Failed to load test image!" << endl;
        return -1;
    }

    // 얼굴 검출
    Mat blob = dnn::blobFromImage(testImg, 1.0, Size(300, 300), Scalar(104, 177, 123));
    detector.setInput(blob);
    Mat detections = detector.forward();
    Mat detMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

    for (int i = 0; i < detMat.rows; ++i) {
        float confidence = detMat.at<float>(i, 2);
        if (confidence > 0.5f) {
            int x1 = static_cast<int>(detMat.at<float>(i, 3) * testImg.cols);
            int y1 = static_cast<int>(detMat.at<float>(i, 4) * testImg.rows);
            int x2 = static_cast<int>(detMat.at<float>(i, 5) * testImg.cols);
            int y2 = static_cast<int>(detMat.at<float>(i, 6) * testImg.rows);
            Rect faceRect(Point(x1, y1), Point(x2, y2));
            Mat face = testImg(faceRect).clone();

            // 특징 추출
            Mat testFeature = extractFeature(recognizer, face);

            // DB와 유사도 비교
            string matched = "Unknown";
            float maxSim = 0.0f;

            for (auto& [name, regFeature] : faceDB) {
                float sim = cosineSimilarity(testFeature, regFeature);
                if (sim > maxSim && sim > 0.6f) {
                    maxSim = sim;
                    matched = name;
                }
            }

            rectangle(testImg, faceRect, Scalar(0, 255, 0), 2);
            putText(testImg, matched, Point(x1, y1 - 10), FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 0, 255), 2);
        }
    }

    imshow("Face Recognition", testImg);
    imwrite("./result.jpg", testImg);  // 결과 저장도 추가
    waitKey(0);
    return 0;
}
```
