#include "../shared/Queue.h"

#include <iostream>

/*
front , rear 

처음은 비어있고 

rear 를 하나 증가시키고 삽입
(size 는 rear - front )

하나 더 들어오면 rear 증가 하고 삽입

빼고 싶다면 front 전진하고 처음들어온거 빼기 

Capacity 가 꽉차벼렸다면 

rear+ 1 % capacity 하면  3 +1 / 4 = 0 으로 0자리에 삽입가능

원형 큐 

rear 전진하면 front 하고 만나 버리네 

그러면 삽입 못하고 capacity 증가를 해줘야해 

first in first out 


*/


int main()
{
	// FIFO(First In First Out)

	Queue<char> q(2); // capacity_ = 2에서 시작 (메모리 증가 확인)

	q.SetDebugFlag(true); // 디버깅

	q.Print();

	q.Enqueue('A'); // push 
	q.Print();

	q.Enqueue('B');
	q.Print();

	q.Enqueue('C');
	q.Print();

	q.Enqueue('D'); // pop
	q.Print();

	q.Dequeue();
	q.Print();

	q.Dequeue();
	q.Print();

	q.Dequeue();
	q.Print();

	for (char c = 'E'; c <= 'K'; c++) // 메모리 증가 테스트 
	{
		q.Enqueue(c);
		q.Print();
	}

	return 0;
}
