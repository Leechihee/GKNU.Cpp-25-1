#RectAreaFn.cpp
```cpp
#include <iostream>

int Area(int w, int h)
{
	return w * h;
}

int main()
{
	int wid = 3, hig = 4;
	std::cout << Area(wid, hig);
	return 0;
}
```

#RectAreaStruct.cpp
```cpp
#include <iostream>

typedef struct CRect {
	int wid, hig;
	int Area() { return wid * hig; }
}Rect;

int main()
{
	Rect r{3,4};
	std::cout << r.Area();
	return 0;
}
```

#RectAreaClass.cpp
```cpp
#include <iostream>

using namespace std;

class Rect
{
private: // 보안성
	 // 맴버함수를 제외한 함수로는 값을 바꿀 수 없다.
	int wid, hig;
public: // inline
	// 바로 실행이 되지만 한번에 로딩 되어 불필요한 누수가 생길 수도 있다.
	// 함수 선언만 하고 정의는 외부로 빼는 방식으로 불필요한 누수를 줄일 수 있다.
	// 여기서 자주 써야하는 함수 같은 경우에는 안에서 바로 정의하고 아니라면
	// 외부에 정의하여 불필요한 누수를 줄인다.
	Rect(int W, int H) { wid = W; hig = H; } // 생성자 (리턴값X, 클래스이름과 동일, 초기화가능), 객체를 생성하는 함수이며 객체를 생성할 때 private 맴버값을 초기화할 수 있는 함수이다.
	void Set(int W, int H) { wid = W; hig = h;) // 인라인 함수를 선언하여 
	int Area();
};

int Rect::Area() // scope operator(범위연산자) ::를 이용하여 클래스 밖에서 public 맴버함수를 정의할 수 있다.
  {
    return wid * hig;
  };

int main()
{
	Rect r(3,4);
	cout << r.Area();
	return 0;
}
```
