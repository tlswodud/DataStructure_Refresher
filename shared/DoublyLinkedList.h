#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr; //left right 
		Node* right = nullptr;

		// 참고: prev/next가 아니라 left/right
	};

	DoublyLinkedList()
	{
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO:
		Node* node = first_;
		Node* current = node->right;
		while (current)
		{	
			delete node;
			node = current;
			current = current->right;
		}
		
	}

	bool IsEmpty()
	{
		if(Size()>0)
			return 0; // TODO:
		else
			return 1;
	}

	int Size()
	{
		int size = 0;

		// TODO:
		Node* node = first_;

		while (node)
		{
			node = node->right;
			size++;
		}
		

		return size;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;
		Node* precurrent = current;
		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;

			cout << " Forward: ";
			// MYCODE
			// 다른 노드로 사용했음
			/*while (current)
			{
				cout << current->item << " ";
				precurrent = current;
				current = current->right;
			}*/
			//강의코드 중간 중단해서
			while (true)
			{
				cout << current->item << " ";

				if (!current->right)
				{
					break;
				}
				current = current->right;
			}

			cout << endl;
			cout << " Backward: ";
			/*while (precurrent)
			{
				cout << precurrent->item << " ";
				precurrent = precurrent->left;
			}*/

			while (true)
			{
				cout << current->item << " ";
				if (!current->left)
				{
					break;
				}
				current = current->left;

			}

			cout << endl;
		}
	}

	Node* Find(T item)
	{	
		Node* current = first_;
		
		while (current) {
			
			if (item == current->item)
			{
				return current;
			}

			current = current->right;

		}


		return nullptr; // TODO:
	}

	void InsertBack(Node* node, T item)
	{
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			// TODO:
			/*Node* current = first_;
			
			Node* newnode = new Node;
			newnode->item = item;

			
			while (current)
			{	
				if (current == node) {
					
					newnode->right = current->right;
					newnode->left = current;
					current->right = newnode;
				}
				
				current = current->right;
				
			}*/
			//찾아가는건 O(n) 이지만 삽입삭제 O(1)
			Node* temp = new Node;
			temp->item = item;
			temp->right = node->right;
			node->right = temp;

			if (temp->right)
			{
				temp->right->left = temp; // 이런 코드도 되는구만 
			}
			temp->left = node;

		}
	}

	void PushFront(T item)
	{
		//// TODO:
		// TODO:
		if (first_)
		{
			Node* current = first_;
			Node* node = new Node;
			node->item = item;

			node->left = nullptr;
			node->right = current;

			current->left = node;

			first_ = node;
			
		}
		else
		{
			Node* node = new Node;
			node->item = item;
			node->right = nullptr;
			node->left = nullptr;

			first_ = node;
		}

	}

	void PushBack(T item)
	{

		/*Node* node = new Node;
		node->item = item;
		node->left = nullptr;
		node->right = nullptr;

		Node* current = first_;
		Node* precurrent = current;
		if (first_)
		{
			while (current)
			{
				precurrent = current;
				current = current->right;
			}
			precurrent->right = node;

			node->left = precurrent;
		}
		else
		{
			PushFront(item);
		}*/
		if (first_) {

			Node* current = first_;
			while (current->right) // 노드 하나 더 안만들고 이런식으로 
				current = current->right;

			Node* temp = new Node;
			temp->item = item;
			temp->right = nullptr;
			temp->left = current;

			current->right = temp;
		}
		else
			PushFront(item);

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

		// TODO:
		/*Node* current = first_->right;

		current->left = nullptr;
		delete first_;
		current = first_;*/

		Node* temp = first_; 
		first_ = first_->right;
		if (first_)
			first_->left = nullptr;

		delete temp;

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

		// TODO:
		
		/*Node* current = first_;
		Node* precurrent = current;

		if (first_) {
			while (current->right)
			{	
				precurrent = current;
				current = current->right;			
			}
			precurrent->right = nullptr;
			
			
		}
		delete current;*/

		Node* current = first_;

		if (current->right)
		{
			while (current->right->right) // 아 이렇게 current  있고  있다면 계속 돌아라
			{
				current = current->right;
			}// 그럼 current  temp  null 이렇게 되겠네 

			Node* temp = current->right;
			current->right = current->right->right;
			//null 로 바로 연결 하고 temp 삭제 
			delete temp;
		}
		else {
			delete first_;
			first_ = nullptr;
		}


	}

	void Reverse()
	{
		// TODO:
		if (IsEmpty())
			return;
		else
		{
			Node* current = first_;
			Node* prev = nullptr;

			while (current)
			{
				prev = current;

				current = current->right;

				std::swap(prev->left, prev->right); // 와 이렇게 스왑으로 해결가능하네 



			}
			first_ = prev;
		}

		

	}

	T Front()
	{
		assert(first_);

		return first_->item; // TODO:
	}

	T Back()
	{
		assert(first_);

		Node* current = first_;
		while (current->right)
		{
			current = current->right;
		}

		return current->item; // TODO:
	}

protected:
	Node* first_ = nullptr;
};