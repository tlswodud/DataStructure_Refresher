#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node // 템플릿 사용 
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		
		Node* current = list.first_;  // current 에

		while (current)
		{
			this->PushBack(current->item); //this 는 왜필요한걸까 
			current = current->next;

		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO: 모두 삭제

		Node* current = first_;
		
		while (current)
		{
			Node* temp = current->next;

			delete current;

			current = temp;
		}

	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;

		//// TODO: size를 하나하나 세어서 반환

		Node *current = first_;
		
		while (current)
		{
			current = current->next;
			size++;
		}
		return size;
	}

	T Front()
	{
		assert(first_);

		return T(); // TODO: 수정
	}

	T Back()
	{
		assert(first_);

		return T(); // TODO: 수정
	}

	Node* Find(T item)
	{
		// TODO: item이 동일한 노드 포인터 반환

		Node* current = first_;

		while (current)
		{	
			if (current->item == item)
			{
				return current;
			}

			current = current->next;			
		}
		
		return 0;
	}

	void InsertBack(Node* node, T item) // 넣는 작업 
	{
		//삽입 삭제 O(1) 아주 빠르다 
		//insertFront
		/*Node* current = node;
		
		Node* new_node = new Node;
		new_node->item = item;
		new_node->next = current;

		
		Node* temp = first_; 
		while (1)
		{
			if (temp->next == current)
			{
				temp->next = new_node;
				break;
			}
			temp = temp->next;
		}*/
				
		Node* current = node;
		Node* new_node = new Node;
		new_node->item = item;
		new_node->next = current->next;

		current->next = new_node;

		// TODO:
	}

	void Remove(Node* n)
	{
		assert(first_);

		Node* current = first_;
		while (1)
		{	
			current = current->next;
			if (current->next == n)
			{
				current->next = n->next;
				break;
			}
		}
		// 하나 앞의 노드를 찾아야 합니다.
		// TODO:

		delete n;
	}

	void PushFront(T item)
	{
		// first_가 nullptr인 경우와 아닌 경우 나눠서 생각해보기 (결국은 두 경우를 하나로 합칠 수 있음)

		// 새로운 노드 만들기
		// TODO:
		Node* temp = new Node;
		temp->item = item;

		temp->next = first_;
		first_ = temp;

		// 연결 관계 정리
		// TODO:
	}

	void PushBack(T item)
	{	
		
		if (first_)
		{
			Node* current = first_;
			while (current->next) // current 의 next 가 nullptr 이면 종료 
			{
				current = current->next;

			}
			
			Node* temp = new Node;
			temp->item = item;
			temp->next = nullptr; // 새로운 노드 만들고 item 과 next 할당

			current->next = temp; // current 다음 주소에 

			/*
			단일 객체 생성 
			노드 타임 하나를 힙 에 만든다 

			반환값은 Node* - >  객체의 주소이다 
			힙에 Node 한개 , 포인터 하나가 스택에 있다

			배열 생성
			float* values;
			values = new float[10];

			앞에 타입이 없다면 이미 선언된 변수 

			힙에 10개의 float을 만들고 그 첫번째 주소를 반환해서 주소 배열인 values 에 넣는다
			*/
		}
		else
		{
			// TODO:
			PushFront(item);
		}
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		// TODO: 메모리 삭제
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.

		assert(first_);

		Node* current = first_;
		while (1)
		{	
			current = current->next;
			if (current->next == nullptr)
			{

			}

		}



		// TODO: 메모리 삭제
	}

	void Reverse()
	{
		// TODO: 
	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};