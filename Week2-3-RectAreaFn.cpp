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
