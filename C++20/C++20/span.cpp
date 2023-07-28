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

// 오늘의 주제 : std::span

void PrintArray(int* arr, int len)
{
	cout << "array size() = " << len << endl;
	for (int i = 0; i < len; i++)
		cout << arr[i] << endl;
}

void Print(std::span<int> container)
{
	// 방식이 vector와 유사하다.
	cout << "container size() = " << container.size() << endl;
	for (int i = 0; i < container.size(); i++)
		cout << container[i] << endl;
}

int main()
{
	// std::span = C배열, std::array, std::vector, std::string 등의
	// 연이은 객체 시퀀스 (contiguous sequence of objects)를 참조(refer)

	// span을 쓰는 이유
	{
		// C타입 배열
		// 배열의 길이를 알려면 배열의 크기를 알아야 길이를 알 수가 있었다.
		int arr[] = { 1,2,3,4,5 };
		const int size = sizeof(arr);
		const int len = sizeof(arr) / sizeof(int);

		// 함수 인자인 arr은 포인터여서, 사실상 배열의 정보는 모르고 단지 주소값만 넘기기 떄문에, 
		// 항상 길이도 넘겨야 그 안에서 배열을 활용할 수 있었다.
		// 또한 len이 5개가 아닌 임의로 10개든 큰 수로 넣게된다면 참조의 영역이 아니게 돼서 오버플로우 문제가 일어난다.
		PrintArray(arr, len); 

		// 그럼 함수 인자를 배열로 하거나 타입을 넘어오는 데이터에 맞춰서 하면 되지 않느냐? 라고 생각할 수 있는데.
		// 당연히 그렇게도 해도 되지만, 유연하게 사용하기 위함이고 하나의 타입에 맞춘 의존적인 코드를 보완하기 위함이다.
		// 호환성이 좋아짐.
		Print(arr);
	}

	// <type T, size_t Extent = dynamic_extent>
	// std::span
	// - static_extent = 컴파일 타임에 크기가 정해짐 (배열같은 애들)
	// - dynamic_extent = 반대로, 컴파일 타임에 정해지지 않는 것 (vector 같은 동적 배열들)
	// Print 함수를 보면 만약 인자가 vector로 설정되어 있을 때, vector는 데이터를 복사해서 넘겨준다고 하면 
	// span은 포인터 + 크기만 넘겨준다. 포인터의 시작 주소와 데이터의 개수 두가지 정보를 이용해서 사실상 참조를 하고있다.

	// span은 vector의 인터페이스와 유사하게 만들어져서 vector의 문법처럼 사용해도 된다.

	vector<int> myVec{ 1,2,3,4,5 };
	vector<int> myVec2{ 6,7,8,9,10 };

	std::span<int> dynamicSpan(myVec); // 동적
	std::span<int, 5> staticSpan(myVec2); // 정적으로 크기(5)를 정해줌

	Print(dynamicSpan);
	Print(staticSpan);

	dynamicSpan = staticSpan;
	//staticSpan = dynamicSpan; // ERROR (고정적인 크기인데, 가변적인 길이를 덮여쓸려고 하니 에러)

	// 포인터/사이즈를 이용해서 span 생성
	std::span<int> span1(myVec.data(), myVec.size());
	Print(span1);

	// 부분적으로 잘라서 만들기
	std::span<int> span2(span1.subspan(1, span1.size() - 3));
	Print(span2);

	// 다시 얘기하지만, 밑에는 myVec의 데이터를 하나하나씩 복사해서 새로운 vector를 만드는 개념인데,
	// span은 원본 데이터는 그대로있고, 영역을 찝어준다고 생각하면 된다.
	// 실질적으로 내부적으론 시작주소랑 데이터 개수 두가지 정보를 이용해 판별하는 것.
	vector<int> vec3(myVec.begin(), myVec.end());

	// 1~2 범위 대상으로, 4함수 실행한 다음, 3에 기록
	std::transform(span1.begin(), span1.end(), span1.begin(), [](int i) { return i * i; });
	Print(span1);
	Print(myVec); // 원본 데이터가 수정됨! (다시 말하지만, 복사 개념이 아닌 원본 데이터 영역을 찝어주는 개념이기 때문)


}