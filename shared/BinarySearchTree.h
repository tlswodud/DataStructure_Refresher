#pragma once

#include <iomanip>
#include <cassert>
#include <iostream>

template<typename K, typename V>
class BinarySearchTree
{
public:
	struct Item // key와 value의 쌍(pair)
	{
		K key = K();	// first   키를 통해 찾는다 
		V value = V();	// second  
	};

	struct Node
	{
		Item item;

		Node* left = nullptr;
		Node* right = nullptr;
	};

	void Preorder()
	{
		using namespace std;
		Preorder(root_);
		cout << endl;
	}

	void Preorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			cout << node->item.key << " ";
			Preorder(node->left);
			Preorder(node->right);
		}
	}

	void Inorder()
	{
		using namespace std;
		Inorder(root_);
		cout << endl;
	}

	void Inorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			Inorder(node->left);
			cout << node->item.key << " "; // key값 기준 정렬 
			Inorder(node->right);
		}
	}

	Item* RecurGet(const K& key)
	{
		return RecurGet(root_, key); 
	}

	Item* RecurGet(Node* node, const K& key)
	{
		if (!node) return nullptr; // <- 동일한 키를 가진 노드를 찾지 못하면 nullptr을 반환하는 기능

		if (key < node->item.key) // 작다면 
			return RecurGet(node->left, key); // 왼쪽으로 가라 
		if (key > node->item.key) // 크다면 
			return RecurGet(node->right, key); // 오른쪽으로 

		return &node->item; // if (key == node->item.key) // 같다면 찾은거니까 
	}

	Item* IterGet(const K& key) // 재귀 호출 사용하지 않고 RecurGet 을 구현해라 
	{
		// TODO:
		Node* current = root_;
		while (current)
		{
			if (key < current->item.key) current = current->left;
			else if (key > current->item.key) current = current->right;
			else return &current->item;
		}
	}
	/*
	
	Item* IterGet(const K& key) // 재귀 호출 사용하지 않고 RecurGet 을 구현해라 
	{
		// TODO:
		Node* node = root_;

		while (key < node->item.key)
		{
			node = node->left;
		}

		while (key > node->item.key)
		{
			node = node->right;
		}
		return &node->item; // No matching
	}*/

	void Insert(const Item& item)
	{
		using namespace std;
		cout << "Insert " << item.key << item.value << endl;
		root_ = Insert(root_, item);
	}

	Node* Insert(Node* node, const Item& item) 
	{	
		if (!node) return new Node{ item , nullptr , nullptr }; // 들어온 노드가 널이라면 생성 , 자식이 없는 노드라는 뜻

		if (item.key < node->item.key)
		{
			node->left = Insert(node->left, item); // 현재 노드 보다 작다면 재귀적으로 끝까지 가서 left 에 넣어줌
		}
		else if (item.key > node->item.key)
		{
			node->right = Insert(node->right, item);
		}
		else
		{
			node->item = item;
		}
		return node;
	}

	void IterInsert(const Item& item) // 재귀 사용하지 않고 
	{
		// TODO:
		Node* p = root_;
		Node* pp = nullptr;

		while (p)
		{
			pp = p; // 현재 노드 부모로 기억한다 

			if (item.key < p->item.key) p = p->left;
			else if (item.key > p->item.key) p = p->right;

			else
			{
				p->item.value = item.value;
				return;
			}
		}
		
		p = new Node{ item , nullptr, nullptr }; // null 이 되면 여기에 넣어야함

		if (root_)
		{
			if (item.key < pp->item.key) pp->left = p;
			else pp->right = p;
		}
		else root_ = p;
	}

	Node* MinKeyLeft(Node* node) // 오른쪽 서브트리에서 가장 작은 값찾을떄 사용 이걸로 Remove 구현
	{
		assert(node);
		while (node->left)
			node = node->left;
		return node;
	}

	void Remove(const K& key)
	{
		using namespace std;
		cout << "Remove " << key << endl;
		root_ = Remove(root_, key);
	}
	/*
	제거 하고자 하는 값이 root라면 

	오른 쪽 트리의 가장 작은값 또는 왼쪽 트리의 가장 큰값을 root로 두면

	이진 트리의 특징을 유지 할 수 있다

	*/

	Node* Remove(Node* node, const K& key)
	{
		if (!node) return node;

		if (key < node->item.key)
			node->left = Remove(node->left, key);
		else if (key > node->item.key)
			node->right = Remove(node->right, key);
		else
		{
			// TODO: 여기에 root 삭제 시 이진트리 유지하고 구현  // 복사를 하면 좀 더 편하다?

			// 자식이 둘다 있거나 하나 만 있거나 하는 경우 구현
			if (!node->left)
			{
				Node* temp = node->right;

				delete node;

				return temp;

			}
			else if (!node->left)
			{
				Node* temp = node->left; // temp 에 노드 left 값을 넣고 
				 
				delete node;             // 노드를 삭제하고 

				return temp;            // temp 반환
			}
			
			Node* temp = MinKeyLeft(node->right); // 오른 쪽에서 가장 작은값을 temp 로 넣고 
			node->item = temp->item;              //  temp 의 아이템을 노드에 넣고 
			node->right = Remove(node->right, temp->item.key);  // temp 아이템 key 값을 삭제

		}


	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{
		if (!node) return 0;
		return 1 + std::max(Height(node->left), Height(node->right));
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename K, typename V>
void BinarySearchTree<K, V>::Print2D()
{
	using namespace std;
	cout << "Height = " << Height() << endl;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
	cout << endl;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item.key <= 1) ? 1 : (int)log10(p->item.key) + 1);
			cout << " " << p->item.key << p->item.value << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->left, lv - 1, d);
			DisplayLevel(p->right, lv - 1, d);
		}
	}
}
