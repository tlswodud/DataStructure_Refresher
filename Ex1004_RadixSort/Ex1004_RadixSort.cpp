#include <iostream>
#include "../shared/Queue.h"

using namespace std;

/*
통을 만들어서 인덱스로 정렬하는거네

자리수를 나눠서 정렬하라?

일의 자리 부터 보고 기수정렬

십의 자리 정렬

백의 자리 정렬 아무것도 없으면 0

이렇게 하면 모두 정렬 가능하다


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

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int GetMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

int main()
{
	int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	int n = sizeof(arr) / sizeof(arr[0]);

	Print(arr, n);

	Queue<int> queues[10];

	int m = GetMax(arr, n); // 가장 큰 자리수를 찾기 위해서

	for(int exp = 1; m  / exp > 0; exp *= 10)
	{
		for (int i = 0; i < n; i++)
		{
			queues[(arr[i] / exp) % 10 ].Enqueue(arr[i]);
		}

		int count = 0;
		
		for (int i = 0; i < n; i++)
		{
			while (!queues[i].IsEmpty())
			{
				arr[count] = queues[i].Front();
				queues[i].Dequeue();
				count++;
			}
		}

		Print(arr, n);
	}

	return 0;
}
