/* ~~ */ << 주석처리라 부르고 사람은 읽을 수 있지만 컴파일러는 읽을 수 없다. comment라고도 함
// 두 정수를 메모리에 저장하고 더하는 코드를 작성하시오.
#include <iostream> // # 이 붙으면 ; 생략한다.

using namespace std;

int main() // 이름 뒤에 () 붙으면 함수가 된다.
{
  int a = 2; // 데이터를 메모리에 올린다.
  int b = 3;
  cout << a + b;
  return 0;
}
