#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Matrix::Matrix(int num_rows, int num_cols)
{
	// TODO:
	values_ = new float[num_rows * num_cols];
	num_rows_ = num_rows;
	num_cols_ = num_cols;

	for (int i = 0;i < num_rows_ * num_cols_; i++)
	{
		values_[i] = 0.0f;
	}

}

// 복사 생성자 (b를 복사)
Matrix::Matrix(const Matrix& b)
{
	// TODO:
	values_ = new float[b.num_cols_ * b.num_rows_];

	num_cols_ = b.num_cols_;
	num_rows_ = b.num_cols_;

	for (int i = 0; i < num_cols_ * num_rows_; i++)
	{
		values_[i] = b.values_[i];
	}
}

Matrix::~Matrix()
{
	// TODO:

	if (values_) delete[] values_;


}

void Matrix::SetValue(int row, int col, float value)
{
	// values_[TODO] = value;

	values_[row * num_cols_ + col] = value; // (r , c )  c + num_cols * r

}

float Matrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return values_[row * num_cols_ + col ]; // 이 인덱스 값을 반환하고 싶다는 거네 
}

Matrix Matrix::Transpose()
{
	Matrix temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	// TODO:
	for (int r = 0; r < num_rows_;r++)
	{
		for (int c = 0; c < num_cols_; c++)
		{
			temp.SetValue(c, r, GetValue(r, c)); // 반환값을 넣어주는데 c 하고 r 하고 순서를 바꿔주는거고 
		}
	}


	return temp;
}

Matrix Matrix::Add(const Matrix& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Matrix temp(num_rows_, num_cols_);

	// TODO:
	
	
	for (int r = 0;r < num_rows_;r++)
	{
		for (int c = 0; c < num_cols_; c++)
		{	
			temp.SetValue(r, c, GetValue(r, c) + b.GetValue(r, c));
		}
	}

	return temp;
}

void Matrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
