#ifndef MINISTL_STRING_H
#define MINISTL_STRING_H
#include<memory>
#include<iostream>
using namespace std;
class String{
	public:
		typedef char               value_type;
		typedef char*              iterator;
		typedef const char*        const_iterator;
		typedef size_t             size_type;
		typedef char*              pointer;
		typedef char&              reference;



		friend ostream &operator<<(ostream &os,const String &s);
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
		String(const String &s1,size_t pos,size_t len=npos);
		String(const char *c);
		String(size_t n,char c);
		String(const String &);
		String(char *,size_t);
		String& operator=(const String &);
		size_t size() const;
		iterator begin() const;
		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;
		iterator end() const;
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
		const char *data() const noexcept;
		size_t find(char c,size_t pos=0) const;
		size_t find(const String &,size_t pos=0)const;
		size_t find(const char *,size_t pos=0) const;
		char &back();
		const char &back()const;
		char &front();
		const char &front() const;
		String substr(size_t pos=0,size_t len=npos) const;
		void swap(String &);
		void swap(char *&,char *&);
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
