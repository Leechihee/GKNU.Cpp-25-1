# 이미지 띄우기
```cpp
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("jcshim.jpeg");
	if (img.empty())
	{
		cerr << "Error!";
		exit(1);
	}
	imshow("GKNU", img);
	waitKey(0);
	return 0;
}
```
# 얼굴 찾기
```cpp
#include<OpenCV2/openCV.hpp>
#include<iostream>

using namespace cv;
int main() {
	Mat img = imread("jcshim.jpeg");
	CascadeClassifier hc("haarcascade_frontalface_default.xml");

	std::vector<Rect> fs;
	hc.detectMultiScale(img, fs);

	for (auto& f : fs) {
		rectangle(img, f, Scalar(255, 0, 0), 2);
	}
	imshow("Faces", img);
	waitKey(0);
}

```
