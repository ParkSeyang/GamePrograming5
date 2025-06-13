#include <iostream>
#include <vector>
#include <algorithm>

/*
* nums �迭���� �׽�Ʈ ���̽��� ���´�.
* nums vector�� 1,3,8,2,9... ������ ������ ���ɴϴ�.
* �� ���ڸ� ������������ �����غ�����. �� ������ ���� answer�� �����ؼ� ��ȯ�ϼ���.
*/

/*
* �ڵ带 ���� �� �ִ�. =  �� ���� �˰��� �ڵ尡 �����Ѵ�.
* �ð� ���⵵, ���� ���⵵.
* �ּ� : �ڵ尡 ������ ������ ���� ����ϴ� �ڵ�.
* �ð��� ������ ������ �����ϰ�, �ð��� ������ ������ �� ����ϴ� ��찡 ����.
*/

/*
* O(1), O(log n), O(n) O(n^2)
* 
* ���� ū ������
* 
* n�� ũ��    |   1   |   10  |    100    |    1000    |    1000,000
* O(1)       	  1  |     1  |      1   |      1     |        1
* O (log n)		  0  |     1  |      2   |      3     |        6
* O(n)			  1  |    10  |    100   |    1000    |    1000,000
* O(n^2)		  1  |        |          |            |         
* 
* ���� : ��κ��� �˰��� ������ �׽�Ʈ ���̽��� ������ ���� ��츦 �����Ѵ�.
*/

/*
* �ð� ���⵵�ε� �� ���� �ð��� ���ϴ� ���� �ƴ϶� ���� Ƚ���� ���ұ��?
* - ȯ�濡 ���� ��� ���� �޶�����.
* - ���� Ƚ���� ������ ���� ���� ū ������ �񱳸� ����.
* - O(n) ��� ǥ���
*/

#pragma region �ð� ���⵵ ����ϱ�

void Test1()
{
	// 1 ~ 5������ ���ڸ� ���� ���� ���� ����ϼ���.
	// int sum ����. for �ݺ����� ����ؼ� sum�� �����غ�����.

	int sum = 0;   // int�� Ÿ���� sum�� �� 0�� �Ҵ� ���� 1��
	
	int n = 0;
	std::cin >> n;

	for (int i = 1; i < 6; i++)
	{
		sum += i;  // 5�� ����
	}

	// �ڵ��� ���� Ƚ�� : n + 3

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sum += i * j;     // ��� ����? n * n
		}
	}
	// �ڵ��� ���� Ƚ�� : N^2 + n + 3


}

#pragma endregion



std::vector<int> solution(std::vector<int> nums)
{
	std::vector<int> answer;
	std::sort(nums.begin(), nums.end());   // STL�� �����Ǿ� �ִ� ������ ����ϰڴ�.
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

// ���ĵǾ� ���� ���� ���ڸ� �迭�� �޾ƿͼ� �� ���� �����ϴ� �Լ��� ����� ������.

// ���� ����, ���� ����, ���� ����

#pragma region ��������

// ������ ���������� �ð��� ���� �ɸ��� �����Դϴ�.
void bubblesort(int arr[], int n)
{

	// ����Ŭ�� �� �� ���ƾ� �ϴ°�?
	for (int i = 0; i < n - 1; i++)   // �ݺ�Ƚ�� n - 1�� ��ŭ
	{
		for (int j = 0; j < n - i - 1; j++)                // j, i , 3���� ǥ���Ϸ��� ��� �ؾ��ұ�?
		{
			// swap�� ���� ����
			if (arr[j] > arr[j + 1])  // ���� ���Ұ� �ٷε��� ������ ũ��.. ���� ���� �ٲ��.
			{
				// swap�� �����ϼ���.

				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
	// ����Ŭ ���� ������ �ؾ��ϴ°�?
	// 1. �迭��� ���� �񱳸��Ѵ�.
	// 2.(K��°) (k + 1) ū��� �迭 ��Ҹ� �����Ѵ�.
	
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}

}

// �ð� ���⵵ : O(n^2)
// �������� : �ּ�(O(n)), �־�(O()), ���(O())

void bubblesort2(std::vector<int> nums)
{
	
	int n = nums.size();

	for (int i = 0; i < n - 1; i++)   // �ڱ� �ڽŰ��� �񱳸� ���ص� �Ǽ� -1 ����Ŭ ���� ���� ū���� ��������.
	{
		for (int j = 0; j < n - i - 1; j++)  // �� ����Ŭ ���� ���ϴ� Ƚ��, ����Ŭ ���� �پ���.
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

#pragma region ���� ����
// ���� ���� ���� ����.
// �� �տ� ������ ����� �����Ѵ�.
// ����Ŭ ���� ���� ���� ���� ����� ��ġ�� ã�ƾ� �մϴ�.
// 
// �ð� ���⵵ : O(n^2) O(n)

// Min()�Լ�. ��ü�迭 �߿��� ���� ���� ���� ��ȯ�ϴ� �Լ�.

void SelectionSort(int arr[], int n)
{
	// �� �� ����Ŭ ���ƾ� �ұ��?
	for (int i = 0; i < n-1; i++)
	{
		int min_idx = i;

		// for �ݺ��� ǥ��, j�� �� i + 1
		for (int j = i + 1; j < n; j++)
		{
			// arr[min_idx] arr[j]�� ���ؼ� ������ �ʰ� �ּҰ�
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
	// arr[j]�� ����, ���� ���� ��(Index) arr[min]

	// swap arr[��] arr[min]

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

#pragma region ���� ����

#pragma endregion


int main()
{
	
	std::cout << "\n�������� �ڵ� ���� " << std::endl;

	int arr[5] = {5,4,1,3,2};
	int n = 5;

	//bubblesort(arr, n);

	std::cout << "\n�������� �ڵ� ����2 " << std::endl;

	std::vector<int> nums = {1,4,5,3,2};

	bubblesort2(nums);
	

	std::cout << "\n �������� �ڵ� ���� " << std::endl;

	int ary1[5] = { 9,8,7,6,5 };
	int s = 5;

	SelectionSort(ary1, s);

	std::cout << "\n �������� �ڵ� ����2 " << std::endl;

	std::vector<int> nums2 = { 5,4,3,2,1 };

	SelectionSort(nums2);

	// Execute();
	
}