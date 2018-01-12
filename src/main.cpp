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
	d.replace(2,1,c);
	cout<<d<<d.size()<<endl;
}
