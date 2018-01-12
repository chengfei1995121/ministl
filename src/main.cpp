#include "String.h"
#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
int main()
{
	String a("cf");
	//String d="f";
	string c("abcdefghijk");
	cout<<c<<endl;
	string d("lmn");
	cout<<d<<endl;
	d.insert(3,10,'c');
	cout<<d<<d.size()<<endl;
}
