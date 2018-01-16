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
	vector<int> a(4,6);
	cout<<a.size()<<endl;
	cout<<a.capacity()<<'\n'<<endl;
	a.swap(b);
	for(auto i=0;i!=4;i++)
		cout<<*(a.begin()+i)<<endl;
	cout<<'\n'<<a.size()<<endl;
	cout<<a.capacity()<<endl;
	//cout<<d<<' '<<d<<d.capacity()<<endl;
	//cout<<c<<c.size()<<' '<<c.capacity()<<endl;
}
