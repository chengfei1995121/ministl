#include "String.h"
#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
int main()
{
	String a("cf");
	//String d="f";
	String c("abcdefghijk");
//	cout<<c<<endl;
	String d(c,3,5);
	cout<<d<<endl;
	d.swap(c);
	cout<<d.size()<<' '<<d<<d.capacity()<<endl;
	cout<<c<<c.size()<<' '<<c.capacity()<<endl;
}
