#include <iostream>

#include "../shared/AVL.h"

using namespace std;
/*
AVL TREE 

 균형을 잡는 거임 

 벨런스 = 왼쪽 서브트리의 높이 - 오른 쪽 서브트리의 높이

 벨런스가 -1 이상 1 이하면 좋은것으로 판단
     3                2             
   2                1   3     2 - 0 =  2
 1               

 벨런스 = 왼쪽 서브트리의 높이 - 오른 쪽 서브트리의 높이
 3 의 벨런스    2 
 2 일때 벨런스  1 

 2가 더 좋다 
어떤 노드의 벨런스가 1보다 크고 왼쪽 자식 노드의 벨런스가 0 이상 일 떄 RotateRight() 사용한다


 avl 트리에서는 균형을 잡는 경우는 3가지이다 
 
 2를 올려주는 거

 오른 쪽 이 더 치우치면 왼쪽으로 도는거 


*/
int main()
{
	using Item = AVL<int, char>::Item;

	AVL<int, char> bst;

	for (int i : { 9, 8, 7, 6, 5, 4, 3, 2, 1 })
		//for (int i : { 1, 2, 3, 4, 5, 6, 7, 8, 9 })
	{
		bst.Insert(Item{ i, char('A' + i) });
		bst.Print2D();
	}

	bst.Inorder(); // key에 대해 정렬

	cout << bst.RecurGet(5)->value << endl;
	cout << bst.RecurGet(3)->value << endl;
	cout << bst.RecurGet(7)->value << endl;
	cout << bst.RecurGet(1)->value << endl;
	cout << bst.RecurGet(4)->value << endl;

	for (int i : {5, 4, 7, 8, 9})
	{
		bst.Remove(i);
		bst.Print2D();
	}

	return 0;
}
