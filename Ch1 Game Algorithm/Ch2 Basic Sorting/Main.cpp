#include <iostream>
#include <vector>
#include <algorithm>

/*
* nums 배열에는 테스트 케이스가 들어온다.
* nums vector에 1,3,8,2,9... 랜덤한 정수가 들어옵니다.
* 이 숫자를 오름차순으로 정렬해보세요. 그 정렬한 값을 answer에 저장해서 반환하세요.
*/

/*
* 코드를 평가할 수 있다. =  더 좋은 알고리즘 코드가 존재한다.
* 시간 복잡도, 공간 복잡도.
* 최선 : 코드가 빠르고 공간도 적게 사용하는 코드.
* 시간이 빠르면 공간이 복잡하고, 시간이 느리면 공간을 덜 사용하는 경우가 많다.
*/

/*
* O(1), O(log n), O(n) O(n^2)
* 
* 가장 큰 차수만
* 
* n의 크기    |   1   |   10  |    100    |    1000    |    1000,000
* O(1)       	  1  |     1  |      1   |      1     |        1
* O (log n)		  0  |     1  |      2   |      3     |        6
* O(n)			  1  |    10  |    100   |    1000    |    1000,000
* O(n^2)		  1  |        |          |            |         
* 
* 정리 : 대부분의 알고리즘 문제는 테스트 케이스의 갯수가 많은 경우를 상정한다.
*/

/*
* 시간 복잡도인데 왜 실행 시간을 비교하는 것이 아니라 실행 횟수를 비교할까요?
* - 환경에 따라서 결과 값이 달라진다.
* - 실행 횟수를 식으로 만들어서 가장 큰 차수로 비교를 하자.
* - O(n) 빅오 표기법
*/

#pragma region 시간 복잡도 계산하기

void Test1()
{
	// 1 ~ 5까지의 숫자를 전부 더한 값을 출력하세요.
	// int sum 변수. for 반복문을 사용해서 sum에 저장해보세요.

	int sum = 0;   // int형 타입의 sum의 값 0을 할당 실행 1번
	
	int n = 0;
	std::cin >> n;

	for (int i = 1; i < 6; i++)
	{
		sum += i;  // 5번 실행
	}

	// 코드의 실행 횟수 : n + 3

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sum += i * j;     // 몇번 실행? n * n
		}
	}
	// 코드의 실행 횟수 : N^2 + n + 3


}

#pragma endregion



std::vector<int> solution(std::vector<int> nums)
{
	std::vector<int> answer;
	std::sort(nums.begin(), nums.end());   // STL로 구현되어 있는 정렬을 사용하겠다.
	answer = nums;
	return answer;
}

void Execute()
{
	std::vector<int> nums = { 5,1,3,4,2 };
	auto v = solution(nums);
	for (auto& elem : v)
	{
		std::cout << elem << "  ";
	}

}

// 정렬되어 있지 않은 숫자를 배열로 받아와서 그 수를 정렬하는 함수를 만들어 보세요.

// 버블 정렬, 선택 정렬, 삽입 정렬

#pragma region 버블정렬

// 구현은 간단하지만 시간이 오래 걸리는 정렬입니다.
void bubblesort(int arr[], int n)
{

	// 사이클이 몇 번 돌아야 하는가?
	for (int i = 0; i < n - 1; i++)   // 반복횟수 n - 1번 만큼
	{
		for (int j = 0; j < n - i - 1; j++)                // j, i , 3번을 표현하려면 어떻게 해야할까?
		{
			// swap을 위한 정의
			if (arr[j] > arr[j + 1])  // 왼쪽 원소가 바로뒤의 값보다 크면.. 서로 값을 바꿔라.
			{
				// swap을 실행하세요.

				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
	// 사이클 마다 무엇을 해야하는가?
	// 1. 배열요소 끼리 비교를한다.
	// 2.(K번째) (k + 1) 큰경우 배열 요소를 변경한다.
	
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}

}

// 시간 복잡도 : O(n^2)
// 버블정렬 : 최선(O(n)), 최악(O()), 평균(O())

void bubblesort2(std::vector<int> nums)
{
	
	int n = nums.size();

	for (int i = 0; i < n - 1; i++)   // 자기 자신과는 비교를 안해도 되서 -1 사이클 마다 가장 큰수가 정해진다.
	{
		for (int j = 0; j < n - i - 1; j++)  // 각 사이클 마다 비교하는 횟수, 사이클 마다 줄어든다.
		{
			if (nums[j] > nums[j + 1])
			{
				std::swap(nums[j], nums[j + 1]);
			}
		}
	}

	for (int n : nums)
	{
		std::cout << n << " ";
	}


}

#pragma endregion

#pragma region 선택 정렬
// 가장 작은 수를 선택.
// 맨 앞에 보내는 방법을 정렬한다.
// 사이클 마다 가장 작은 수가 저장된 위치를 찾아야 합니다.
// 
// 시간 복잡도 : O(n^2) O(n)

// Min()함수. 전체배열 중에서 가장 작은 값을 반환하는 함수.

void SelectionSort(int arr[], int n)
{
	// 몇 번 사이클 돌아야 할까요?
	for (int i = 0; i < n-1; i++)
	{
		int min_idx = i;

		// for 반복문 표현, j의 값 i + 1
		for (int j = i + 1; j < n; j++)
		{
			// arr[min_idx] arr[j]와 비교해서 작으면 너가 최소값
			if (arr[min_idx] > arr[j])
			{
				min_idx = j;
			}
		}
		if (i != min_idx)
		{
			std::swap(arr[i], arr[min_idx]);
		}
	}
	// arr[j]의 값과, 가장 작은 값(Index) arr[min]

	// swap arr[값] arr[min]

	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}

}

void SelectionSort(std::vector<int> nums)
{
	int n = nums.size();

	for (int i = 0; i < n - 1; i++)
	{
		int min_idx = i;
		for (int j = )
		{

		}
	}

}

#pragma endregion

#pragma region 삽입 정렬

#pragma endregion


int main()
{
	
	std::cout << "\n버블정렬 코드 예시 " << std::endl;

	int arr[5] = {5,4,1,3,2};
	int n = 5;

	//bubblesort(arr, n);

	std::cout << "\n버블정렬 코드 예시2 " << std::endl;

	std::vector<int> nums = {1,4,5,3,2};

	bubblesort2(nums);
	

	std::cout << "\n 선택정렬 코드 예시 " << std::endl;

	int ary1[5] = { 9,8,7,6,5 };
	int s = 5;

	SelectionSort(ary1, s);

	std::cout << "\n 선택정렬 코드 예시2 " << std::endl;

	std::vector<int> nums2 = { 5,4,3,2,1 };

	SelectionSort(nums2);

	// Execute();
	
}