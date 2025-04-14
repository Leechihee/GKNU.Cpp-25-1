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
STL 중 출력값이 pair, triple 같은 컨테이너 함수인 경우에 매번 쓰기에 가독성과 효율이 떨어지기 때문에 auto 또는 typedef를 이용하여 줄인다.**
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
	for (const auto& a : upArray) 
	{
		a->pr();
	}
	return 0;
}
```
