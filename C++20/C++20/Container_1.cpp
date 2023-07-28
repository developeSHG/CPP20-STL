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

// 오늘의 주제 : Container #1

// 1. vector, string 등에 constexpr 사용 가능
// algorithm 100개 이상의 함수들이 constexpr로 바뀜 (함수들이 컴파일 타임에 연산이 될 수 있다 라는 개념)
constexpr int Test()
{
	// C++20 이전에는 이 코드는 당연히 런타임에 만들어지는 코드다보니 
	// 컴파일 타임에 함수의 결과물이 결정될 수 없었다. 
	std::vector<int> v{ 1,4,5,2,3 };
	std::sort(v.begin(), v.end());                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
	return v.back();
}

// 2. std::array 만드는 방법이 추가됨 (std::to_array)

// 3. std::make_shared로 shared_ptr 배열 생성

template<typename T>
struct ArrayDeleter
{
	void operator()(const T* ptr)
	{
		delete[] ptr;
	}
}

int main()
{
	// 1번
	{
		constexpr int ret = Test(); // 컴파일 타임에 값이 결정됨.

		enum
		{
			VALUE = ret // ret가 컴파일 타임에 결정되었기 때문에, enum 타입도 에러없이 통과된다.
		};
	}
	
	// 2번
	{
		// 만약 동적으로 배열의 사이즈가 왔다갔다 변하는 게 아니라, 고정적인 크기를 가진다면
		// vector 보다, array를 쓰는 것이 좋다. (용량을 체크해서 다른 메모리 침범하는 걸 막아주기 때문)
		// 하지만, C++ 스타일의 배열(int* arr)을 이용하게 될 경우에는, 메모리 관리 상 위험할 수 있으니
		// 이왕이면 std::array를 쓰는 게 낫다.
		// 근데 여태 편리하게 만드는 방법이 없었는데, to_array를 이용해 편하게 만들 수 있다.
		auto arr1 = std::to_array("Hello World"); // 16개짜리 배열
		auto arr2 = std::to_array<int>({ 1,2,3,4,5 });
	}

	// 3번
	{
		// 고전적인 방식은 할당을 하면 메모리 릭이 나지않게 소멸을 시켜줘야 헀고,
		// 배열의 경우는 []를 붙여서 소멸시켜줘야 한 게 표본.
		int* arr3 = new int[10];
		delete[] arr3;

		// 위랑 다르게 shared_ptr로 관리하고, 그것을 배열로 한다고 하면
		// delete[] 방식으로 삭제해야 하는데, 기존에 shared_ptr에서는 그런 처리가 되지 않았다.
		std::shared_ptr<int> sp(new int[10]);

		// 정상적으로 삭제가 안되었는데, 기존에 있던 기능으로 
		// 원한다고 하면 어떻게 삭제할지를 추가적으로 넣는 생성자가 있었다.
		// (템플릿을 이용하건 람다를 이용하건)
		std::shared_ptr<int> sp(new int[10], ArrayDeleter<int>());

		
		// 하지만 위 방법도 너무나도 귀찮다.
		// 그래서 C++20에선 배열을 받아주는 버전이 생겼다.
		std::shared_ptr<double[]> shared_arr = std::make_shared<double[]>(1024);
		shared_arr[1] = 1.0;

		// 하지만, 굳이 shared_ptr로 동적배열을 만들어서 사용할까? 십다.
		// 그럴거면 차라리 vector로 shared_ptr을 만들지.
	}

	// 결론은 2, 3번은 굳이 활용할까 싶고, 1번이 속도를 올려주는 면에서 가장 중요한 것 같다.
}