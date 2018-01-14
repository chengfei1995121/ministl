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
	String d("cf");
	cout<<d<<endl;
	cout<<d<<' '<<d<<d.capacity()<<endl;
	cout<<c<<c.size()<<' '<<c.capacity()<<endl;
}
