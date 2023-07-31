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
#include <numbers>
#include <numeric>
#include <bit>
#include <bitset>
#include <chrono>
#include <format>
#include <source_location>
#include <functional>

// 오늘의 주제 : 기타 함수

void PrintLog(const char* filename, int line)
{
	cout << format("{} Line({})", filename, line) << endl;
}

int Add(int a, int b)
{
	return a + b;
}

void Test()
{
	// is_constant_evaluated
	// consteval 붙은 함수는 컴파일 타임에 실행됨
	// constexpr 붙은 함수는 컴파일/런타임 둘다 됨
	// 보통 함수 런타임

	// 경우에 따라 최적하를 하고 싶을 때, 
	// 런타임에 실행되는 게 아니라 컴파일에 실행되게끔 하고 싶을 수 있다.
	// 근데 constexpr이 붙은 함수는 둘 다 가능하다보니 코드에서 컴파일에 실행된다고 가정할 수 없었다.
	// 그래서, 함수에서 내부로 조건을 체크해서 타임을 구분할 수 있게되었다.

	if (std::is_constant_evaluated())
	{
		// 컴파일 타임에 실행되는 코드
	}
	else
	{
		// 런타임에 실행되는 코드
	}
}

int main()
{
	// source_location - 어떤 파일의 몇 번째 줄에서 어떤 이슈가 일어났는지 사용.
	// ex) 로그 남길 때
	// ex) 멀티쓰레드 환경에서 데드락 탐지
	// ex) 메모리 누수를 잡기 위해서 할당/해제
	{
		// 기존에 vs에서 지원해줘서 사용하던 방식.
		PrintLog(__FILE__, __LINE__); // 임시 메크로

		auto src = std::source_location::current(); 
		PrintLog(src.file_name(), src.line()); // 멤버가 file_name외에 column, function_name 등 다양한 정보들도 있다.
	}

	// bind_front (바인딩에 관련된 부분)
	{
		//Add(10, 20); // 커맨드 패턴처럼 나중에 호출한다고 가정해보자.

		using namespace std::placeholders;
		auto func = std::bind(Add, 10, _1); // _1은 함수의 두 번째 인자로 나중에 채워주겠다. 란 의미
		// 마치 함수 포인터처럼 함수를 바인딩했다가, 나중에 두 번째 인자를 건내줘서 계산하겠다.
		cout << func(20) << endl; // 30

		// 근데 위의 형식이 안이뻐보였는지, 추가되었음 (bind랑 거의 비슷함)
		auto func2 = std::bind_front(Add, 10); // C++20
		cout << func2(20) << endl; // 30

		// 하지만 애초에 람다로 캡쳐해서 사용하면 되기에 잘 사용안할듯. 가독성도 더 좋음.
		auto func3 = [](int b) { return Add(10, b); };
		cout << func3(20) << endl;
	}

	Test();
}