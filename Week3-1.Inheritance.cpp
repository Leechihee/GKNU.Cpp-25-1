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
	CRect* p = new CRect(2, 3);
	cout << p->Area();
	delete p;
	return 0;
}
