#include "MyString.h"

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init)
{
	// 크기(size_) 결정
	size_ = 0;
	while (init[size_] != '\0')
	{
		size_++;
	}
	str_ = new char[size_];
	memcpy(str_, init, size_);

	// 메모리 할당

	// 데이터 복사
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	// 기본 복사 생성자는 포인터 주소만 복사하기 때문에 
	// 소멸시 오류 발생
	// 여기서는 새로 메모리를 할당 받아서 복사
	size_ = str.size_; // 
	str_ = new char[size_];
	memcpy(str_, str.str_, size_); //현재 에 원본의 내용을 size 바이트 만큼 복사 한다

}

MyString::~MyString()
{
	// 메모리 해제
	if (str_ != nullptr) {//할당이 안되어있는경우는 안해도 되니까 
		delete[] str_;
		str_ = nullptr;
		size_ = 0;
	}

}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	// 힌트: str.str_, str.size_ 가능
	if (this->size_ != str.size_)
		return false;

	for (int i = 0; i < this->size_; i++)
	{
		if (str.str_[i] != str_[i])
		{
			return false;
		}
	}
	return true;
}

int MyString::Length()
{
	return size_;
}

void MyString::Resize(int new_size)
{
	// 메모리 재할당과 원래 갖고 있던 내용 복사

	if (new_size != size_)
	{
		char* new_str = new char[new_size]; // new 는 주소를 준다 
		/*힙 메모리에 접근하려면 어디에 있는지 를 알기 위해 주소를 줘야한다
	    이를 저장하기 위해 포인터 변수 여기서는 char * 변수를 쓴다
		*/

		for (int i = 0; i < (new_size < size_ ? new_size : size_); i++)
		{
			new_str[i] = str_[i];
		}
		delete[] str_;
		str_ = new_str;
		size_ = new_size;
	}
		


}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	// assert(start + num - 1 < this->size_); // 문제를 단순하게 만들기 위해 가정

	MyString temp;

	temp.Resize(num);

	for (int i = 0; i < num;i++)
	{
		temp.str_[i] = this->str_[start + i];
	}
	return temp;
}

MyString MyString::Concat(MyString app_str)
{
	MyString temp;

	// TODO: 
	temp.Resize(app_str.size_ + this->size_);
	// memcpy 는 시작 주소를 받는다 temp_str_ 은 이건 포인터고 
	// 아래는 문자열 마지막의 포인터 주소를 받아오는거다 
	memcpy(temp.str_, this->str_, this->size_);
	memcpy(&temp.str_[this->size_], app_str.str_, app_str.size_); // 문자열 끝 위치 

	return temp;
}

MyString MyString::Insert(MyString t, int start)
{
	assert(start >= 0);
	assert(start <= this->size_);

	MyString temp;

	temp.Resize(this->size_ + t.size_);

	for (int i = 0; i < start; i++)
	{
		temp.str_[i] = str_[i];
	}
	for (int i = start; i < start + t.size_;i++)
		temp.str_[i] = t.str_[i - start];
	for (int i = start + t.size_;i < size_ + t.size_;i++)
		temp.str_[i] = str_[i - t.size_];

	return temp;
}

int MyString::Find(MyString pat)
{
	//TODO:

	for (int start = 0; start <= Length() - pat.Length(); start++)
	{
		for (int j = 0; j < pat.Length();j++)
		{
			if (str_[start + j] != pat.str_[j])
				break;

			if (j == pat.Length() - 1)
			{
				return start;
			}
		}
	}
	return -1;
}

void MyString::Print()
{
	for (int i = 0; i < size_; i++)
		cout << str_[i];
	cout << endl;
}

