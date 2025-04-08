# Template Class
```cpp
#include <iostream>

template<typename T>
class CMy {
	T num1, num2;
public:
	CMy() {}
	T Add(T a, T b)
	{
		num1 = a;
		num2 = b;
		return num1 + num2;
	}
};

int main()
{
	CMy<double> me; // 객체 생성할 때, 타입을 명시해줘야함
	int a1 = 2, a2 = 3;
	std::cout << me.Add(a1, a2) << std::endl;
	double b1 = 2.2, b2 = 3.3;
	std::cout << me.Add(b1, b2) << std::endl;
	return 0;
}
```
# Memory / Smart Pointer
```cpp
#include <iostream>
#include <memory>

class CPnt {
	int x, y;
public:
	CPnt(int x=0, int y=0) { this->x = x; this->y = y; }
	void Out() { std::cout << x << ' ' << y << std::endl; }
};

int main()
{
	std::unique_ptr<CPnt> p = std::make_unique<CPnt>(); // delete 불필요 , unique_ptr이 자동 해제
	p->Out();
	return 0;
}
```
# Exception
```cpp
#include <iostream>

class CPnt {
	int x, y;
public:
	CPnt(int x=0, int y=0) { this->x = x; this->y = y; }
	void Out() { std::cout << x << ' ' << y << std::endl; }
};

int main()
{
	try {
		CPnt* p = new CPnt();
		p->Out();
		int a = 3, c = 0;
		std::cout << a / c;
		delete p;
	}
	catch(...){
		std::cout << "예외발생\n";
	}
	return 0;
}
```
