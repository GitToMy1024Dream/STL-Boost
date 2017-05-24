//test.c
#include "List.h"
void FunTest()
{
	List<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	v.PushFront(6);
	v.PushFront(7);
	v.PushFront(8);
	v.PushFront(9);
	v.PushFront(10);
	v.PopBack();
	v.PopFront();
	v.Erase(--v.End());	
	v.Clear();
	List<int>::Iterator it;
 
	for (it = v.Begin(); it != v.End(); it++)
	{
		cout << *it << "  ";
	}
	cout << endl;
	//List<int> v2(v);
	
	//List<int> v2(v);
}
int main()
{
	FunTest();
	system("pause");
	return 0;
}