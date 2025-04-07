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
