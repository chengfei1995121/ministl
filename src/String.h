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
		String(size_t n,char c);
		String(const String &);
		String& operator=(const String &);
		size_t size() const;
		char *begin() const;
		char *end() const;
		void free();
		char &operator[](size_t n);
		bool empty()const;
		size_t capacity()const;
		char at(size_t n);
		String &operator+=(const String &);
		String &operator+=(const char *);
		String &operator+=(const char);
		void check_size();
		void push_back(char c);
		String &replace(size_t pos,size_t len,const String &);
		String &insert(size_t pos,const String&);
		String &insert(size_t pos,const char *);
		String &insert(size_t pos,size_t n,const char);
		void clear();
		String &erase(size_t pos=0,size_t len=npos);
		size_t find(char c,size_t pos=0) const;
		size_t find(const String &,size_t pos=0)const;
		size_t find(const char *,size_t pos=0) const;
		~String(){
			free();
		}
	private:
		static const size_t npos=-1;
		static allocator<char> alloc;
		void reallocate();
		char *sstart;
		char *send;
		char *scap;
};
//allocator<char> String::alloc;
#endif
