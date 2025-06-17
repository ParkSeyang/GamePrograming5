#pragma once

#include <iostream>
#include <vector>

#pragma region ���� ����
/*
* ��� �ڵ带 �����غ��� ������?
*
* ���� ����
* �ٽ� ���� : �ϴ� ������, ���ݾ� ����� 1���� �� �� ����
*            �׸��� �������� �ͳ��� �����ؼ� ��ģ��.
*/

/* ���ĵ��� ����
* 
* �� �������� ��
* - ���� : ���ĵǾ� �������� ������.
* - ���� : n�� ũ�Ⱑ ũ�� Ŭ ���� ��ȿ�����̴�. 
* 100�� ������ ����, ���ĵǾ� �ִ� ����(biased)�� ���� �� ����ϸ� ������ �ִ�.
* 
* �� �� ���� ��
* - ���� : ���������� ���� ����Ѵ�. STL sort, ��κ��� ��쿡 O(n logn) �ð��� �����Ѵ�.
* - ���� : worst case(�־��� ���)�� O(n^2)�� �߻��Ҽ��ִ�.
* ������ �� sort, pivot - �� ����. �˰���
* 
* �� ���� ���� ��
* - ���� : ��������� O(n logn) �ð��� �����Ѵ�.
* - ���� : sorted��� ������ ���� �迭�� ����ϱ� ������, �߰����� �޸𸮸� ����Ѵ�.
* 
*  algorithm ��� sort(begin(),end());
* 
*/

/*
* ������ = mergesort
* ��ģ�� = merge
*/

void Merge(int arr[], int n, int left, int mid, int right)
{
	// 1. ���ĵ� �����͸� ���� ������ �迭 ������ �����մϴ�. (sorted array ���� �迭)
	std::vector<int> sortedarray;  // ���ʰ� �������� ���ؼ� ���Ľ�Ų ���� ������ �ӽ� �����̳�
	sortedarray.assign(n, 0);   // n���� ������ �����Ͱ� 0���� �ʱ�ȭ �� ���� �迭�� ����
	int i = left;               // ���ʿ��� �����ϴ� �ε��� ��ȣ
	int j = mid + 1;              // �����ʿ��� �����ϴ� �ε��� ��ȣ
	int k = left;               // ���ĵ� �ε������� ���� ù��° �ε��� ��ȣ

	// 2. arr �迭�ȿ� ����ִ� �� left �ε��� ���� right �ε��� �� ���� ���� sorted ��������

	// left ���� ���, right ���� ���
	while (i <= mid && j <= right) // ���� �Ǵ� ������ �ε����� ���� ���� ���� �����ϼ���.
	{
		if (arr[i] <= arr[j])
		{
			sortedarray[k] = arr[i];
			i++;
			k++;
		}
		else
		{
			sortedarray[k] = arr[j];
			j++;
			k++;
		}
	}
	
	// 3. i�� ������ ��, j�� ������ �� �������� ���� ä�켼��
	if (i > mid)  // i�� �� ����Ѱ��, ���� �ε����� j�� ���� ���
	{
		for(int t = j; t <= right; t++)
		{
			sortedarray[k] = arr[t];
			k++;
		}
	}
	else // j�� �� ����� ���, i�� ������ ��
	{
		for (int t = i;  t <= mid;  t++)
		{
			sortedarray[k] = arr[t];
			k++;
		}
	}
	// sorted 4������ right ������ŭ�� arr���� �����ϴ� �ڵ带 ����� �ϼ��غ�����.
	// 4. sorted ���� ���ĵ� ����. arr ���� �����Ϳ� ���ĵ� �����͸� �Ű��ش�.

	for (int t = left; t <= right ; t++)
	{
		arr[t] = sortedarray[t];
	}

}

void MergeSort(int arr[], int n, int left, int right)
{
	// ��������� MergeSort

	// ���ʺκ� MergeSort
	// �����ʺκ� MergeSort

	// merge
	if (left < right) // ���࿡ left == right �� -> ���Ұ� 1���̴�.
	{
		int mid = (left + right) / 2; // left �� right �� ����ؼ� �����غ�����.
		MergeSort(arr, n, left, mid); // ���ʺκ�
		MergeSort(arr, n, mid + 1, right); // ������ �κ�

		Merge(arr, n, left, mid, right);
	}

}

#pragma endregion

