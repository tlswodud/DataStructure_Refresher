#pragma once

#include "Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
/*
양쪽을 모두 사용가능한 것이다

rear  front 가 증가 감소하며 삭제 및 삽입을 할수 있다 
*/
template<typename T> // int 도 char 도 
class Deque : public Queue<T>
{

	typedef Queue<T> Base; // Base라는 이름으로 바꿔준다 

public:
	Deque(int capacity): Queue<T>(capacity)
	{

	}

	T& Front()
	{
		return Base::Front();  // Base의 front 전부 재활용 
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();

		// TODO:

		Base::queue_[Base::front_] = item;
		Base::front_ = (Base::front_ - 1 + Base::capacity_) % Base::capacity_;
		/*
		음수가 되는걸 방지하기 위해서 

		-1 이 되면 + capacity_ (8이라가정) 

		그럼 7로 front_가 바뀐다!
		
		*/
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());

		// TODO:

		

		Base::rear_ = (Base::rear_ - 1 + Base::capacity_ ) % Base::capacity_;



	}

private:
	// Queue와 동일

	int& rear_ = Base::rear_;

	/*
	자식클래스에 레퍼런스로 부모의 변수로 생성하면 

	자식클래스의 변수가 부모 클래스 변수의 레퍼런스기 떄문에 같은거라고 볼수 있다

	이렇게 하면 Base 빼도 된다.

	간단간단

	*/

};
