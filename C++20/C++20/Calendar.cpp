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

// 오늘의 주제 : Calendar

int main()
{
	// C++11에 추가된 Time 라이브러리
	// - time point
	// - time duration
	// - clock

	// 시간이 왜 그렇게 중요할까?
	// 예를 들어보자면, 서버쪽에서 매일 7시마다 던전이 초기화된다고 가정해보자.
	// 매일 7시니 시간을 판별할 수 있는 수단이 필요할 것이다.
	// 근데 아침 7시 자체가 국가마다 시간이 다 다르다. 
	// 한국 서버를 할 떄랑 유럽 서버를 할 떄랑 현지 몇 시에 있는 시간을 따라갈 것 인지
	// 아니면 글로벌하게 영국시간 기준으로 할 것인지 등 여러 기획사항에 맞물려있어서 작업을 해야할 것이다.
	// 그런것을 일일이 코딩하기엔 복잡하기에 시간과 관련된 라이브러리를 사용한다. (또 이벤트라던가 누적된 보너스 등등)
	
	// C++20에서 추가되고, 개선이 되었다.
	{
		// hh_mm_ss : duration since midnight, split into hours, minutes, seconds, fractional seconds
		// C++11 chrono
		// C++20 calendar, time_zone
	}

	auto timeOfDay = std::chrono::hh_mm_ss(10.5h + 32min + 1004s + 0.6s);
	cout << timeOfDay << endl;
	cout << timeOfDay.hours() << endl;
	cout << timeOfDay.minutes() << endl;
	cout << timeOfDay.seconds() << endl;
	cout << timeOfDay.subseconds() << endl;
	cout << timeOfDay.to_duration() << endl;

	// Calendar Date
	using namespace chrono;
	chrono::year_month_day ymd1{ year(2021), month(11), day(14) };
	chrono::year_month_day ymd2{ year(2021) / month(11) / day(14) };
	chrono::year_month_day ymd3{ 2021y, November, 14d }; // 컨벤션이 정해져있어서 이런식으로도 가능.
	cout << ymd1 << endl;

	// year/month/day
	// day/month/year
	// month/day/year
	std::chrono::year_month_day_last ymdl1 = 2021y / November / last;
	std::chrono::year_month_day_last ymdl2 = last / November / 2021y;
	std::chrono::year_month_day_last ymdl3 = November / last / 2021;
	auto d1 = ymdl1.day();
	chrono::year_month_day ymd4{ ymdl1 };

	std::chrono::year_month_weekday ymwkd1{ year(2021) / November / Friday[4] };
	chrono::year_month_day ymd5{ ymwkd1 };

	// timepoint
	time_point timePoint = chrono::sys_days(ymd1);

	// Cute Syntax (예약된 키워드)
	// 2021y, 30d, January, February, ... December

	// Validation
	std::chrono::day d{ 31 };
	d++; // 오퍼레이터 되어있음
	bool valid = d.ok(); // 유효한 날짜인지 체크

	auto leapYear2000{ year(2000) / 2 / 29 };
	auto leapYear2001{ year(2001) / 2 / 29 };
	auto leapYear2002{ year(2002) / 2 / 29 };

	bool valid2 = leapYear2000.ok(); // true
	bool valid3 = leapYear2001.ok(); // false
	bool valid4 = leapYear2002.ok(); // false

	// A날짜와 B날짜 사이의 시간차를 구할수도 있다.
	auto now = std::chrono::system_clock::now();
	auto diff = floor<chrono::hours>(now) - sys_days(1987y / January / 30d);
	cout << diff << endl;

}