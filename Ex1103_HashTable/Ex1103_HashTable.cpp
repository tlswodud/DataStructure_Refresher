#include <iostream>
#include <string> // std::string

using namespace std;
/*
해슁 

키 와 벨류 쌍이 있을 때 key를 검색하여 가져오는것 

이진 보다 빠를 수 있을까 ? 

배열에서 값을 가져오고 저장하는건 O(1) 속도가 빠르다.

이걸 이용을 잘하면 속도를 더 빠르게 가능하지 않을까? 

*/
template<typename K, typename V>
class HashTable
{
public:
	struct Item
	{
		K key = K();
		V value = V();
	};

	HashTable(const int& cap = 8)
	{
		capacity_ = cap;
		table_ = new Item[capacity_];
	}

	~HashTable()
	{
		delete[] table_;
	}

	void Insert(const Item& item)
	{
		// TODO:

		size_t index = HashFunc(item.key); // 키를 인덱스로 사용 이런 해쉬펑션 이라한다
		//table_[index] = item;

	/*	if (!table_[index].key)
		{
			table_[index] = item;
		}
		else
		{
			while (table_[index].key)
			{
				index++;
			}
			table_[index] = item;

		}*/

		while (table_[index].key != K())index++; // 

		table_[index] = item;
	}

	V Get(const K& key)
	{
		// TODO: 못 찾으면 0을 반환
		size_t index = HashFunc(key);

		for (int i = 0; i < capacity_;i++)
		{
			index = (index + i) % capacity_;
			if (table_[index].key == key)
			{
				return table_[index].value;
			}
		}

		return 0;
	}

	// 정수 -> 해시값
	//size_t HashFunc(const int& key) // 해쉬펑션 64bit 부호가 없는 64bit 
	//{
	//	return key % capacity_;
	//}

	// 문자열을 정수 인덱스(해시값)로 변환
	// Horner's method
	size_t HashFunc(const string& s)
	{	
		size_t index = 0;
		int g = 31;

		for (int i = 0; i < s.size(); i++)
		{
			index += int(s.at(i)) + g *index;
		}
		return index % capacity_;
	}

	void Print()
	{
		for (int i = 0; i < capacity_; i++)
			cout << i << " : " << table_[i].key << " " << table_[i].value << endl;
		cout << endl;
	}

private:
	Item* table_ = nullptr;
	int capacity_ = 0;
};

int main()
{
	// 충돌 
	// - 개방 주소법: 선형 조사법
	// - 체이닝: 멤버 변수 Item* table_ 대신에 LinkedList<Item>* table_사용 

	// 키: int, 값: int 인 경우
	// 키의 범위가 아주 크고 아이템의 개수는 적을 경우
	//{
	//	using Item = HashTable<int, int>::Item;

	//	HashTable<int, int> h(8);

	//	h.Insert(Item{ 123, 456 }); // 아주아주 큰경우 해쉬 테이블을 무한히 올릴수 없음

	//	h.Print();

	//	cout << "Get 123 " << h.Get(123) << endl;

	//	h.Insert(Item{ 1000021, 9898 });

	//	h.Print();

	//	cout << "Get 1000021 " << h.Get(1000021) << endl;

	//	h.Insert(Item{ 1211, 999 }); // 충돌! 우연히 동일한 해쉬 키값으로 충돌 
	//	// 이거 괜찮나?
	//	//충돌 시에 다른 공간에 저장하는 개방 주소법 Open Addressing 
	//	h.Print();

	//	cout << "Get 123 " << h.Get(123) << endl;
	//	cout << "Get 1211 " << h.Get(1211) << endl;
	//}

	 //키: std::string, 값: int
	{
		using Item = HashTable<string, int>::Item;

		HashTable<string, int> h(8);

		h.Insert(Item{ "apple", 1 });
		h.Insert(Item{ "orange", 2 });
		h.Insert(Item{ "mandarin", 4 });

		h.Print();

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << endl;

		h.Print();

		h.Insert(Item{ "tomato", 4 });

		h.Print(); 

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << "pineapple " << h.Get("pineapple") << endl;
		cout << endl;
	}

	return 0;
}