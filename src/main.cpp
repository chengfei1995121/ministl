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
	String d("lmn");
	cout<<d<<endl;
	d.insert(3,"cf");
	cout<<d<<d.size()<<endl;
}
