#include <iostream>
#include <cassert>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;
/*
그래프 

TREE 
Graph 는 트리를 확장한것 
노드 연결에 제한이 없다 

Vertex 정점
Edge 간선

Vertex에서 vertex로 간다면 화살표로 양방향은 없이 

*/

template<typename T>
class AdjMatGraph // Adjacent Matrix Graph
{
public:
	struct Vertex // Node
	{
		T item = T(); // 정수 뿐 아니라 다양하게 가능하다 
	};

	AdjMatGraph(int max_vertices)
	{
		max_vertices_ = max_vertices; // capacity

		matrix_ = new int* [max_vertices_]; 
		for (int r = 0; r < max_vertices_; r++) {
			matrix_[r] = new int[max_vertices_];
			for (int c = 0; c < max_vertices_; c++)
				matrix_[r][c] = 0;
		}

		vertices_ = new Vertex[max_vertices_];

		n_ = 0;
	}

	~AdjMatGraph()
	{
		delete[] vertices_;

		for (int i = 0; i < max_vertices_; i++)
			delete[] matrix_[i];
		delete[] matrix_;

		if (visited_)
			delete[] visited_;
	}

	void PrintMatrix()
	{
		using namespace std;
		if (n_)
			for (int r = 0; r < n_; r++) {
				for (int c = 0; c < n_; c++)
					cout << matrix_[r][c] << ", ";
				cout << endl;
			}
		else
			cout << "Empty" << endl;

		cout << endl;
	}

	void InsertVertex(T item)
	{
		vertices_[n_].item = item;
		n_++;
	}

	void InsertEdge(int u, int v) // 여기서 u, v는 인덱스
	{
		assert(u < n_ && v < n_);

		// TODO:
		matrix_[u][v] = 1;
	}

	int Capacity()
	{
		return max_vertices_;
	}

	void DepthFirstTraversal()
	{
		ResetVisited();

		DepthFirstTraversal(0);

		cout << endl;
	}

	void DepthFirstTraversal(int v) // v는 인덱스
	{
		// if (visited_[v]) return; // <- 불필요

		visited_[v] = true;
		cout << vertices_[v].item << " ";
		for (int w = 0; w < n_; w++)
			if (matrix_[v][w] && !visited_[w]) // <- 대신에 여기서 꼭 !visited_[w] 있어야 함
				DepthFirstTraversal(w);
	}



	void IterDFT()
	{
		ResetVisited();
		int v = 0; // 0번에서 시작
		Stack<int> s;
		s.Push(v);
		while (!s.IsEmpty())
		{
			v = s.Top();
			s.Pop();
			if (!visited_[v])
			{
				cout << vertices_[v].item << " ";
				visited_[v] = true;
				//for (int w = 0; w < n_; w++) <- 위키피디아 버전 그대로
				for (int w = n_ - 1; w >= 0; w--) //  < -출력 순서 동일하게 하려고 역순 사용
				{
					if (matrix_[v][w]) {
						s.Push(w);
					}
				}
				cout << "Stack :";
				s.Print();
				// cout << endl;
			}
		}
		cout << endl;
	}

	void BreadthFirstTraversal()
	{
		int v = 0; // 0번에서 시작

		Queue<int> q;

		ResetVisited();

		visited_[v] = true;
		q.Enqueue(v);

		while (!q.IsEmpty())
		{
			v = q.Front();
			q.Dequeue();

			cout << vertices_[v].item << " ";

			for (int w = 0; w < n_;w++)
			{
				if (matrix_[v][w] && !visited_[w])
				{
					visited_[w] = true;
					q.Enqueue(w);
				}

			}
			cout << "Queue : ";
			q.Print();
			cout << endl;

		}


	}

	void ResetVisited()
	{
		if (!visited_)
			visited_ = new bool[max_vertices_];
		for (int i = 0; i < max_vertices_; i++) visited_[i] = false; // 초기화
	}

private:
	int** matrix_ = nullptr; 
	Vertex* vertices_ = nullptr;
	int n_ = 0;					// size
	int max_vertices_ = 0;		// capacity 최대 저장 개수 

	bool* visited_ = nullptr;  // 
};

int main()
{
	// 정점(vertex), 간선(edge)

	AdjMatGraph<int> g(7);

	for (int i = 0; i < g.Capacity(); i++)
		g.InsertVertex(i);

	/*
	0번에서 1번을 간후 온김에 연결된 곳으로 간다 depth first search  싶이 우선 

	stack 으로 넣고 다음 근처에 있는 것들을 넣어주고  

	0번에서 1번가고 0번으로 가서 2번으로 간다 breath first search 너비 우선 
	*/

	/*
	// 위키피디아 버전
	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);
	g.InsertEdge(3, 0);	g.InsertEdge(0, 3);
	g.InsertEdge(4, 0);	g.InsertEdge(0, 4);
	*/

	// 강의 영상 버전
	g.InsertEdge(0, 2);	g.InsertEdge(2, 0);
	g.InsertEdge(0, 1);	g.InsertEdge(1, 0);
	g.InsertEdge(1, 4);	g.InsertEdge(4, 1);
	g.InsertEdge(1, 3);	g.InsertEdge(3, 1);
	g.InsertEdge(2, 4);	g.InsertEdge(4, 2);
	g.InsertEdge(3, 6);	g.InsertEdge(6, 3);
	g.InsertEdge(4, 6);	g.InsertEdge(6, 4);
	g.InsertEdge(5, 6);	g.InsertEdge(6, 5);

	g.PrintMatrix();

	g.DepthFirstTraversal();

	g.BreadthFirstTraversal();

	return 0;
}