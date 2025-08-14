#include <iostream>

#include "../shared/SinglyLinkedList.h"

using namespace std;
/*
꼼꼼하게 주소 연결을 확인하는 것을 권장한다

*/
int main()
{
	SinglyLinkedList<int> list; 

	list.SetPrintDebug(true);

	list.PushFront(3);
	list.PushBack(4);
	list.PushFront(2);
	list.PushFront(1);
	list.PushBack(5);

	list.Print();

	// copy constructor
	{
		SinglyLinkedList<int> list2 = list; // copy constructor
		list2.SetPrintDebug(true);
		list2.Print();
	}

	list.Reverse(); // 5 4 3 2 1 연결만 바꿔서 
	list.Print();

	SinglyLinkedList<int>::Node* temp = list.Find(3);
	list.InsertBack(temp, 1000);
	list.Print();

	list.InsertBack(temp, 50);
	list.Print();
	list.Remove(temp);
	list.Print();

	
	// PopFront()/Back() 테스트
	for (int i = 0; i < 5; i++)
	{
		//list.PopFront();
		//list.Print();

		list.PopBack();
		list.Print();

		if (!list.IsEmpty())
			cout << list.Front() << " " << list.Back() << endl;
	}

	// Edge case 테스트 주의

	return 0;
}
