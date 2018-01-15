#include "Vector.h"
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
using namespace std;
int main()
{
	Vector<int> a(4,100);
	a.push_back(5);
	cout<<a.size()<<endl;
	cout<<a.capacity()<<endl;
	cout<<*a.begin()<<endl;
	//cout<<d<<' '<<d<<d.capacity()<<endl;
	//cout<<c<<c.size()<<' '<<c.capacity()<<endl;
}
