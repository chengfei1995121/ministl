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
	String d("ijm");
	cout<<d<<endl;
	cout<<c.find("ab",0)<<endl;
	cout<<c<<c.size()<<c.capacity()<<endl;
}
