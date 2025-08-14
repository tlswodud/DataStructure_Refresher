#include <iostream>

using namespace std;
/*
쭉나열되어있는 구조

Sequential Representation
순차 표현
하나씩 보는것은 좋지만

삭제 시에 , 삽입시에 하나씩 떙기고 밀어줘야했었음

삭제, 삽입이 정--- 말 많으면 비효율적이다

데이터를 넣다 뻈다면 뭐가 좋을까?

데이터를 흩어놓으면 ? 좋을것 같다
접근하기 위해서 주소를 지정하고

데이터의 주소를 어떻게 관리할까 ?
다 한곳에 모아놓는다면 ? 주소의 배열이 되고  , 그렇다면
순차 표현을 거쳐가야하기에 불편하다

정답은?
다음 노드의 주소를 각각의 노드가 가지고 있으면 된다

주소를 알고 있는다.

하나하나 접근하는 속도는 느리지만

삭제 시에는 빠르다

노드 주소를 다다음 위치로 바꿔주면 된다
메모리도 삭제해주고


"List"
원하는 위치에 데이터를 넣었다 뻈다

CPU에서 메모리로 데이터를 읽어들일 때는 우리가 요청하는 것 딱 하나씩만 읽어들이는 방식이 아니라
메모리 대역폭에 맞춰서 주변 데이터를 블럭 단위로 읽어와서
일단 캐쉬에 넣어둡니다.
그 다음에 요청하는 데이터가 캐쉬에 들어 있다면
재빠르게 가져오고 그렇지 않다면 다시 메인 메모리에서
데이터를 또 다시 블럭 단위로 가져옵니다.
그래서 배열 같은 순차적 자료구조에서
순서대로 데이터를 읽어오는 것은 캐쉬 효과 덕분에
아주 빠릅니다.


*/
struct Node
{
	int item = 0;	  // <- 큰 데이터도 가능
	Node* next = nullptr;

	friend ostream& operator<<(ostream& os, const Node& n)
	{
		cout << &n <<" " << n.item << " "<< n.next << flush;
		return os;
	}
};

void RecurPrint(Node* node)
{
	// TODO:

	/*if (node->item == 1)
	{
		cout << *node << endl;
	}


	Node* current = node->next;

	if (current == nullptr)return;

	cout << *current << endl;

	RecurPrint(current);*/

	if (node)
	{
		RecurPrint(node->next);
		cout << *node << endl;

	}

}

void IterPrint(Node* node)
{
	// TODO:
	//while (1)
	//{	
	//	Node* current = node->next;
	//	//재귀하고 이거 하니까 헷갈렸네 
	//	//node는 기존 노드 first 로 하겠고 
	//	//nullptr 이 안되니까 무한반복 
	//	if (current == nullptr)return;
	//	cout << *current << endl;				
	//}

	Node* current = node;

	while (current)
	{
		cout << *current << endl;
		
		current = current->next;

	}
}

int main()
{
	// ListArray와 비교

	Node* first = nullptr;
	first = new Node;
	first->item = 1;
	first->next = nullptr;

	Node* second = nullptr;
	second = new Node;
	second->item = 2;
	second->next = nullptr;

	Node* third = nullptr;
	third = new Node;
	third->item = 3;
	third->next = nullptr;

	Node* fourth = nullptr;
	fourth = new Node;
	fourth->item = 4;
	fourth->next = nullptr;

	Node* fifth = nullptr;
	fifth = new Node;
	fifth->item = 5;
	fifth->next = nullptr;

	// 계속 추가 가능

	/*cout << first  <<" "<< *first << endl;
	cout << second <<" "<< *second << endl;
	cout << third  <<" "<< *third << endl;
	cout << fourth <<" "<< *fourth << endl;
	cout << fifth  <<" "<< *fifth << endl;
	cout << endl;*/

	Node* nodes[] = { first , second , third , fourth , fifth }; 
	// 이렇게 주소 배열저장

	// 연결 관계 만들어 주기
	// first->next = second;
	// TODO:
	// 마지막
	first->next = second;
	second->next = third;
	third->next = fourth;
	fourth->next = fifth;
	fifth->next = nullptr;

	cout << *(first) << endl;
	cout << *(first->next) << endl;
	cout << *(first->next->next) << endl;
	cout << *(first->next->next->next) << endl;
	cout << *(first->next->next->next->next) << endl;
	//cout << *(first->next->next->next->next->next) << endl; // 오류

	cout << endl;

	// 임시 변수 사용
	{
		Node* current = first;
		cout << *current << endl;
		
		current = first->next; // 이게 맞았다 
		cout << *current <<endl;


	// TODO:
		cout << endl;
	}

	// 재귀 호출 이용
	RecurPrint(first);
	cout << endl;

	// 반복문 이용
	IterPrint(first);
	cout << endl;

	// TODO: 데이터 삭제

	Node* current = first;

	while (current)
	{
		Node* temp = current;

		cout << "delete  " << *temp << endl;

		current = current->next; // 다음 넘어가고 

		delete temp; // 그 다음에 삭제를 해줘야겠지 당연한거네

	}

	return 0;
}
/*

링크 메모리

데이터 외에 추가로 링크 포인터도 저장을 해야하기 때문에 
메모리가 더 많이 필요합니다. 
삽입/삭제가 편리하다는 장점을 살릴 수 없는 경우에는 
메모리 낭비가 되겠죠. 
반면에 삽입과 삭제가 아주 빈번하게 일어날때는 
그 정도 메모리를 추가로 사용하는 것은 
현명한 투자라고 볼 수도 있습니다.
아이템 자체의 사이즈가 아주 큰 경우에도 
포인터 하나가 추가되는 것 정도는 
큰 낭비라고 볼 수 없습니다.

*/