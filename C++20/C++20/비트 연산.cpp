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

// 오늘의 주제 : 비트 연산

unsigned int BitCount(unsigned int flag)
{
	if (flag == 0)
		return 0;

	// BitCount(0b1010100)
	// = (1 or 0) + BitCount(0b101010)  
	return flag % 2 + BitCount(flag / 2);
}

int main()
{
	// 비트 연산이 자주 사용하느냐?
	// - 암호학
	// - 게임서버 ID (uint64) - 숫자가 거대하니 다 쓰지 않다보니
	// - 기타 알고리즘 문제

	// 피자집 : 피자 주문하는데, 0~19번 스무가지의 토핑이 존재
	bool toppings[20];
	// 위처럼 배열로 그냥 20개를 만들어 줄 수 있지만,
	// 피자가 아니라 mmorpg의 플레이어가 만든 커스터마이징 데이터였다고 가정해보면
	// 플레이어가 워낙 많다보니 자잘한 메모리를 아낄 수 있다면, 전체적으로 봤을 때 굉장히 큰 메모리 전략을 취할 수 있을것이다.
	// 이럴 때 그냥 정수 하나로 비트연산을 하면 유용하다.
	{
		// 전체 구하기
		unsigned int fullPizza = (1 << 20) - 1; // 0b11111111111111 - 다 1로 채워졌으니 full로 비교가능

		// 추가 (or 연산)
		enum { PEPPERONI = 3 };
		unsigned int toppings = 0;
		toppings |= (1 << PEPPERONI); // 3번 토핑 추가 

		// 포함 여부 확인 (end 연산)
		bool added = (toppings & (1 << PEPPERONI)); 

		// 삭제 (not 연산으로 페퍼로니를 제외한 비트를 다 키고, end를 통해 페퍼로니 비트는 0이니 삭제함)
		toppings &= ~(1 << PEPPERONI);

		// 토글
		toppings ^= (1 << PEPPERONI);

		// 개수 구하기
		int count = BitCount(toppings);

		// 최소 원소 찾기
		// (끝에 붙어있는 0은 몇개인가?)
		// Visual C++ : _BitScanForward(&index, toppings)
		// gcc : __builtin_ctz(toppings);
	}


	// 추가적으로 이런 비트연산 경우에 가독성이 조금 안좋기도 하고,
	// 굳이 불편하다 싶을 떄 사용할 수 있는 여러 함수들이 추가되었다.
	{
		// 엔디안
		int b = 0x11223344;
		// [44 33 22 11] little 엔디안 (작은 주소에서 큰 주소로)
		// [11 22 33 44] big 엔디안 (큰 주소에서 작은 주소로)

		// 네트워크, 파일 입출력
		if (std::endian::native == std::endian::big)
		{
			cout << "big" << endl;
		}
		else
		{
			cout << "little" << endl;
		}

		float n1 = 1.0f;
		int n2 = static_cast<int>(n1); // 1
		int n3 = bit_cast<int>(n1); // 비트로 바꿔주는 캐스팅 (n3의 결과값은 정수로 분석해서 뽑아냈기 때문에 1이 아닌 엉뚱한 값이다.)

		// bit_cast : 새로운 캐스팅 (기존에 4대 캐스팅만 있었다)
		// has_single_bit	: 어떤 숫자가 2^n 형태인지 (2의 거듭제곱)
		// popcount : unsigned int 숫자에서 1의 개수
		// bit_ceil : 해당 값보다 작지 않은 (2의 거듭제곱)중 제일 작은 것 (floor < num < ceil)
		// bit_floor : 해당 값보다 크지 않은 (2의 거듭제곱)중 제일 큰 것 (floor < num < ceil)
		// bit_width : 해당 값을 표현하기 위해 필요한 최소 비트 개수
		// rotl : bitwise left-rotation
		// rotr : bitwise right-rotation
		// countl_zero : 제일 큰 비트부터 시작해서, 연속된 0의 개수
		// countl_one : 제일 큰 비트부터 시작해서, 연속된 1의 개수
		// countr_zero : 제일 작은 비트부터 시작해서, 연속된 0의 개수
		// countr_one : 제일 작은 비트부터 시작해서, 연속된 1의 개수

		std::uint8_t num = 0b00110010;
		cout << boolalpha;

		cout << std::has_single_bit(num) << endl; // false
		cout << popcount(num) << endl; // 3
		cout << std::bitset<8>(std::bit_ceil(num)) << endl; // 0b01000000
		cout << std::bitset<8>(std::bit_floor(num)) << endl; // 
		cout << std::bit_width(5u) << endl; // width(0x000101) = 3
		cout << std::bitset<8>(std::rotl(num, 2)) << endl; // 0b11001000
		cout << std::bitset<8>(std::rotr(num, 2)) << endl; // 0b10001100
		cout << countl_zero(num) << endl; // 2
		cout << countl_one(num) << endl; // 0
		cout << countr_zero(num) << endl; // 1
		cout << countr_one(num) << endl; // 0
	}
}