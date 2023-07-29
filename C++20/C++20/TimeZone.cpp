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

// 오늘의 주제 : Time Zone

// 서버프로그래머 입장에서 은근히 중요한 주제
// 서버는 시간과 많이 관련되어 있기 때문에.

using namespace std::chrono;

int main()
{
	// 온라인 게임 (한국/북미/유럽)
	// 프랑스/독일/러시아/영국/... - 각 나라마다 시차가 존재한다.
	// ex) 와우 - 오전 6시에 던전/일일퀘 리셋 등 나라별로 기준이 다름.
	// DB 시간 저장할 때? 로컬 시간? UTC 시간?

	// UTC (Coordinated Universal Time 협정 세계시) <-> Local Time (실행 환경)
	// UTC와 Local Time은 서로 반대의 개념
	// Local Time은 말그대로 한국에서 켰으면 한국 시간, 프랑스에서 켰으면 프랑스 시간.
	// UTC는 어느 국가에서 실행했던 상관없이 동일하게 같은 시각을 바라본다.
	// 근데 모든 시간을 동일하게 한다고 하면 기준점이 있어야하는데, 그 기준점은 영국
	 
	// - 영국은 UTC+0.00 (Greenwich Mean Time, GMT) UTC과 곧 GMT 개념인셈.
	// - 한국은 UTC+9.00 (GMT 기준 9시간을 더함)
	// - 뉴욕은 UTC-5:00 (GMT 기준 5시간을 뺌)
	// 결과적으로 DB에다가 영국시간 기준으로 저장할 것이고,
	// 서버에서 연산할 때도 영국시간 기준으로 연산한다.

	// 이렇게 해야되는 이유는 한국 DB에다가 한국 로컬시간 기준으로 저장했다고 가정하면,
	// 한국 단일서버로 한국에서만 접속한다고 했을 때, 문제 없겠지만
	// 유럽 서버 기준으로 DB를 저장한다고 했을 때, 프랑스/독일/러시아 등등 각각 기준이 다르기 때문에 문제라는 것.
	// 그래서 공용시간을 하나로 관리해서 Local Time을 UTC로 변환한 다음에 사용하는 것.

	cout << "UTC" << endl;
	auto utcTime = system_clock::now();
	cout << utcTime << endl;

	// 서버(C++) <-> 클라(C#. Unity)  를 사용한다고 가정하자.
	// 서버에서는 어떤 활동에 대한 리셋시간을 보내준다고 했을 때, UTC 시간을 기준으로 맞춰 보내줄텐데,
	// 지금 활용하고 있는 코드는 C++ 전용 클래스이다 보니, C#을 사용하는 클라에게 보내주기 애매할 수 있다.
	// 그럴 때, 활용하는 기준은 유닉스 시간이다.
	//   
	// UNIX Epoch (유닉스 시간) - 위키피디아
	// 유닉스 시간(영어: Unix time)은 시각을 나타내는 방식이다. 
	// POSIX 시간이나 Epoch 시간이라고 부르기도 한다. 
	// 1970년 1월 1일 00:00:00 협정 세계시(UTC) 부터의 경과 시간을 초로 환산하여 정수로 나타낸 것이다.
	__int64 hoursSinceUtc = duration_cast<hours>(utcTime.time_since_epoch()).count();
	cout << "Hours : " << hoursSinceUtc << endl;
	__int64 utcEpoch = duration_cast<seconds>(utcTime.time_since_epoch()).count();
	cout << "Epoch : " << utcEpoch << endl;

	// 시간과 관련된 부분들이 예전에 C++ 표준에 없어서,
	// 윈도우, 리눅스 등 각각 환경에 따라 API가 제공하는 시간 함수들을 이용해서 시간을 조립을 했는데,
	// C++20에 가면서 확립이 되어 기능이 생겼다,
	cout << "Local" << endl;
	// C++20에 추가된 기능 - 현재 컴퓨터로 띄우는 로컬에 세팅되어 있는 시간을 기준으로 Local Time을 계산해줌.
	auto localTime = zoned_time(current_zone(), utcTime); // 한국이라면 한국 기준
	auto localTime2 = zoned_time("Asia/Shanghai"s, utcTime); // 다른 나라도 직접 지정 가능
	cout << localTime2 << endl;

	auto offset = localTime.get_info().offset; // GMT와 몇 시간 차이나는지
	cout << offset << endl;
}