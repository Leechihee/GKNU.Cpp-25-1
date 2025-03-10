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
