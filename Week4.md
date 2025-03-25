# Operator Overloding
```cpp
#include <iostream>

class CPnt {
	int x, y;
public:
	CPnt(int X=0, int Y=0) : x(X), y(Y) {}
	void Out() { std::cout << x << ' ' << y << std::endl; }
	//CPnt Add(CPnt p2) { return CPnt(x + p2.x, y + p2.y); }
	CPnt operator+(CPnt p2) { return CPnt(x + p2.x, y + p2.y); }
};

int main()
{
	CPnt p1(1, 1), p2(2,2), p3;
	//p3 = p1.Add(p2);
	p3 = p1 + p2;
	p1.Out();
	p2.Out();
	p3.Out();
	return 0;
}
```
# Function Templete
```cpp
#include <iostream>

template <typename T>
T Add(T a, T b)
{
	return a + b;
}

int main()
{
	std::cout << Add(1, 2) << std::endl;
	std::cout << Add(2.2, 3.3) << std::endl;
	return 0;
}
```
# Vector Class
```cpp
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v = { 1,2,3 };
	int sum = 0;
	for (int x : v)
		sum += x;
	std::cout << sum << std::endl;
	return 0;
}
```
