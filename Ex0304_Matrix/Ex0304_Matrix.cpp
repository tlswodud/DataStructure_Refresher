#include <iostream>

#include "Matrix.h"

/*
3 by 4 matrix 
1 2 3 4 
2
3

001 012 023 030
100 114 125 130
200 210 220 237

(r ,c ) 
c  + num_cols * r 

3 + 2  * 1
= 7 
1차원 인덱스로 바꾸는 이유는 결국 우리는 1차원 인덱스로 접근해야한다

*/

int main()
{
	using namespace std;

	Matrix m1(3, 4); // row 3 개 col 4 개 생성 
	m1.SetValue(0, 0, 1.0f);
	m1.SetValue(0, 1, 2.0f);
	m1.SetValue(0, 2, 3.0f);
	m1.SetValue(1, 0, 0.0f);
	m1.SetValue(1, 1, 4.0f);
	m1.SetValue(1, 2, 5.0f);
	m1.SetValue(2, 3, 7.0f); // 더해진 행렬

	m1.Print();

	cout << endl;

	Matrix add = m1.Add(m1); // 자기 자신과 더하기
	add.Print();

	cout << endl;

	Matrix tr = m1.Transpose(); // 전치행렬 
	tr.Print();

	return 0;
}

