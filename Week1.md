# First.cpp
```cpp
#include <iostream> // 머리부분인 #include는 전처리기를 뜻하며 프로그램이 시작될때 가장 먼저 실행이 된다.
                    // 뒤에 붙는 <iostream>은 입출력 함수/클래스를 사용할 수 있게 해주는 헤더이다.

using namespace std; // iostream 안에 있는 함수 중 출력함수인 cout를 사용하기 위해선 std::cout을 입력을 해야하지만
                     // 위 코드를 전역변수로 선언하면 std:: 를 사용하지 않아도 cout을 사용할 수 있게 한다.


int main()
{
    int A = 2, B = 3; // int형 변수를 선언하는 코드이고 위 코드가 실행되면 int형에 알맞는 메모리(4byte)를 자동할당해주는 코드이며
                      // A라는 메모리에 2라는 값을 넣고 B라는 메모리에 3이라는 값을 넣는 코드이다.
    cout << A + B; // A에 있는 값과 B에 있는 값을 더하고 출력하는 함수이다.
    return 0; // 해당 함수의 결과값을 출력하는 함수이며 이 프로그램(함수)가 제대로 실행이 되었는지 확인하는 용도로 쓰이기도 한다.
}

/*코드 자체는 몇줄 안되어있지만 하나하나 해석하고 분석해보면 많은 코드들이 엮어있는 것을 알 수 있다.
간단한 변수 선언도 사실 메모리를 할당해주는 것이고 출력하는 것도 나중에 배울 stream이 해준다는 것을 알 수 있었다.*/
```

# Second.cpp
```cpp
#include <iostream> 

using namespace std;


/*함수를 정의하는 방법이며 맨 앞부분에 붙는 int는 이 함수가 출력하는 데이터의 형이고
뒤에 붙는 Add부분은 함수의 이름이다. 그리고 ()안에 들어가는 내용인 int a, int b는 이 함수의 매개변수를 뜻한다.
마지막으로 {} 안에 코드를 넣어 함수가 실행하도록 해야한다.*/
int Add(int a, int b) // 두 수를 함수에 전달하여 더 한 값을 출력하는 함수이다.
{
    return a + b; // 매개변수로 a, b를 받았으니 a + b를 한 값을 출력한다.
}

int main()
{
    int A = 2, B = 3;
    cout << Add(A,B); // 함수의 출력값이 int형이므로 cout을 이용하여 화면에 출력이 가능하다.
    return 0;
}

/*함수를 정의하고 정의한 함수를 이용하여 두 수를 넣는 방법을 배웠다. 이 방법은 나중에 함수를 이용한 프로젝트나
코딩테스트 문제를 풀때에 도움이 많이 될것이다.*/
```
