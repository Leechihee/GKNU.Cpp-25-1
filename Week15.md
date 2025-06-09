# WINDOWS SKD로 메세지 박스 띄우기
## 1. main 함수로 메세지 박스 띄우기
```cpp
#include <windows.h>

int main()
{
	MessageBox(NULL, L"I love CPP", L"GKNU",NULL);
	return 0;
}
```
## 2. WinMain으로 창 띄우기
```cpp
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MessageBox(NULL, L"Hello", L"Box", MB_OK);
	return 0;
}
```
