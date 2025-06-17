#include <iostream>
#include <vector>
#include <algorithm>
#include "MergeSort.h"

//  void quickSort(std::vector<int> nums, int start, int end)
// {
//     int n = nums.size();
//     int pivot = start;
//     int left = start + 1;
//     int right = end;
// 
//     if (start >= end)
//     {
//         return;
//     }
// 
//     while (left <= right)
//     {
// 
//         while (left <= end && nums[left] <= nums[pivot])
//         {
//             left++;
//         }
//         while (right >= start && nums[right] >= nums[pivot])
//         {
//             right--;
//         }
// 
//         if (left > right)
//         {
//             std::swap();
//         }
//         else
//         {
//             std::swap();
//         }
// 
//     }
// 
// }


int main()
{
   // int n;
   // std::cin >> n;
   //
   // std::vector<int> list;
   // list.assign(n, 0);
   //
   // for (int i = 0; i < n; i++)
   // {
   //     std::cin >> list[i];
   // }
   //
   // for (int i = 0; i < n; i++)
   // {
   //     std::cout << list[i] << std::endl;
   // }
   
    

    std::cout << "\n병합 정렬 배열 버젼" << std::endl;

    int arr[6] = { 3,2,5,1,4,6 };

    MergeSort(arr, 6, 0, 5);

    for (int i = 0; i < 6; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << "\n병합 정렬 vector 버젼" << std::endl;

}

