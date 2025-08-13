#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>

template<typename T>
class Queue // Circular Queue
{
public:
	Queue(int capacity = 2)
	{
		assert(capacity > 0);

		capacity_ = capacity;
		queue_ = new T[capacity_];
		front_ = rear_ = 0;
	}

	~Queue()
	{
		if (queue_) delete[] queue_;
	}

	bool IsEmpty() const
	{
		return front_ == rear_;
	}

	bool IsFull() const
	{
		// 원형 큐에서 꽉 찼다의 기준
		return (rear_ + 1) % capacity_ == front_;
	}
	/*
	T& 은 T타입의 참조reference 를 반환한다는거다 
	즉 함수가 리턴할때 T 값 그 자체가 아닌 어떤 변수나 배열의 매모리 위치를 
	가리키는 별명 을 넘겨준다는거다

	이 참조를 통해 함수 호출자는 그 변수를 직접 읽거나 수정할수 있다

	값을 복사하는것이 아닌 원본 변수의 위치를 알려주는거다.
	*/
	T& Front() const 
	{
		assert(!IsEmpty());

		return queue_[(front_ + 1) % capacity_]; // 주의 + 1
	}

	T& Rear() const
	{
		assert(!IsEmpty());

		return queue_[rear_];
	}

	int Size() const
	{
		// 하나하나 세는 방법 보다는 경우를 따져서 바로 계산하는 것이 빠릅니다.
		// 3가지 경우 
		// 
		// f  = r  , f > r , r > f
		// 
		// 
		// if-else-if-else로 구현하는 경우
		if (rear_ > front_)
			return rear_ - front_;
		else if (rear_ < front_)
			return capacity_ - (front_) + rear_; 
		else
			return 0;

		// 또는 if-else 하나로도 구현 가능합니다.
		// if (front_ < rear_)
		//	  return rea;
		// else
		//    return ...;

		//return 0; // TODO: 임시
	}

	void Resize() // 2배씩 증가
	{
		// 조언
		// - 새로운 개념이 항상 그렇듯 원형 큐도 처음에는 어렵고 나중에는 당연해집니다.
		// - 처음 공부하실 때 답을 맞추려고 하지 마시고 "어떻게 디버깅을 잘 할까?"를 찾으세요.
		// - 부지런히 여러가지 출력해보고 "출력하는 도구(예: 배열 출력)"도 만들어서 사용해보고
		// - 머리도 쓰고 고민도 하다 보면 인생을 지탱해줄 능력을 갖추게 됩니다.
		// - 힘들면 디스코드에서 조금씩 도움 받으시는 것도 좋아요.

		// TODO: 하나하나 복사하는 방식은 쉽게 구현할 수 있습니다. 
		//     효울적  (도전) 경우를 나눠서 memcpy()로 블럭 단위로 복사하면 더 효율적입니다.
			
		//MYCODE -----
			/*int capacity_2 = capacity_;
			capacity_ = capacity_ * 2;
			T* new_queue = new T[capacity_];
			
			memcpy(new_queue, queue_, sizeof(T) * capacity_);
			
			if (front_ == rear_ + 1) // 원형 큐가 전부 차서 Resize해야하는 경우 
			{
				int j = 1; // 난 j 로 했고 
				for (int i = front_ + 1 ; i <capacity_2 ;i++)  // front_ 위로 증가 
				{
					new_queue[j] = queue_[i]; // 삽입
					j++;
				}

				for (int k = 0; k < front_;k++) // 다했다면 0 부터 front_ 까지 증가 
				{
					new_queue[j] = queue_[k];
					j++;
				}
				//초기화 

				front_ = 0;
				rear_ = capacity_2 -1;

			}
			// 기존 데이터 삭제후 새로 데이터 삽입
			if (queue_) delete[] queue_;
			queue_ = new_queue;*/ // 
		//강의 코드
		T* new_queue = new T[2 * capacity_];
		
		int count = 1;
		for (int i = (front_ + 1) % capacity_; i != (rear_ + 1) % capacity_; i = (i + 1) % capacity_)
		{ // 이 코드는 원형 처럼 돌려서 rear_ 까지 i 를 front +1 위치 부터 넣어주는 for문  
			new_queue[count] = queue_[i];
			count++;
		}

		front_ = 0;
		rear_ = capacity_ - 1;
		capacity_ *= 2;
		delete[] queue_;
		queue_ = new_queue;


	}

	void Enqueue(const T& item) // 맨 뒤에 추가, Push()
	{
		if (IsFull())
			Resize();
		/*if (capacity_ == rear_ + 1)
		{
			rear_ = 0;
			queue_[rear_] = item;
		}
		else {
			rear_ = rear_ + 1;

			queue_[rear_] = item;
		
		}*/
		
		rear_ = (rear_ + 1) % capacity_;
		queue_[rear_] = item;

		// TODO:
	}

	void Dequeue() // 큐의 첫 요소 삭제, Pop()
	{
		assert(!IsEmpty());

		// TODO: 

		//if (front_ == capacity_)
		//{
		//	front_ = 0;

		//	queue_[front_] = '-';
		//}
		//else {
		//	front_ = front_ + 1;

		//	queue_[front_] = '-';
		//}

		front_ = (front_ + 1) % capacity_;

	}

	void Print()
	{
		using namespace std;

		for (int i = (front_ + 1) % capacity_; i != (rear_ + 1) % capacity_; i = (i + 1) % capacity_)
			cout << queue_[i] << " ";
		cout << endl;

		if (print_debug_)
			PrintDebug();
	}

	void PrintDebug()
	{
		using namespace std;

		cout << "Cap = " << capacity_ << ", Size = " << Size();
		cout << endl;

		// front와 rear 위치 표시
		for (int i = 0; i < capacity_; i++) {
			if (i == front_) cout << " F ";
			else if (i == rear_) cout << " R ";
			else cout << "   ";
		}
		cout << endl;

		// 0 based index
		for (int i = 0; i < capacity_; i++)
			cout << setw(2) << i << " ";
		cout << endl;

		if (front_ < rear_)
		{
			// front 앞 사용하지 않은 공간
			for (int i = 0; i < front_ + 1; i++)
				cout << " - ";

			// 저장된 내용물
			for (int i = front_ + 1; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear 뒤 사용하지 않은 공간
			for (int i = rear_ + 1; i < capacity_; i++)
				cout << " * ";

			cout << endl << endl;
		}
		else if (front_ > rear_)
		{
			// rear 이전에 저장된 내용물
			for (int i = 0; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear와 front 사이 사용하지 않은 공간
			for (int i = rear_ + 1; i <= front_; i++)
				cout << " * ";

			// front 뒤 내용물
			for (int i = front_ + 1; i < capacity_; i++)
				cout << setw(2) << queue_[i] << " ";

			cout << endl << endl;
		}
		else // 비었을 경우
		{
			for (int i = 0; i < capacity_; i++)
				cout << " - ";
			cout << endl << endl;
		}
	}

	void SetDebugFlag(bool flag)
	{
		print_debug_ = flag;
	}

protected: // 뒤에서 상속해서 사용
	T* queue_; // array for queue elements
	int front_ = 0; // 시작 인덱스보다 하나 작은 값
	int rear_ = 0; // 마지막 인덱스 (첫 값은 1에 추가)
	int capacity_; // 빈 칸을 하나 둬야 하기 때문에 필요 메모리는 최대 저장량 + 1
	bool print_debug_ = false;
};
