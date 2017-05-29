#include "Vector.h"
void FunTest()
{
	Vector v1(5,8);
	cout<<"v1:"<<v1<<endl;
	Vector v2(v1);
	cout<<"v2:"<<v2<<endl;
	v1.Insert(2,10);
	cout<<"v1:"<<v1<<endl;
	v1.PushBack(100);
	cout<<"v1:"<<v1<<endl;
	v1.PopBack();
	cout<<"v1:"<<v1<<endl;
	v1.Assign(3,5);
	cout<<"v1:"<<v1<<endl;
	v1.At(3);
	cout<<v1<<endl;
	v1.Back();
	cout<<v1<<endl;
	v1.Capacity();
	cout<<v1<<endl;
}
int main()
{
	FunTest();
	system("pause");
	return 0;
}