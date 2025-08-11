#include "Array2D.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Array2D::Array2D(int num_rows, int num_cols)
{
	//TODO:

	//주소의 배열이다 
	arrays_ = new float* [num_rows]; // 포인터의 주소들의 배열인 arrays 에 float* 타입의 주소를 num_rows 개 할당한다

	for (int r = 0; r < num_rows; r++)
	{
		arrays_[r] = new float[num_cols]; // arrays_[i] 에 float 타입을 num_cols 개 할당한다  
	}
	// 동적할당 후에 첫 주소를 arrays_ 에 저장하고 
	// 아주 아주 많다면 이렇게 쪼개서 저장할수 있는것 
	num_rows_ = num_rows;
	num_cols_ = num_cols;

	// 초기화를 해줘야한다 

	for (int r = 0; r < num_rows_; r++)
	{	
		float* row = arrays_[r]; //arrays_ 값을 float* 으로 받아서 초기화 

		for (int c = 0; c < num_cols; c++)
		{
			row[c] = 0.0f;
			// arrays_[r][c] = 0.0f; 이거도 된다 
		}
	}
}

// 복사 생성자 (b를 복사)
Array2D::Array2D(const Array2D& b)
{
	//TODO:

	arrays_ = new float*[b.num_rows_];

	num_cols_ = b.num_cols_;
	num_rows_ = b.num_rows_;

	for (int i = 0; i < b.num_rows_; i++)
	{
		arrays_[i] = new float[b.num_cols_];
	}

	for (int r = 0; r < num_rows_; r++)
	{
		memcpy(arrays_[r], b.arrays_[r], sizeof(float) * num_cols_);
		//b,arrays_[r] 주소 부터 시작해서 
		// 20 바이트 수만큼 float 4 바이트 * num_cols 수 총 한행을 
		// arrays_[r] 에 복사하겠다
	}


}

Array2D::~Array2D()
{
	//TODO:
	if (arrays_) {
		for (int i = 0; i < num_rows_; i++)
		{
			delete[] arrays_[i];
		}

		delete[] arrays_;
	}
}

void Array2D::SetValue(int row, int col, float value)
{
	// TODO:

	arrays_[row][col] = value;

}

float Array2D::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return arrays_[row][col]; // TODO:
}

Array2D Array2D::Transpose()
{
	Array2D temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	for (int r = 0; r < num_rows_; r++)
		for (int c = 0; c < num_cols_; c++)
			temp.SetValue(c, r, GetValue(r, c));

	return temp;
}

Array2D Array2D::Add(const Array2D& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Array2D temp(num_rows_, num_cols_);

	for (int r = 0; r < num_rows_; r++)
		for (int c = 0; c < num_cols_; c++)
			temp.SetValue(r, c, GetValue(r, c) + b.GetValue(r, c));

	return temp;
}

void Array2D::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
