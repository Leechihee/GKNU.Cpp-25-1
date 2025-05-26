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
