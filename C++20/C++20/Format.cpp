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

// 오늘의 주제 : Format

int main()
{
	// C에서의 Format String
	// printf("%d + %d = %d입니다", 1, 1, 2);

	// format : 포맷 스트링 반환
	// format_to : 결과를 output iterator에 반환
	// format_to_n : 최대 n개 문자를 output iterator에 반환

	int value = 20;
	cout << format("Hello C++{}", value) << endl;

	string buffer;
	format_to(std::back_inserter(buffer), "Hello C++{}", 20);
	cout << buffer << endl; // Hello C++20

	buffer.clear();
	format_to_n(std::back_inserter(buffer), 5, "Hello C++{}", 20);
	cout << buffer << endl; // Hello

	// 진짜로 { 쓰고 싶으면? {{ 두개를 사용하면 됨.
	cout << format("{{Hello C++{}}}", value) << endl;

	// C#처럼 지정하기도 가능!
	cout << format("{} {} {}", 10, 20, 30) << endl;
	cout << format("{2} {0} {1}", 10, 20, 30) << endl; // 30, 10, 20

	// Fill Character (빈칸 채우는 문자 지정 가능. 기본값은 space)
	// Alignment
	// < : left (숫자가 아니라면 얘가 default)
	// > : right (숫자라면 얘가 default)
	// ^ : center
	int num = 100;
	cout << format("{:10}", num) << endl; // [       100] - 칸이 총 10개 (100을 제외한 빈칸이 총 7개. 숫자라면 기본 정렬이 오른쪽)
	cout << format("{:10}", 'x') << endl; // [x         ] - 칸이 총 10개 (x를 제외한 빈칸이 총 9개. 문자라면 기본 정렬이 왼쪽)
	cout << format("{:*<10}", 'x') << endl; // [x*********] - 왼쪽 정렬로 지정
	cout << format("{:*>10}", 'x') << endl; // [*********x] - 오른쪽 정렬로 지정
	cout << format("{:*^10}", 'x') << endl; // [****x*****] - 중앙 정렬로 지정
	
	// [부호]
	// 정수나 부동소수점에 사용
	// + (양수면 + 붙여라)
	// - (음수면 - 붙여라) << default
	cout << format("{0:}, {0:+}, {0:-}, {0: }", 0) << endl; // 0, +0, 0, 0
	cout << format("{0:}, {0:+}, {0:-}, {0: }", 1) << endl; // 1, +1, 1, 1
	cout << format("{0:}, {0:+}, {0:-}, {0: }", -1) << endl; // -1, -1, -1 ,-1

	// [#]
	// 정수에 대해, 0b, 0, 0x 이진수, 팔진수, 십육진수
	// 0 : pads with leading zeros
	cout << format("{:#015}", 0x78) << endl;
	cout << format("{:#015b}", 0x78) << endl;
	cout << format("{:#015x}", 0x78) << endl;

	// [width / precision]
	// width : {:n} n은 minimum width
	// precision : .에다가 양수 조합 (string이라면 문자개수, float라면 formatting precision)
	int i = 123456789;
	double d = 123.456789;
	cout << "---" << format("{}", i) << "---" << endl;
	cout << "---" << format("{:15}", i) << "---" << endl; // w=15
	cout << "---" << format("{}", d) << "---" << endl;
	cout << "---" << format("{:15}", d) << "---" << endl; // w=15
	cout << "---" << format("{:.50}", d) << "---" << endl; // p=50
	cout << "---" << format("{:.8}", d) << "---" << endl;
	cout << "---" << format("{:.5}", d) << "---" << endl;
	cout << "---" << format("{:.5}", "Hello World") << "---" << endl;

	// [Type]
	// 대부분 컴파일러가 알아서 어떤 타입인지 추론해줌.
	// but! 우리가 직접 지정할 수도 있다!
	// s : string
	// b : binary
	// B : b와 같지만 0B로 시작
	// d : decimal
	// o : octal
	// x : hexadecimal
	// X : x와 같지만 0X로 시작
	// 부동소수점 관련 (e, E, f, F, g, G) : 생략 (지수 표시, 정밀도 등)	
	cout << format("{:}", num) << endl; // 100
	cout << format("{:d}", num) << endl; // 100
	cout << format("{:b}", num) << endl; // 1100100
	cout << format("{:o}", num) << endl; // 144
	cout << format("{:x}", num) << endl; // 64

	// [User Defined Types]
	// std::formatter 클래스를 신규 타입에 대해 특수화
	// - 멤버 함수 parse, format을 구현해야 함.
	// -- BUT ! 아직 버그가 있는 것 같다! 예제를 테스트 해봤는데 C2039 에러 상황 (TODO)
}