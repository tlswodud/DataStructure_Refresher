#include <iostream>

#include "../shared/Stack.h"

using namespace std;

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;

/*
스텍을 쌓아서 0이면 가고 아니면 막히고 

*/

char maze[kNumRows][kNumCols] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '1', '0', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1'},
	{'1', '1', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze()
{
	for (int j = 0; j < kNumRows; j++)
	{
		for (int i = 0; i < kNumCols; i++)
			cout << maze[j][i] << " ";
		cout << endl;
	}
}

struct Pos
{
	int row;
	int col;

	// 디버깅을 위한 편의 기능
	friend ostream& operator<<(ostream& os, const Pos& pos) // c++ 문법과관련된것 보기좋게 출력 
	{
		cout << "(" << pos.row << ", " << pos.col << ")" << flush;
		return os;
	}
	/*
1)
operator<<는 뭐야?
우리가 cout << 변수; 할 때, 변수의 내용을 어떻게 보여줄지 컴퓨터에게 알려주는 방법이에요.

컴퓨터는 기본 자료형(int, double 등)은 알아서 출력하지만, 내가 만든 Pos 같은 건 어떻게 보여줄지 몰라요. 그래서 우리가 직접 알려줘야 해요.

2)
friend ostream& operator<<(ostream& os, const Pos& pos) 이건 뭐야?
cout << pos;가 쓰일 때 실행되는 함수에요.

os는 cout 같은 출력 도구(출력 스트림)이고,

pos는 출력할 내 Pos 객체예요.

3)
왜 friend야?
이 함수는 Pos 구조체 안에 있지만, Pos의 멤버 함수가 아니에요.

friend는 이 함수에게 Pos 안에 있는 row, col 같은 친구 멤버 변수들을 특별히 볼 수 있게 허락해주는 열쇠 같은 거예요.

(사실 여기서는 row와 col이 public이라서 안 써도 되지만 보통 이렇게 많이 써요.)

4)
마지막에 왜 return os; 해?
cout << pos1 << pos2;처럼 여러 개를 한 줄에 이어서 출력할 수 있게, 출력 스트림을 돌려주는 거예요.
	
	*/
};

//void RecurMaze(Pos p) // 재귀호출방식 
//{
//	const char mark = maze[p.row][p.col];
//
//	if (mark == 'G')
//	{
//		cout << "Found!" << endl;
//		return;
//	}
//
//	// 방문했던 적이 없고 ('X'가 아니고) 나는 새로운 배열을 만들어서 하는데 
//	// 벽도 아닌 경우 ('1'도 아닌 경우) // 갈수 있는길
//	if (mark != '1' && mark != 'X')
//	{
//		 //'x' 표시
//		 maze[p.row][p.col] = 'X';
//		 //옆으로 이동
//		 
//
//		 RecurMaze({p.row +1  , p.col});
//		 RecurMaze({ p.row - 1  , p.col });
//		 RecurMaze({ p.row , p.col +1 });
//		 RecurMaze({ p.row , p.col -1 });
//
//
//	} 
//} // 

////조기 종료가 가능한 버전
// if 로 1 반환하면 자동 종료되게 설정 
//int RecurMaze(Pos p)
//{
//	// TODO:
//	const char mark = maze[p.row][p.col];
//
//	if (mark == 'G')
//	{
//		cout << "Found" << endl;
//		return 1;
//	}
//
//
//	if (mark != '1' && mark != 'X' )
//	{
//		maze[p.row][p.col] = 'X';
//
//		if (mark != 'X' && mark != '1')
//		{
//			maze[p.row][p.col] = 'X';
//
//			if (RecurMaze({ p.col + 1 , p.row }))return 1 ;
//			if (RecurMaze({ p.col , p.row +1 }))return 1;
//			if (RecurMaze({ p.col -1 , p.row }))return 1;
//			if (RecurMaze({ p.col  , p.row -1 }))return 1;
//			
//		}
//	}
//
//	return 0;
//}

void StackMaze() // 스텍 풀이 
{
	Stack<Pos> s;

	Pos start = { 1, 1 }; // i = 1, j = 1  시작 지점
	//Pos start;
	//start.row = 1;
	//start.col = 1;

	s.Push(start); // s.Push({1, 1});

	// s.Print(); // 디버깅에 사용 가능

	while (!s.IsEmpty())
	{
		Pos p = s.Top(); // 미리 p 에 넣어줬구나 
		s.Pop();

		cout << p << " "; // 디버깅 출력 그래서 출력되는거고

		const char mark = maze[p.row][p.col];

		if (mark == 'G')
		{
			cout << "Found!" << endl;
			break;
		}

		// TODO:
		if (mark != '1' && mark != 'X') {
			maze[p.row][p.col] = 'X';

			s.Push({ p.row + 1 , p.col });
			s.Push({ p.row - 1 , p.col });
			s.Push({ p.row  , p.col + 1 });
			s.Push({ p.row  , p.col - 1 });

		}
	}
}

int main()
{
	PrintMaze();

	//RecurMaze({ 1, 1 });

	StackMaze();

	PrintMaze();

	return 0;
}

