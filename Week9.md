# Vector
```cpp
#include <iostream>
#include <vector> // 임의접근 용이
#include <algorithm> // 각종 알고리즘 포함

using namespace std;

int main()
{
	//vector
	vector<int> v = { 5,2,9,1,3 };
	sort(v.begin(), v.end()); // sort(start_iterator, end_iterator, compare);
	for (int i = 0;i < v.size();i++) // 기본 for문
		cout << v[i] << ' ';
	cout << endl;
	for(int i : v) // 범위기반 for문
		cout << i << ' ';
	cout << endl;
	for (auto it = v.begin(); it != v.end(); it++) // iterator 활용 for문
		cout << *it << ' ';
	return 0;
}
```
# List
```cpp
#include <iostream>
#include <list> // 요소 추가 용이
#include <string>

using namespace std;

int main()
{
	list<string> l = { "apple", "orange", "banana" };
	for (const string& str : l)
		cout << str << ' ';
	cout << endl;
	for (auto it = l.begin();it != l.end();it++)
		cout << *it << ' ';
	cout << endl;
	return 0;
}
```
** list는 index 접근이 불가능, 범위기반 접근과 iterator 접근을 해야한다 **
# Map
```cpp
#include <iostream>
#include <map> // 키로 값 찾기 용이
#include <string>

using namespace std;

int main()
{
	map<string, int> fc;
	fc["apple"] = 3;
	fc["orenge"] = 5;
	fc["banana"] = 2;
	for (const auto& p : fc)
  // map은 pair 구조체로 키,값을 저장함, 이 for문은 map에 저장된 키와 값들을 보는 for문
		cout << p.first << ' ' << p.second << endl;
  cout << endl;
  for(auto it = fc.begin();it!=fc.end();it++)
	  cout << it->first << ' ' << it->second << endl;
	return 0;
}
```
