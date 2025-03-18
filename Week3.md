#First
```cpp
// 상속
// inheotance
// protected
#include <iostream>
using namespace std;

class CPoly {
protected:
	int w, h;
public:
	CPoly(int x, int y) : w(x), h(y) {}
};

class CRect : public CPoly {
public:
	CRect(int x, int y) : CPoly(x, y) {}
	int Area() { return w * h; }
};

int main()
{
	CRect* p = new CRect(2, 3); // 동적할당, 내가 임의로 지정했기때문에 나중에 필요가 없어지면 delete를 이용해서 메모리를 반납해줘야한다.
	cout << p->Area();
	delete p; // p에 내가 임의로 지정한 메모리가 들어있고 이제 필요가 없기때문에 반납해야한다.
	return 0;
}
```
#Second / fucntion overriding
```cpp
#include <iostream>

class CPoly {
protected:
    int w, h;
public:
    CPoly(int x, int y) : w(x), h(y) {}
    virtual int Area() {} // 
    virtual ~CPoly() {}
};

class CRect : public CPoly {
public:
    CRect(int x, int height) : CPoly(x, y) {}
    int Area() override {
        return (w * h) / 2; // 삼각형 면적 계산 공식 적용
    }
};

int main() {
    CRect rect(10, 5);
    
    std::cout << "Rectangle Area: " << rect.Area() << std::endl;
    
    return 0;
}
```
