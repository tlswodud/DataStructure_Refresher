#pragma once

class Matrix
{
public:
	Matrix(int num_rows, int num_cols);

	Matrix(const Matrix& b);

	~Matrix();

	void SetValue(int row, int col, float value); // row col 교차 지점에 value 를 저장한다

	float GetValue(int row, int col) const;       

	Matrix Add(const Matrix& b);

	Matrix Transpose(); // 구현사례 

	void Print();

private:
	float* values_ = nullptr;  // 1차원 배열 값을 가져오는 것 
	int num_rows_ = 0;
	int num_cols_ = 0;
};
