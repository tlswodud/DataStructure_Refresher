#include <iostream>

using namespace std;

/*
index 색인

메모리가 시작하는


*/

int SequentialSearch(int arr[], int start, int stop, int x)
{
	for (int i = start; i < stop; i++)
	{
		if (arr[i] == x)
			return i;
	}

	return -1;
}

int main()
{
	int arr[] = { 1, 2, 8, 13, 22, 45, 55, 75, 88 };
	int n = sizeof(arr) / sizeof(arr[0]);

	int keys[] = { 1, 13, 55 };
	int kn = sizeof(keys) / sizeof(keys[0]);

	int indices[] = { 0, 3, 6, n }; // 마지막에 n 하나 더 추가

	int k = 0;

	for (int x : {1, 2, 8, 13, 22, 45, 55, 75, 88, 99, -1, 47, 101, 1000, 7, 10, 50, 60 })
	{
		if (x < arr[0] || x > arr[n - 1])
			cout << x << " was not found" << endl;
		else
		{
			// TODO: 
			/*
			key 의 indicies 값이 찾고자하는 x 보다
			*/


			// 인덱스 테이블에서 검색할 범위 결정
			int k = 0;
			while (k < kn - 1 && keys[k + 1] <= x)
				k++;

			// 색인 표의 범위에 따라서 선형 탐색
			// indices[k] 이상 indices[k+1] 미만에 대해 검색
			// 이때 indices 배열 마지막에 추가로 n을 저장해뒀기 때문에 k+1 사용 가능
			int found = SequentialSearch(arr, indices[k], indices[k + 1], x);
			if (found >= 0)
				cout << x << " was found at " << found << endl;
			else
				cout << x << " was not found" << endl;

			
			/*
			indices[0] 보다 작은것도 고려 해줘야하나 해서 이렇게 짰음 
			안해도 되나 봄 

			for (int i = 0; i < kn;i++)
			{	
				if (keys[i] == x) {
					cout << indices[i] << endl;
					break;
				}

				if (keys[i] > x)
				{	
					if (i == 0) {
						cout << SequentialSearch(arr, 0, indices[1], x) << endl;
						
					}
					
					else {
						int result = SequentialSearch(arr, indices[i - 1], indices[i], x);
						
						if (result == -1) {
							cout << x << " was not found" << endl;
							break;
						}
						cout <<result << endl;
					}
					break;
				}
				else if(keys[kn-1] < x )
				{
					int result = SequentialSearch(arr, indices[i], n, x);

					if (result == -1) {
						cout << x << " was not found" << endl;
						break;
					}
					cout << result << endl;
					break;
				}
			}*/




		}
	}

	return 0;
}
