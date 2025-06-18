#include <iostream>
#include <vector>
#include <utility>

/*
* ※ 정렬을 다양한 방법으로 직접 구현 ※
* 왜 정렬을 해야하는가?
* 새로운 아이템(Item) 컨테이너 추가될 때 
* 정렬되어 있는 상태로 저장이 되는 경우가 있다.
*/

/*
* 탐색 : 컨테이너 안에 데이터가 있는지 없는지 찾는다.
* 탐색을 프로그래밍 코드로 한번 구현해보자.
* (1) 앞에서 부터 데이터를 비교해서 있는지 없는지 확인
* - 선형 탐색 방법(Linear search)
* (2) 이진 탐색 (Binary search)
* - 컨테이너가 정렬되어 있을 때 중앙 값을 기준으로 데이터를 나누어서 찾는 방법.
*/

/* 선형 탐색 의 경우(시간 복잡도)
* 최선의 경우 (Best case) O(1)의 시간이 걸리고 최악의 경우(worst case) O(n)의 시간이 걸립니다.
* 평균 O(n) 시간이 걸린다. 데이터의 갯수가 백만을 넘어가면 비효율적이겠다.
* "분할 정복 알고리즘" : 범위를 나누어서 작은 범위를 해결하는 방식으로 문제를 푼다.
*/

/* std::pair 선언하는 방법
* - std::pair<int, 클래스 이름>
* ex) std::pair<int, std::string> e;
* 
* // pair 타입 선언하는 방법
* std::vector<std::pair<int, std::string>> data;
* 
* data.push back({0, "AAA"}); 0~5
* // 해당 하는 인덱스가 있으면 그 인덱스에 저장되어 있는 문자를 출력하는 코드 만들기.
* 
* // 유저의 ID에 유저가 가진 정보를 저장합니다. 서버에 유저의 ID를 기준으로 해당 유저의 정보(닉네임)을 검색하는 기능을 구현해보세요.
*/
template<typename T1, typename T2>
struct myPair
{
    T1 first;
    T2 second;

};

// 개인과제
void UserDataSearch(std::vector<std::pair<int, std::string>>data, int userID)
{
    
}

void LinearSearch(int arr[], int n, int target)
{
    // 전체 갯수를 반복해서 (for 반복문)
    // target과 같은 데이터가 존재하면 (조건문)

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
        {
            std::cout << "해당 하는 데이터 : " << target << " 을 찾았습니다.";
            return;
        }
    }
    
    std::cout << "데이터를 찾지 못했습니다." << std::endl;
}

void LinearSearch(std::vector<int>& arr, int target)
{
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
        {
            std::cout << "해당 하는 데이터 : " << target << " 을 찾았습니다.";
            return;
        }
    }

    std::cout << "데이터를 찾지 못했습니다." << std::endl;
}

// iterator 방식으로 구현한 이진 탐색 예제.
void BinarySearch(int arr[], int n, int target)
{
    int left = 0;
    int right = n - 1;

    // 중앙 값을 구하는 두가지 방법.
    // int mid = (left + right) / 2 
    // |Or| 
    // int mid = left + (right - left) / 2
   
    while (left <= right) // 왼쪽, 오른쪽
    {

        int mid = left + (right - left) / 2; // 루프를 돌때 마다 중앙값을 변경해준다.
      
        // 현재 mid값과 target을 비교해보세요.
        if (arr[mid] == target) // target 찾은 경우 : 데이터를 찾았다.
        {
            std::cout << "해당 하는 데이터 : " << target << " 을 찾았습니다.";
            return;
        }
        else if(arr[mid] > target) // target이 작은 경우 : 왼쪽에서 다시 찾으세요.
        {
            right = mid - 1; // mid의 기준으로 어떻게 right를 바꾸면 될까?
        }

        else //if (arr[mid] < target)  // target이 큰 경우
        {
            left = mid + 1;// 왼쪽 left가 mid의 기준으로 어떻게 바뀌면 될까?
        }

    }

    std::cout << "데이터를 찾지 못했습니다." << std::endl;

}

// 재귀 함수 방식으로 구현한 이진 탐색

void BinarySearchByRecursive(int arr[], int n, int target, int left, int right) // 왼쪽, 오른쪽의 값이 바뀐다.
{
   
    // 재귀 함수를 탈출할 수 있는 조건
    if (left > right)
    {
        std::cout << "데이터를 찾지 못했습니다." << std::endl;
        return;
    }
    int mid = left + (right - left) / 2;
 
    if (arr[mid] == target)
    {
        std::cout << "해당 하는 데이터 : " << target << " 을 찾았습니다.";
        return;
    }
    // 자기 자신의 함수를 호출하세요.
    else if (arr[mid] > target)  
    {
        BinarySearchByRecursive(arr, n, target, left, mid - 1); // 왼쪽  (right = mid - 1)
    }
    else
    {
        BinarySearchByRecursive(arr, n, target, mid + 1, right); // 오른쪽 (left = mid + 1)
    }

}

void BinarySearchByRecursive(std::vector<int> ary, int target, int left, int right)
{

}

void Example()
{
    // pair 사용방법이 기억이 안날시 겜프 4 복습하기.
    // pair 데이터 하나를 표현하는 방식. key, value 값을 구분해서 저장하는 방식.
    // 연산자 오버로딩. 클래스 비교를 재정의

    std::vector<std::pair<int, std::string>> data;

    std::pair<int, std::string> a = { 1, "AAA" };

    data.push_back({ 0,"AAA" });
    data.push_back(a);
    data.push_back(std::make_pair(2, "CCC"));
    data.push_back({ 3,"DDD" });
    data.push_back({ 4,"EEE" });

    // std::pair<int, std::string> a = {1,"aaa"};
    // std::make_pair(1, "aaa");

    // 선형 탐색, 이전 팀색을 사용해서 결과 값을 찾으세요.

    // 타입이 다르기 때문에 해당하는 타입으로 다시 만들어 줘야한다.

    std::vector<int> temp;

    for (int i = 0; i < data.size(); i++)
    {
        temp.push_back(data[i].first);
    }

    /* 개인과제 2
    * 1. 반환하는 값을 bool 타입으로 변경해보세요.
    * 2. LinearSearch(vector<int> -> vector<pair<int, std::string>> 버젼으로 변경해보세요.)
    * 3. userID를 사용해서 유저의 닉네임을 출력하는 코드를 완성해보세요.
    */

    LinearSearch(temp, 4);  // 값이 존재한다면 
    std::cout << "데이터가 존재합니다 : (" << data[4].second << ")" << std::endl;
}

int main()
{
    std::cout << "\n배열로 구현한 선형 탐색" << std::endl;

    int arr[5] = { 0,5,2,4,9 };

    LinearSearch(arr, 5, 2);

    std::cout << std::endl;

    std::cout << "\n벡터로 구현한 선형 탐색" << std::endl;

    std::vector<int> data = { 0,5,2,4,9 };

    LinearSearch(data, 9);

    std::cout << std::endl;

    std::cout << "\n배열로 구현한 이진 탐색" << std::endl;

    int arr2[5] = { 0,2,4,5,9 };
   // std::sort()
    BinarySearch(arr2, 5, 0);

    std::cout << std::endl;

    std::cout << "\n재귀함수로 구현한 이진 탐색" << std::endl;

    int arr3[5] = { 0,2,4,5,9 };

    BinarySearchByRecursive(arr3, 5, 0, 0, 4);

    std::cout << "\n벡터로 구현한 이진 탐색" << std::endl;

    // std::sort(data2.begin(), data2.end());

    // BinarySearch(data, 2);

    std::cout << std::endl;


    Example();
}
