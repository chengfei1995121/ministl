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
	cout<<c<<endl;
	string d("lmn");
	cout<<d<<endl;
	c.erase(3,5);
	cout<<c<<c.size()<<c.capacity()<<endl;
}
