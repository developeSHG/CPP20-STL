#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <coroutine>
#include <array>
#include <set>

// 오늘의 주제 : Container #3 (contains + prefix/suffix checking)

// 이전 글에 한 erase, erase_if처럼 유용하게 활용할 수 있는 기능

int main()
{
	// contains
	{
		std::set s{ 1,2,3,4,5 };

		// map이나 set은 이렇게 find를 해서 원하는 원소를 찾을 수 있다.
		auto findit = s.find(2);
		if (findit != s.end()) // 끝이 아니라면
			cout << "찾았다" << endl;

		// 하지만 이렇게 두 단계에 걸쳐서 찾는 방법도 조금 가독성이 떨어진다는 생각이 든다.
		// 그래서 C#이랑 비슷하게 C++20에서 contains가 추가되었다.
		if (s.contains(2))
			cout << "찾았다" << endl;

		std::map<int, int> m({ 1, 1000 }, { 2,2000 });
		if (m.contains(2))
			cout << "찾았다" << endl;
	}

	// string의 prefix/suffix (starts_with, ends_with)
	{
		std::string str = "Hello World";

		// string에서 특정 문자열로 시작하는지 체크해보자.
		// 새로 추가된 버전
		bool b1 = str.starts_with("Hello");
		bool b2 = str.ends_with("World");

		std::string str2 = "Hello";
		bool b3 = str.starts_with(str2);

		// 문자열을 활용할 일이 생각보다 없긴 하겠지만,
		// 굳이 예제를 생각해보면 툴을 만드는데 파일 입출력을 통해
		// 파일을 갖고 온 다음에, 특정 단어로 시작하면 어떤 타입으로 인지한다고 하면
		// 사용할 수 있지 않을까 싶다.
	}

	// 결론) contains가 유용하다.
}