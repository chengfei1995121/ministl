#include "Vector.h"
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
using namespace std;
int main()
{
	vector<int> b;
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	vector<int> a(b);
	cout<<a.size()<<endl;
	cout<<a.capacity()<<'\n'<<endl;
	a.erase(a.begin()+2);
	for(auto i=a.begin();i!=a.end();i++)
		cout<<*i<<endl;

	cout<<'\n'<<a.size()<<endl;
	cout<<a.capacity()<<endl;
	//cout<<d<<' '<<d<<d.capacity()<<endl;
	//cout<<c<<c.size()<<' '<<c.capacity()<<endl;
}
