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

// 오늘의 주제 : Container #2 (erase, erase_if)

int main()
{
	// 좀 중요한 개념.
	// C++을 사용했으면 누구나 한번쯤은 STL 컨테이너의 삭제에 대해 불편한 점을 느껴봤을 것이다.

	// ex) 기존 방식대로 음수를 삭제해보자.
	{
		vector<int> vec{ -1, 2, -3, 4, -5 };

		// 기존 방식
		{	
			// 밑에 삭제코드는 STL을 많이 안접해본 사람이 작성할 수 있는 코드로써
			// 처음보면 잘 삭제가 되지 않을까? 라는 생각이지만,
			// 많이 겪어본 사람들은 C++의 엄청난 함정 이라는 것을 알고있다.
			for (auto it = vec.begin(); it != vec.end(); it++)
			{
				int value = *it;
				if (value < 0)
				{
					vec.erase(it);
				}
				else
				{

				}
			}

			// 공식
			for (auto it = vec.begin(); it != vec.end();)
			{
				int value = *it;
				if (value < 0)
				{
					it = vec.erase(it); // 삭제되면 다음 iterator를 받아줘야하고, 한 개만 삭제할거면 break문을 걸어 빠져나온다.
				}
				else
				{
					++it; // for문의 ++은 iterator가 삭제되지 않았을 때만 한다. erase 하면 다음 iterator를 가리키기 때문.
				}
			}

			for (auto num : vec)
				cout << num << endl;
		}

		
		// 위의 방식들은 너무 지저분하다.
		// 다른 프로그래머들이 수정하다가 버그를 일으킬 수 도 있고, 가독성이 너무 안좋다.
		// 조금 나은 방식으로는 algorithm 함수를 이용.
		{
			std::remove_if(vec.begin(), vec.end(), [](int num) { return num < 0; });
			// 하지만 결과는 매우 이상하다. (2, 4, -3, 4, -5)
			// remove_if도 함정이다. 이름부터가 함정.
			// if를 만족하면 삭제하겠다 가 아니라, 단지 이동시켜주는 기능이다.
			// 삭제되면 안되는 애들만 복사해서 앞으로 덮어쓰고, 나머지 애들은 그냥 놔두기 때문에 값이 이상하게 나온 것.

			// 그래서 해결법은 remove_if가 뱉어주는 이터레이터 결과물을 받아주고, erase로 end까지의 범위를 삭제해줘야 정상적으로 된디.
			// 이것도 매우 불편하다.
			auto newEnd = std::remove_if(vec.begin(), vec.end(), [](int num) { return num < 0; });;
			vec.erase(newEnd, vec.end());
		}

		// C++20 erase, erase_if
		// 지저분한 방식들을 해결해주는 기능이 추가됐다. (가독성이 매우 좋음)
		{
			std::erase(vec, 2);
			std::erase_if(vec, [](int num) { return num < 0; });
		}
	}

}