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
