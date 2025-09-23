#include <iostream>

/*

보간 탐색 이라는 개념 

이진 탐색

배열이 정렬이 되어있고 가운데 를 찾는 방식

일반적으로 그렇지는 않지 

사전이라면 알파벳으로 찾겠지

이런게 보간 탐색이다 

인덱스가 작다면 적당히 작은 쪽에서 . 크다면 적당히 큰 쪽 

오른쪽이 크니까 

인덱스가 증가하면 값도 증가한다 


arr[high] - arr[low] : x - arr[low] = high - low : pos - low  

값과 인덱스 의 비율 

찾고자 하는거지 x 값
가장 가능성이 높은게 pos index 

pos = low  + (high - low ) * (x - arr[low] )  / (arr[high] - arr[low])
*/
using namespace std;

int rec_count = 0;

int InterpolationSearch(int arr[], int low, int high, int x)
{
	rec_count++;

	if (low <= high && x >= arr[low] && x <= arr[high])
	{
		//int pos = (low + high) / 2; // 이진 탐색 (중간)
		int pos = low + (int)(((float)(high - low) / (arr[high] - arr[low])) * (x - arr[low]));
		// TODO: int pos = 보간 탐색으로 수정

		if (arr[pos] == x)
			return pos;

		if (arr[pos] < x)
			return InterpolationSearch(arr, pos + 1, high, x);

		if (arr[pos] > x)
			return InterpolationSearch(arr, low, pos - 1, x);
	}

	return -1;
}

// https://www.geeksforgeeks.org/interpolation-search/
int main()
{
	int arr[] = { 10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47 };
	int n = sizeof(arr) / sizeof(arr[0]);

	for (auto x : { 10, 18, 33, 47, -1, 99 })
	{
		rec_count = 0;

		int index = InterpolationSearch(arr, 0, n - 1, x);

		if (index != -1)
			cout << x << " was found at index " << index << endl;
		else
			cout << x << " was not found." << endl;

		cout << "rec_count = " << rec_count << endl;
		cout << endl;
	}

	return 0;
}