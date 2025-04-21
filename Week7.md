# Auto / 데이터형 자동 추론&할당
```cpp
#include <iostream>

int main()
{
	auto a = 1; // int로 추정하여 자동할당한다.
	auto f = 1.1; // float, double 중 하나로 할당된다.
	auto str = "Hello, World!"; // const char*으로 추정된다.
	std::cout << a << ' ' << f << ' ' << str;
	return 0;
}
```
**auto f 같은 문제때문에 auto는 리턴되는 형이 확실할 때 사용해야한다.  
STL 중 출력값이 pair, triple 같은 컨테이너 함수인 경우에 매번 쓰기에 가독성과 효율이 떨어지기 때문에 auto 또는 typedef를 이용하여 줄인다.  
선언과 동시에 초기화를 시켜주지않으면 컴파일에러가 발생한다.**
# Ramda Function // 익명함수
```cpp
#include <iostream>

int main()
{
	auto Add = [](int a, int b) {return a + b; };
	// 간단한 함수를 외부함수로 정의하지않고 람다함수로 정의하여 간단하게 사용할 수 있다.
	// 주 사용처는 STL 알고리즘, 이벤트함수 외 여러가지 부분에서 간단하게 사용할 함수가 필요할때 사용한다.
	std::cout << Add(2, 3);
	return 0;
}
```
# Smart_ptr // 똑똑한 포인터
```cpp
#include <iostream>
#include <memory> // auto_ptr, unique_ptr, share_ptr을 사용하기 위한 헤더

int main()
{
	std::unique_ptr<int> p = std::make_unique<int>(20);
	// 직역하면 유일포인터며 타 포인터에 전달하면 해당 포인터는 주소값을 넘겨주고 소멸한다. (기본적으로 복사생성자를 지원하지않는다.)
	// 또한 자동 delete가 되어 메모리 누수 또한 방지된다.
	std::cout << *p; // 포인터이기 때문에 * 연산자로 접근해야한다. 구조체나 클래스일 경우 ->으로 접근해야한다.
	// delete p; unique_ptr이기 때문에 사용안함. 함수가 종료 될때 자동 delete
	return 0;
}
```

# Smart_ptr Array // 스마트 포인터 배열
```cpp
#include <iostream>
#include <memory>
#include <vector>

class CPnt {
private:
	int x, y;
public:
	CPnt(int a, int b) : x(a), y(b) {};
	~CPnt() {}
	void pr() const { std::cout << x << ' ' << y << std::endl; }
};

int main()
{
	std::unique_ptr<CPnt> upArray[3];
	for (int i = 0; i < 3; i++)
		upArray[i] = std::make_unique<CPnt>(i, i);

  // unique_ptr은 기본적으로 복사생성자를 지원하지않기 때문에
  // call by value가 아닌 call by reference로 가져와야하므로 &으로 가져와야한다.
	for (const auto& a : upArray) // 정보를 가져올 때, 수정을 가하면 문제가 생길 수도 있기때문에 const로 가지고 온다.
	{
		a->pr();
	}
	return 0;
}
```
# Exception / 예외처리
```cpp
#include <iostream>

int main()
{
	int a = 10, b;
	std::cout << "숫자를 입력하시오 : ";
	std::cin >> b;
	try // 블럭 안에서 코드가 실행될 때 예외를 잡는다.
	{
		if (b == 0) // 예외처리, stdexcept, exception 헤더로 다양한 예외처리 클래스를 이용/선언할 수 있다.
			throw "0으로 나눌 수 없습니다."; // catch로 이동하면서 해당 문자열을 전달한다.
		// 문제가 없다면 계속 실행
		std::cout << a / b << '\n';
	}
	// try 블럭 안에서 예외가 발생하여 throw를 통해 바로 이동했다면 해당 블럭 안에 있는 코드 실행
	catch (const char* msg) // 이때 catch의 매개변수로 어떤 예외처리인지 나눌 수 있다.
	{
		std::cerr << "예외발생 : " << msg << std::endl; // 전달 받은 매개변수를 출력한다.
		// std::cerr은 오류 구문 출력할 때에 많이 쓰인다.
	}
	return 0;
}

```cpp
#include <iostream>
#include <fstream>

int main()
{
	std::fstream ifs("my1.txt");
	try
	{
		if (!ifs) // 파일을 열 수 없으면 false 출력 // is_open() 메서드로 출력가능
			throw "파일을 열 수 없습니다.";
	}
	catch (const char* msg)
	{
		std::cerr << msg;
	}
	return 0;
}
```
```
# Fstream // 파일 입출력
## 1. ofstream // 파일 쓰기
```cpp
#include <fstream>

int main()
{
	std::ofstream ofs("my.txt");
	// output file stream이며 파일에 내용을 쓰기 위한 스트림이다.
	// 파일을 열 수 없다면 failbit를 출력하고 진리값으로도 출력한다.
	ofs << 11 << '\n' << 22; // 파일에 출력한다. 기존에 쓰던 << 연산자를 사용한다.
	// 이때 \n이 아닌 띄어쓰기로 칸을 나눌 경우 정수값이 아닌 문자열로 취급하여 출력한다.
	ofs.close();
	return 0;
}
```
## 2. ifstream // 파일 읽기
```cpp
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream ifs("my.txt"); // input file stream이며 파일을 읽기 위한 스트림이다.
	// ofstream과 같이 파일 열기에 실패하면 failbit나 진리값을 출력한다.
	int a, b;
	ifs >> a >> b; // 파일을 읽어 해당 변수에 입력을 한다. 기존에 cin에 쓰던 >> 연산자를 사용한다.
	std::cout << a + b;
	ifs.close();
	return 0;
}
```
**ofstream과 ifstream을 합친 클래스가 fstream이다. 명확히 하기 위해 ifstream과 ofstream을 나누어서 작업하기도 한다.**
