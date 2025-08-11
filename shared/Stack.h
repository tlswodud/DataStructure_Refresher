#pragma once

#include <cassert>
#include <iostream>

template<typename T> // 템플릿 사용

/*
템플릿 문법에 대해 보면 
template<typename T> 이렇게 하고 
class stack {.... } 정의한 것이고

stack <int> s1;
stack <char> s2; 이렇게 사용자가 타입을 지정해줄수 있는 것이다
*/



class Stack
{
public:
	Stack(int capacity = 1)
	{
		assert(capacity > 0);
		Resize(capacity);
	}

	~Stack()
	{
		if (stack_) delete[] stack_;
	}

	void Resize(int new_capacity)
	{
		T* new_stack = new T[new_capacity];
		memcpy(new_stack, stack_, sizeof(T) * Size());
		if (stack_) delete[] stack_;
		stack_ = new_stack;
		capacity_ = new_capacity;
	}

	bool IsEmpty() const
	{	
		if (top_ == -1)
			return true;
		return false; // TODO:
	}

	int Size() const
	{	
		return top_ + 1; //TODO:
	}

	void Print()
	{
		using namespace std;

		for (int i = 0; i < Size(); i++) // Size() 사용
			cout << stack_[i] << " ";
		cout << endl;
	}

	// Returns TOP element of stack.
	T& Top() const
	{
		assert(!IsEmpty());

		return stack_[top_];
	}

	// Insert item into the TOP of the stack
	void Push(const T& item)
	{
		// TODO: 필요하면 리사이즈 
		
		if (capacity_ == top_ + 1)
		{
			Resize(capacity_ * 2);
		}

		top_ = top_ + 1;
		stack_[top_] = item;
		
		// TODO:
	}

	// Delete the TOP element of the stack
	void Pop()
	{
		assert(!IsEmpty());

		//stack_[top_] = 0;
		top_--;

		//메모리를 아낄때 
		//stack_[top_--].~T();

		// TODO:
	}

protected: // 뒤에서 상속해서 사용
	T* stack_ = nullptr;
	int top_ = -1; // 0 아님 size 하고 비슷한 개념 
	int capacity_ = 0;

};
