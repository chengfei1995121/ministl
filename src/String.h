#ifndef MINISTL_STRING_H
#define MINISTL_STRING_H
#include<memory>
#include<iostream>
using namespace std;
class String{
	public:
		friend ostream &operator<<(ostream &os,String &s);
		friend 	bool operator==(const String &s1,const String &s2);
		friend bool operator<(const String &s1,const String &s2);
		friend bool operator<=(const String &s1,const String &s2);
		friend bool operator>(const String &s1,const String &s2);
		friend bool operator>=(const String &s1,const String &s2);
		friend bool operator!=(const String &s1,const String &s2);
		friend String operator+(const String &s1,const String &s2);
		friend String operator+(const String &s1,const char *c);
		friend String operator+(const char *c,const String &s1);
		String():sstart(nullptr),send(nullptr),scap(nullptr){}
		String(const char *c);
		String(int n,char c);
		String(const String &);
		String& operator=(const String &);
		int size() const;
		char *begin() const;
		char *end() const;
		void free();
		char &operator[](int n);
		bool empty()const;
		int capacity()const;
		char at(int n)const;
		String &operator+=(const String &);
		String &operator+=(const char *);
		String &operator+=(const char);
		void check_size();
		void push_back(char c);
		String &replace(int pos,int len,const String &);
		String &insert(int pos,const String&);
		String &insert(int pos,const char *);
		~String(){
			free();
		}
	private:
		static allocator<char> alloc;
		void reallocate();
		char *sstart;
		char *send;
		char *scap;
};
//allocator<char> String::alloc;
#endif
