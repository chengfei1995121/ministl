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
	String d("cf");
	char e[100];
	auto f=c.copy(e,3,5);
	e[f]='\0';
	cout<<e<<endl;
	//cout<<d<<' '<<d<<d.capacity()<<endl;
	//cout<<c<<c.size()<<' '<<c.capacity()<<endl;
}
