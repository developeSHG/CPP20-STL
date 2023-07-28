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
#include <numbers>
#include <numeric>

// 오늘의 주제 : Arithmetic (산술)

int main()
{
	int x = -2;
	unsigned int y = 10;

	{
		// 게임에서 정수를 생각하면, 사실 음수로 떨어지는 정수가 많이 없을 수 있다. (hp, 경험치, 골드 등등)
		// 양의 숫자만 가지는게 일반적.
		// 그럼에도 불구하고, unsigned를 사용하지 않고, int 사용을 많이 한다.
		// 그럼 unsigned랑 int를 섞었을 때, 일어날 수 있는 문제를 살펴보자.
		cout << std::boolalpha;	// 1, 0 이 아니라 true, false로 출력.
		cout << "-2 < 7 = " << (x < y) << endl; // false
		cout << "-2 <= 7 = " << (x <= y) << endl; // false
		cout << "-2 > 7 = " << (x > y) << endl; // true
		cout << "-2 >= 7 = " << (x >= y) << endl; // true

		// 결과가 이상한 걸 볼수있다.
		// 예상대로라면, [true, true, false, false] 가 아니다.

		// 왜 이런 결과가 나타났냐면 int랑 unsigned를 섞어기 떄문에 발생했다.
		// 밑에 처럼 x가 unsigned int로 변환해준 다음에, 비교하게 된다.
		unsigned int tempX = (unsigned int)x;
		auto z = (tempX < y);
	}
	
	// unsigned에서는 알다시피 -2란 숫자가 존재하지 않기 때문에,
	// 동일한 데이터 값을 갖는 상태에서 unsigned로 분석을 해서 숫자를 추출했기 때문에
	// 디버깅을 해보면 매우 큰 숫자로 된 쓰레기 값을 확인할 수 있다.
	// 이런 버그는 디버깅을 하지 않는 이상, 눈으로 찾기 어렵기 떄문에 까다롭다.


	// 이런 경우를 대비해 C++20에서 cmp_XX가 추가되었다. (#include <numbers>)
	{
		cout << "-2 < 7 = " << std::cmp_less(x < y) << endl; // true
		cout << "-2 <= 7 = " << std::cmp_less_equal(x <= y) << endl; // true
		cout << "-2 > 7 = " << std::cmp_greater(x > y) << endl; // false
		cout << "-2 >= 7 = " << std::cmp_greater_equal(x >= y) << endl; // false

		// non-integer 정수 아닌 애들을 넣으면?
		std::cmp_less(3, 1.4f); // 컴파일 ERROR - 무조건 정수만 넣어야한다.

		// 정수랑 소수점이랑 비교하고 싶으면?
		// 그런 경우에는 그냥 변환이 일어나기 떄문에 그냥 하면 된다.
		bool b1 = (3 < 1.4f);

		// 수학 상수 기호들이 추가됨 (#include <numeric>)
		const float PI = 3.14f;
		std::numbers::pi; // double ver
		std::numbers::pi_v<float>; // float ver
		std::numbers::sqrt2; // 루트2
		std::numbers::e; // e (숫자에서 말하는 e. 로그랑 짝을 이루는 애)

		// 중간값 (a + (b - a) / 2)
		// [a | b]
		constexpr int mid = std::midpoint(10, 20); // 15
		
		// 선형 보간 = 비율이 1 : 9로 10%쯤에 위치해있는 수
		// [ a |   b] 
		// (a + t * (b - a))
		constexpr int ler = std::lerp(10, 20, 0.1); // 11
	}
}