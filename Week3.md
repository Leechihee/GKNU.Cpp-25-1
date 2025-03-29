# First / inheritance (상속)
```cpp
#include <iostream>
using namespace std;

class CPoly {
protected: // 상속할 때 자식클래스에게 private으로 상속해준다.
	int w, h;
public:
	CPoly(int x, int y) : w(x), h(y) {}
};

class CRect : public CPoly {
// CPoly를 상속받았기때문에 protected에 있는 w,h는 CRect에선 private으로 사용되어진다.
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
# Second / fucntion overriding (함수의 재정의)
```cpp
#include <iostream>

class CPoly { // 추상화 클래스이며 생성자로 객체를 만들 수 없는 클래스이다. 상속만 하기위한 클래스이다.
protected:
    int w, h;
public:
    CPoly(int x, int y) : w(x), h(y) {}
    virtual int Area() = 0; // 순수 가상 함수 : 추상화 클래스를 만들기위한 코드이며 상속받는 모든 클래스는 순수 가상 함수를 재정의해줘야한다.
    virtual ~CPoly() {} // 파괴자를 가상 함수로 정의하면서 모든 자식 클래스들은 파괴자를 정의해줘야한다.
};

class CRect : public CPoly {
public:
    CRect(int x, int height) : CPoly(x, y) {}
    int Area() override { // 재정의를 명시해줌으로서 실수 캐치와 코드 수정이 보다 쉬움
        return w * h; // 직사각형 면적 계산 공식 적용
    }
};

int main() {
    CRect rect(10, 5);
    
    std::cout << "Rectangle Area: " << rect.Area() << std::endl;
    
    return 0;
}
```
