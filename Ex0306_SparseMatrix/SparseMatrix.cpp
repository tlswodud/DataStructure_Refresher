#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;


/*
0 이 아닌 항이 몇개 없는걸 희소 행렬이라하고 
*/

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
{
	terms_ = new MatrixTerm[capacity];
	
	capacity_ = capacity;
	num_cols_ = num_cols;
	num_rows_ = num_rows;
	num_terms_ = 0;
}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix& b)
{	
	if (b.capacity_ > 0) {
		terms_ = new MatrixTerm[b.capacity_];

		capacity_ = b.capacity_;
		num_cols_ = b.num_cols_;
		num_rows_ = b.num_rows_;
		num_terms_ = 0;

		memcpy(b.terms_, terms_, sizeof(MatrixTerm) * b.num_terms_);
	}
}

SparseMatrix::~SparseMatrix()
{
	if (terms_)
	{
		delete[] terms_;
	}
}

void SparseMatrix::SetValue(int row, int col, float value)
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장

	////정렬하지 않는경우 

	//terms_[num_terms_].row = row;
	//terms_[num_terms_].col = col;
	//terms_[num_terms_].value = value;

	//num_terms_++;

	int key = col + num_cols_ * row;
	int i = 0;
	// BIG O (num_terms_)
	for (; i < num_terms_; i++) // 하나씩 쭉 
	{
		int key_i = terms_[i].col + num_cols_ * terms_[i].row;
		//  쭉 진행하다가 동일하면 거기에 추가하고 끝 
		if (key_i == key)
		{
			terms_[i].row = row;
			terms_[i].col = col;
			terms_[i].value = value;
			return;
		}
		else if (key_i > key)
		{
			break;
		}// 이게 더 크다?  뒤로 밀어내고 추가해야한다 
	}

	num_terms_++;

	for (int j = num_terms_ - 1; j > i; j--) //
	{
		terms_[j] = terms_[j - 1]; // 뒤에 있는걸 앞으로 땡겨주기
	}
	terms_[i].col = col;
	terms_[i].row = row;
	terms_[i].value = value;

}

float SparseMatrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{	
	// 정렬이 안되어있을때 모든 걸 다 뒤져야한다 -> 최악의 시간복잡도

	// 주어진 num_terms 만큼 증가하다 row , col 이 같다면 value  반환
	//for (int i = 0; i < num_terms_; i++)
	//{
	//	if (terms_[i].row == row && terms_[i].col == col)
	//	{
	//		return terms_[i].value;
	//	}
	//}
	//return 0.0f;// 아니면 0


	// TODO: key = col + num_cols * row; 
	// 정렬된 상태라면 순서대로 보면 되니 더 빠르다
	int key = col + num_cols_ * row;

	for (int i = 0; i < num_terms_; i++)
	{
		int key_i = terms_[i].col + terms_[i].row * num_cols_;

		if (key_i == key)
			return terms_[i].value;

		else if (key_i > key)
		{
			return 0.0f;
		}
	}
	return 0.0f;

}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(num_cols_, num_rows_, capacity_); // num_cols_, num_rows_ 순서 주의
	// 정렬이 안되어있는 경우 
	//for (int r = 0; r < temp.num_rows_; r++)
	//{
	//	for (int c = 0; c < temp.num_cols_; c++)
	//	{
	//		temp.SetValue(c, r , GetValue(r , c)); // 이중포문이니 
	//	} // num_terms * 2  * num_rows * num_cols 이렇게 시간 복잡도가 아주 커진다
	//}   //결국 이건 느리다

	//되어있는경우 
	//for (int r = 0; r < temp.num_rows_; r++)
	//{
	//	for (int c = 0; c < temp.num_cols_; c++)
	//	{
	//		temp.SetValue(r, c , GetValue(c , r));
	//	}
	//}

	//return temp;

	// 뭐지 이건 
	for (int r = 0; r < temp.num_rows_; r++) // r을 뒤져가면서 temp 는 num_cols 다 유의
	{ // 보면 num_cols * num_terms 이렇게 한번더 안곱해도 찾는다 
		for (int i = 0; i < num_terms_; i++)
		{
			if (terms_[i].col == r)
			{
				temp.terms_[temp.num_terms_].value = terms_[i].value;
				temp.terms_[temp.num_terms_].col = terms_[i].row;
				temp.terms_[temp.num_terms_].row = terms_[i].col;
				temp.num_terms_++;
			}
		}
	}
	return temp;

}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < num_terms_; i++) // 항들만 
		cout << "(" << terms_[i].row
		<< ", " << terms_[i].col
		<< ", " << terms_[i].value
		<< ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < num_rows_; r++) 
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}
