﻿#include <iostream>
#include <cassert>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

template<typename T>
class AdjListGraph // Adjacent List Graph 인접 리스트 그래프 
{
public:
	struct Vertex
	{
		T item = T(); // 아이템 저장 
	};

	struct Node
	{
		//Vertex* vertex = nullptr;
		int vertex = -1; // vertex의 index 저장 안된거 
		Node* next = nullptr;
	};

	AdjListGraph(int max_vertices)
	{
		max_vertices_ = max_vertices; // capacity

		vertices_ = new Vertex[max_vertices_];
		list_ = new Node * [max_vertices_];
		for (int i = 0; i < max_vertices_; i++)
			list_[i] = nullptr;

		n_ = 0;
	}

	~AdjListGraph()
	{
		delete[] vertices_;
		delete[] list_;

		if (visited_)
			delete[] visited_;
	}

	void InsertVertex(T item)
	{
		vertices_[n_].item = item;
		n_++;
	}

	void InsertEdge(int u, int v) // 여기서 u, v는 인덱스
	{
		assert(u < n_ && v < n_);

		Node* temp = new Node{ v, list_[u] };
		list_[u] = temp;
	}

	int Capacity()
	{
		return max_vertices_;
	}

	void Print()
	{
		for (int v = 0; v < n_; v++)
		{
			cout << vertices_[v].item << " : ";

			Node* current = list_[v];
			while (current)
			{
				cout << vertices_[current->vertex].item << " ";
				current = current->next;
			}
			cout << endl;
		}

		cout << endl;
	}

	void DepthFirstTraversal()
	{
		ResetVisited();

		DepthFirstTraversal(0);

		cout << endl;
	}

	void DepthFirstTraversal(int v) // v는 인덱스
	{
		// TODO:재귀를 활용한 방식 

		visited_[v] = true;
		Node* current = list_[v];
		cout << vertices_[v].item << " ";
		
		while (current)
		{	
			if(!visited_[current->vertex])
				DepthFirstTraversal(current->vertex);
			
			current = current->next; //while 문을 통해 current 를 next로 바꿔주면서 
		}

	}

	void IterDFT()
	{
		// TODO:stack
		ResetVisited();

		int v = 0;

		Stack <int> s;
		s.Push(v);
		visited_[v] = true;

		while (!s.IsEmpty())
		{
			v = s.Top();
			s.Pop();

			cout << vertices_[v].item << " ";

			Node* current = list_[v]; // 연결리스트 사용

			while (current)
			{
				int w = current->vertex;
				if (!visited_[w])
				{
					s.Push(w);
					visited_[w] = true;

				}
				current = current->next;
			}
			cout << "stack  ";
			s.Print();
		}

	}

	void BreadthFirstTraversal()
	{
		// TODO: queue 
		int v = 0;

		Queue<int> q;

		ResetVisited();

		visited_[v] = true;
		q.Enqueue(v);

	

		while (!q.IsEmpty())
		{
			v = q.Front();
			q.Dequeue();

			cout << vertices_[v].item << " ";

			Node* current = list_[v];

			while (current)
			{
				int w = current->vertex;
				if (!visited_[w])
				{
					visited_[w] = true;
					q.Enqueue(w);
				}

				current = current->next;
			}
		}
		cout << "Queue ";
		q.Print();
		cout << endl;



	}

	void ResetVisited()
	{
		if (!visited_)
			visited_ = new bool[max_vertices_];
		for (int i = 0; i < max_vertices_; i++) visited_[i] = false; // 초기화
	}

private:
	Vertex* vertices_ = nullptr;
	Node** list_ = nullptr;     // 연결리스트 노드의 이중 포인터 
	int n_ = 0;					// size
	int max_vertices_ = 0;		// capacity

	bool* visited_ = nullptr;
};

int main()
{
	AdjListGraph<int> g(7);

	for (int i = 0; i < g.Capacity(); i++)
		g.InsertVertex(i);

	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);

	g.Print();

	g.DepthFirstTraversal();
	cout << endl;

	g.IterDFT();

	g.BreadthFirstTraversal();

	return 0;
}
