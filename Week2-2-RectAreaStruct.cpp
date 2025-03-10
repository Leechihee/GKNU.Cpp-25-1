#include <iostream>

typedef struct CRect {
	int wid, hig;
	int Area() { return wid * hig; }
}Rect;

int main()
{
	Rect r;
	r.wid = 3;
	r.hig = 4;
	std::cout << r.Area();
	return 0;
}
