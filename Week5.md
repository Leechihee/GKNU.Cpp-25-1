# Friend / Inline
```cpp
#include <iostream>

class Cpnt {
	int x, y;
public:
	inline Cpnt(int n = 0, int m = 0);
	inline void Out();
	//Cpnt Add(const Cpnt& c) { return Cpnt(x + c.x, y + c.y); }
	Cpnt operator+(const Cpnt& p);
	~Cpnt() {}
	friend int main();
};

void Cpnt::Out() { std::cout << this->x << ' ' << this->y << std::endl; } // this는 객체 스스로를 뜻하는 포인터이다.
Cpnt::Cpnt(int x, int y)
{
	this->x = x;
	this->y = y;
}
Cpnt Cpnt::operator+(const Cpnt& p) { return Cpnt(x + p.x, y + p.y); }

int main()
{
	Cpnt p1(1, 1);
	p1.x = 88;
	p1.Out();
	return 0;
}
```
# Initializer_list
```cpp
#include <iostream>
#include <initializer_list> // == vector

void pr(int* v)
{
	int i = 0;
	while (i < 5)
		std::cout << *(v + i++) << ' ';
	std::cout << std::endl;
}

void print(std::initializer_list<int> nums)
{
	for (int n : nums)
		std::cout << n << ' ';
	std::cout << std::endl;
}

int main()
{
	int v[] = { 1,2,3,4,5 };
	std::cout << "pr(v) = ";  pr(v);
	std::cout << "print({1,2,3,4,5}) = ";  print({ 1,2,3,4,5 });
	return 0;
}
```
# AbsClass & 생성자 상속
```cpp
#include <iostream>

// abs class : 상속으로만 사용할 수 있는 클래스. 객체 자체를 생성할 수 없다.
// cpp에선 다형성, 타 언어에선 interface 라고 지칭함.
class Cpoly {
protected:
	int w, h;
public:
	Cpoly(int a, int b) : w(a), h(b) {}
	virtual void Area() = 0; // pure virtual function
	// 순수 가상 함수 : 추상화 클래스를 상속받는 모든 자식 클래스는 해당 메서드함수를 정의해줘야한다.
	// 정의 해주지 않으면 컴파일 오류가 난다.
};

class Crect : public Cpoly{
public:
	//Crect(int a, int b) : Cpoly(a, b) {} // 기존 생성자 선언 방법
	using Cpoly::Cpoly; // 부모 클래스의 생성자를 상속받아 생성자를 선언하는 방법
	/*생성자의 상속 : 부모 클래스의 생성자를 상속받는다.
	using 키워드를 사용하는 이유는 코드를 보다 쉽게 작성&관리하기 위해 사용한다.
	기능으론 다른 점이 없다.*/

	void Area() override { std::cout << w * h << std::endl; }
};

int main()
{
	Crect r(2,3);
	Cpoly* p = &r;
	p->Area();
	return 0;
}
```
# 다형성
```cpp
#include <iostream>

class Cpoly {
protected:
	int w, h;
public:
	Cpoly(int a, int b) : w(a), h(b) {}
	virtual void Area() = 0;
};

class Crect : public Cpoly {
public:
	using Cpoly::Cpoly;
	void Area() override { std::cout << w * h << std::endl; }
};

class Ctrie : public Cpoly {
public:
	using Cpoly::Cpoly;
	void Area() override { std::cout << w * h / 2 << std::endl; }
};

int main()
{
	Cpoly* p = nullptr;
	Crect* r = new Crect(2, 3);
	Ctrie* t = new Ctrie(2, 3);
	p = r;  p->Area();
	p = t;  p->Area();
	// 하나의 부모객체 포인터변수로 자식객체를 사용할 수 있다.
	// 다형성을 활용하기 위해 사용한다.
	delete r;
	delete t;
	return 0;
}
```
# Reference
```cpp
#include <iostream>

void inc(int& num)
{
	num++;
}

int main()
{
	int a = 0;
	inc(a);
	std::cout << a << std::endl;
	inc(a);
	std::cout << a << std::endl;
	inc(a);
	std::cout << a << std::endl;
	inc(a);
	std::cout << a << std::endl;
	return 0;
}
```
# Template & Reference / Swap, Print function
```cpp
#include <iostream>

template<typename T>
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
void print(T x, T y)
{
	std::cout << x << " , " << y << std::endl;
}

int main()
{
	int x = 10, y = 20;
	print(x, y);
	swap<int>(x, y); // 매개변수 형태 명시
	print(x, y);
	double a = 1.1, b = 2.2;
	print(a, b);
	swap<double>(a, b); // 매개변수 형태 명시
	print(a, b);
	return 0;
}
```
