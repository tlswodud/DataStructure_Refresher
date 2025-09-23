#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;
/*
전체를 쪼개고 쪼개는것

중간위치 잡고 이를 pivot 이라하고

이것 보다 작은건 왼 , 큰건 우

piviot 7

   16      7       2

   16하고 2를 바꿈 

   2       7      16 이렇게 

 
시간 복잡도: 피벗이 잘 정해져서 균등하게 나뉘게 되면 최선 O(n log n)이 됩니다. 평균도 O(n log n)으로 알려져 있습니다. 그러나 피벗이 최악으로만 결정된다면 한쪽으로만 몰리게 되어서 최악의 시간 복잡도는 O(n^2)이 되어버립니다.

공간 복잡도: 최선과 평균은 O(log n)이 됩니다. 최악의 경우는 O(n)이 됩니다.

평균 성능은 확률적 기대값으로 추측하는데 알고리듬 과목에서 다룹니다.

*/
bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{ 
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int low, int high, int n)
{
	for (int i = 0; i < n; i++)
		if (i >= low && i <= high)
			cout << setw(3) << arr[i] << " ";
		else
			cout << "    ";
	cout << endl;
}

// Hoare partition scheme
/*

*/
int Partition(int arr[], int low, int high, int n)
{
	int pivot = arr[size_t(floorf((high - low) / 2.0f)) + low];
	int i = low - 1;
	int j = high + 1;

	cout << "pivot=" << pivot << endl;
	cout << "         ";
	Print(arr, low, high, n);

	while (true)
	{
		do i = i + 1; // 무조건 한번은 실행하고 그 다음 조건식 검사 True 면 반복
		while (arr[i] < pivot);

		do j = j - 1;
		while (arr[j] > pivot);

		if (i >= j)
			return j;

		swap(arr[i], arr[j]);


		cout << "pivot=" << pivot << ", i=" << i << ", j=" << j << endl;
		cout << "         ";
		Print(arr, low, high, n);
	}
}

void QuickSort(int arr[], int low, int high, int n) // 마지막 n은 출력용;
{
	if (low >= 0 && high >= 0 && low < high)
	{
		// Partitioning Index
		int p = Partition(arr, low, high, n);

		QuickSort(arr, low, p, n); // Note: the pivot is now included
		QuickSort(arr, p + 1, high, n);
	}
}

int main()
{
	int arr[] = { 4, 17, 2, 9, 7, 5, 8, 1, 14, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;

	QuickSort(arr, 0, n - 1, n);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;
}
