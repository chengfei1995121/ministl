#include "Vector.h"
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
using namespace std;
int main()
{
	Vector<int> b;
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	cout<<b.size()<<endl;
	cout<<b.capacity()<<'\n'<<endl;
	b.insert(b.begin(),10,10);
	b.insert(b.begin(),2,10);
	cout<<'\n'<<b.size()<<endl;
	cout<<b.capacity()<<endl;
	//cout<<d<<' '<<d<<d.capacity()<<endl;
	//cout<<c<<c.size()<<' '<<c.capacity()<<endl;
}
