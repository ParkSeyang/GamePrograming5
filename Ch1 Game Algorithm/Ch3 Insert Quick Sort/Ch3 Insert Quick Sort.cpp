#include <iostream>
#include <vector>
#include <algorithm>

/*
* 삽입 정렬
* - 특정 수를 정렬된 위치로 옮기는 방식
* - 앞에서 부터 데이터를 정렬한다.
*/

void InsertSort(int arr[], int n)
{
    // 몇 번 cycle을 돌아야 하나요?

    for (int i = 1; i < n; i++)
    {
        // 현재 key의 값이 무엇인가?

        int key = arr[i];

        // key의 값 이전의 값 들과 비교를하라.

        int j = i - 1;

        // while() 조건이 true 일때 중괄호 {} 코드를 실행하라.

        while (j >= 0 && arr[j] > key) // 인덱스의 값이 0보다 작을 때 또는 j 값 보다 key 값이 클 때 
        {
            arr[j + 1] = arr[j]; // 왼쪽의 데이터와 새로 들어온 데이터의 위치를 변경해라.
            j--; // 현재 key 의 위치
        }

        arr[j + 1] = key;
    }

}

void InsertSort(std::vector<int>& nums)
{
    // 몇 번 cycle을 돌아야 하나요?
    
    int n = nums.size();

    for (int i = 1; i < n; i++)
    {
        // 현재 key의 값이 무엇인가?
        int key = nums[i];
        
        // key 왼쪽에 있는 모든 데이터들과 비교해서 위치를 찾은 다음에 그 위치에 삽입.
       
        int index = i - 1;

        while (index >= 0 && nums[index] > key)  // j의 값이 0보다 크거나 같을 때만 또는 key의 값이 왼쪽에 있는 값보다 작을 때만
        {
            // 작으면 왼쪾과 키에 들어있는 값을 변경하고
            // index를 왼쪽으로 이동해서 다음 수와 또 비교한다.
            nums[index + 1] = nums[index];

            index--;
        }
        nums[index + 1] = key;
    }

    // 위치를 찾으면 해당 위치에 key를 저장하라.
}

/*
* 장점 : 모든 경우에 위치 변경이 발생하는 것이 아니라, while 조건에 해당 할 때만 위치 변경(swap)이 발생한다.
* 컨테이너 데이터가 정렬되어 있을 수록 정렬 속도가 빠르다.
* 사이클 : n
* while() 1 ~ n 크기를 가질 수 있다.
* 시간 복잡도
* - 최선의 경우 O(n) 평균, 최악의 경우 (O(n^2))
* 
* 단점 : n의 제곱에 비례해서 시간이 걸린다.
*/

/* 잡상식!
* log 시간이 얼마나 빠를까?
* 2^10 = 1024 // 대략 1000
* 2^20 * 2^10 // 1,000,000 대략 백만
* log2(2^20) = 20;   n번(백만 번) log n번 (20번)
* 
* 시간을 단축하게 하기 위해서는 logn으로 표현하는 방법을 찾는다.
* 그 방법이 바로 "분할 정복" 알고리즘
* 
*/

#pragma region 퀵 정렬

/*
* 임의의 pivot을 정한다. 가장 왼쪽의 값을 피벗으로 한다.
* pivot : 기준점
* 분할 정복 알고리즘. 분할을 하기위한 기준이다.
* 특징 : 분할 정복 알고리즘을 사용하고 있다. 재귀 함수로 구현된다.
* 시간복잡도
* 평균 O(N * logn) 시간을 갖는다.
* O(n^2) 정렬 방식으로 알고리즘을 구하세요. (버블, 선택, 삽입)
* O(n log n) 정렬 방식으로 알고리즘을 구하세요. (퀵, 병합)
*/

/*
* 언제 사용하는가? data의 갯수가 10만 개가 넘어갈때, 10만 X 10만 = 10 ~ 몇 백억 0.00001 * 10억
* 데이터의 개수가 많을 때 사용한다.
* 
* 단점 : 정렬되어 있는 데이터에서 quickSort를 사용할 경우 O(n^2) 시간이 걸린다.
* 알고리즘 문제에 quickSort 구현했을 때 시간이 초과했다 -> 정렬되어 있는 케이스를 받을 때 비효율적이다.
*/

// 퀵정렬 배열로 만든 예제
void quickSort(int data[], int start, int end)
{
    if (start >= end)  // 데이터가 1개만 있을 때, 재귀 함수를 끝내기 위한 조건 return으로 표현
    {
        return;
    }
    int pivot = start;     // 기준이 되는 값
    int left = start + 1;  // 왼쪽에서 변경할 위치
    int right = end;       // 오른쪽에서 변경할 위치
    int temp;              // swap 사용하기 위한 임시 변수

    while (left <= right) // 왼쪽 인덱스를 오른쪽 인덱스가 추월 했을 때 까지 반복
    {
        while (data[left] <= data[pivot]) // pivot 보다 큰 값을 만날때 그 값을 찾아라 
        {
            // 작을 때 계속 left를 증가시켜라
            left++;
        }
        while (right > start && data[right] >= data[pivot] ) // pivot 보다 작은 값을 만날 때 그 값을 선택해라
        {
            // 클때 계속 right을 감소시켜라
            right--;
        }

        // left > right 왼쪽 인덱스가 오른쪽 인덱스 보다 크면 (엇갈렷다.)
        if (left > right)
        {
            temp = data[right];
            data[right] = data[pivot];
            data[pivot] = temp;
           // std::swap(data[pivot], data[right]);
        }
        else
        {
            temp = data[right];
            data[right] = data[left];
            data[left] = temp;
            // std::swap(data[left], data[right]);

        }

        // 재귀 함수

        // quickSort( 왼쪽파트 ), quickSort( 오른쪽파트 )
        quickSort(data, start, right-1 );  // 왼쪽
        quickSort(data, right + 1, end);  // 오른쪽



    }


}

// 퀵정렬 벡터로 만든 예제
void quickSort(std::vector<int> nums2, int start, int end)
{

}

#pragma endregion


int main()
{
    std::cout << "삽입 정렬 배열 형식" << std::endl;

    int arr1[10] = { 3,5,9,1,2,4,6,8,7,0 };

    InsertSort(arr1, 10);
    
    for (int i = 0; i < 10; i++)
    {
        std::cout << arr1[i] << " ";
    }

    std::cout << "\n\n삽입 정렬 vector 형식" << std::endl;

    std::vector<int> arr2= { 7,2,3,4,9,5,8,1,6,0 };

    InsertSort(arr2);

    for (int num : arr2)
    {
        std::cout << num << " ";
    }

    std::cout << "\n\n퀵 정렬 vector 형식" << std::endl;

    int arr3[10] = { 3,5,9,1,2,4,6,8,7,0 };

    quickSort(arr3, 0, 9);

    for (int i = 0; i < 10; i++)
    {
        std::cout << arr3[i] << " ";
    }

    std::cout << "\n\n퀵 정렬 vector 형식" << std::endl;


}
