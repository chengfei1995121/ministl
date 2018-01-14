#include"String.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
allocator<char> String::alloc;
String::String(const char *c){
	size_t n=strlen(c);
	auto newdata=alloc.allocate(n);
	uninitialized_copy(c,c+strlen(c),newdata);
	sstart=newdata;
	send=scap=sstart+n;
}
String::String(size_t n,char c){
	size_t i=0;
	auto newdata=alloc.allocate(n);
	while(i!=n)
	{
		alloc.construct(newdata++,c);
		i++;
	}
	sstart=newdata;
	send=scap=sstart+n;
}
String::String(const String &S)
{
	auto newdata=alloc.allocate(S.end()-S.begin());
	uninitialized_copy(S.begin(),S.end(),newdata);
	sstart=newdata;
	send=scap=sstart+S.size();
}
String &String::operator=(const String &s)
{
	auto newdata=alloc.allocate(s.end()-s.begin());
	free();
	uninitialized_copy(s.begin(),s.end(),newdata);
	sstart=newdata;
	send=scap=sstart+s.size();
	return *this;
}
void String::free()
{
	if(sstart)
	{
		for(auto p=send;p!=sstart;)
		{
			alloc.destroy(--p);
		}
		alloc.deallocate(sstart,scap-send);
	}
}
size_t String::size() const
{
	return send-sstart;	
}
char *String::begin() const 
{
	return sstart;
}
char *String::end() const
{
	return send;
}
ostream &operator<<(ostream &os,const String &s)
{
	auto data=s.sstart;
	while(data!=s.send)
	{
		os<<(*data);
		data++;
	}
	return os;
}
char &String::operator[](size_t pos)
{
		return *(sstart+pos);
}
bool String::empty() const
{
	if(size())
		return true;
	else 
		return false;
}
size_t String::capacity() const
{
	return scap-sstart;
}
char String::at(size_t pos)
{
	if(pos>=size())
	{
		cout<<"越界"<<endl;
		exit(-1);
	}
	else 
		return *(sstart+pos);
}
String &String::operator+=(const String &s)
{
	if(size()+s.size()<capacity())
	{
		for(auto p=s.begin();p!=s.end();p++)
		{
			*(send)=*p;
			send++;
		}
	}
	else 
	{
		auto newdata=alloc.allocate(size()+s.size());
		auto q=uninitialized_copy(sstart,send,newdata);
		q=uninitialized_copy(s.begin(),s.end(),q);
		free();
		sstart=newdata;
		send=scap=q;
	}
	return *this;
}
bool operator==(const String &s1,const String &s2)
{
	if(strcmp(s1.sstart,s2.sstart)==0)
	{
		return true;
	}
	else 
		return false;
}
bool operator<(const String &s1,const String &s2)
{
	if(strcmp(s1.sstart,s2.sstart)<0)
		return true;
	else 
		return false;
}
bool operator<=(const String &s1,const String &s2)
{
	if(strcmp(s1.sstart,s2.sstart)<=0)
		return true;
	else 
		return false;
}
bool operator>(const String &s1,const String &s2)
{
	if(strcmp(s1.sstart,s2.sstart)>0)
		return true;
	else 
		return false;
}
bool operator>=(const String &s1,const String &s2)
{
	if(strcmp(s1.sstart,s2.sstart)>=0)
		return true;
	else 
		return false;
}
bool operator!=(const String &s1,const String &s2)
{
	if(strcmp(s1.sstart,s2.sstart)!=0)
		return true;
	else 
		return false;
}
void String::check_size()
{
	if(capacity()==size())
	{
		reallocate();
	}
}
void String::reallocate()
{
	auto p=size()?2*size():1;
	auto newdata=alloc.allocate(p);
	auto n=uninitialized_copy(sstart,send,newdata);
	free();
	sstart=newdata;
	send=n;
	scap=sstart+p;
}
void String::push_back(char c)
{
	check_size();
	alloc.construct(send++,c);
}
String &String::operator+=(const char *c)
{
	int n=strlen(c);
	for(int i=0;i<n;i++)
	{
		push_back(c[i]);
	}
	return *this;
}
String &String::operator+=(const char c)
{
	push_back(c);
	return *this;

}
String operator+(const String &s1,const String &s2)
{
	allocator<char> alloc;
	String s3;
	auto newdata=alloc.allocate(s1.size()+s2.size());
	auto n=uninitialized_copy(s1.sstart,s1.send,newdata);
	auto p=uninitialized_copy(s2.sstart,s2.send,n);
	s3.sstart=newdata;
	s3.send=p;
	s3.scap=s3.sstart+s1.size()+s2.size();
	return s3;
}
String operator+(const String &s1,const char *c)
{
	allocator<char> alloc;
	String s3;
	auto newdata=alloc.allocate(s1.size());
	auto n=uninitialized_copy(s1.sstart,s1.send,newdata);
	s3.sstart=newdata;
	s3.send=n;
	s3.scap=s3.sstart+s1.size();
	int len=strlen(c);
	for(int i=0;i<len;i++)
	{
		s3.push_back(c[i]);
	}
	return s3;
}
String operator+(const char *c,const String &s1)
{
	allocator<char> alloc;
	String s3;
	int len=strlen(c);
	auto newdata=alloc.allocate(len+s1.size());
	auto n=uninitialized_copy(c,c+len,newdata);
	auto p=uninitialized_copy(s1.sstart,s1.send,n);
	s3.sstart=newdata;
	s3.send=p;
	s3.scap=s3.sstart+s1.size()+len;
	return s3;
}
String &String::replace(size_t pos,size_t len,const String &s1)
{
	if(len>=s1.size())
	{
		if(len+pos+sstart<scap)
		{
		for(size_t i=0;i<s1.size();i++)
		{
			*(sstart+pos+i)=*(s1.sstart+i);
		}
		auto st=sstart+pos+s1.size();
		auto elen=len-s1.size();
		if(elen!=0)
		{
		while(st+elen!=send)
		{
			*st=*(st+elen);
			st++;
		}
		send=st;
		}
		}
		else 
		{
			cout<<"超出范围"<<endl;
		}
	}
	else 
	{
		if(capacity()>size()-len+s1.size())
		{
			auto ylen=s1.size()-len;
			auto st=sstart+pos+len;
			for(size_t i=0;i<ylen;i++)
			{
				alloc.construct(send+i,'0');
			}
			auto p=send;
			while(p!=st)
			{
				p--;
				*(p+ylen)=*p;
			}
			send=send+ylen;
			for(size_t i=0;i<s1.size();i++)
			{
				*(sstart+pos+i)=*(s1.sstart+i);
			}
		}
		else 
		{
			auto newdata=alloc.allocate(size()-len+s1.size());
			auto n=uninitialized_copy(sstart,sstart+pos,newdata);
			n=uninitialized_copy(s1.sstart,s1.send,n);
			n=uninitialized_copy(sstart+pos+len,send,n);
			free();
			sstart=newdata;
			send=n;
			scap=n;
		}
	}
	return *this;
}
String &String::insert(size_t pos,const String &s1)
{
	if(size()+s1.size()<capacity())
	{
		auto len=s1.size();
		for(size_t i=0;i<len;i++)
		{
			alloc.construct(send+i,'0');
		}
		auto p=send;
		auto start=sstart+pos;
		while(p!=sstart+pos)
		{
			p--;
			*(p+len)=*(p);
		}
		send=send+len;
		for(size_t i=0;i<len;i++)
		{
			*(++start)=*(s1.sstart+i);
		}
	}
	else 
	{
		auto newdata=alloc.allocate(size()+s1.size());
		auto n=uninitialized_copy(sstart,sstart+pos,newdata);
		n=uninitialized_copy(s1.sstart,s1.send,n);
		n=uninitialized_copy(sstart+pos,send,n);
		sstart=newdata;
		send=scap=n;
	}
	return *this;
}
String &String::insert(size_t pos,const char *c)
{
	const size_t len=strlen(c);
	if(size()+len<capacity())
	{
		for(size_t i=0;i<len;i++)
		{
			alloc.construct(send+i,'0');
		}
		auto p=send;
		auto start=sstart+pos;
		while(p!=sstart+pos)
		{
			p--;
			*(p+len)=*(p);
		}
		send=send+len;
		for(size_t i=0;i<len;i++)
		{
			*(++start)=*(c+i);
		}
	}
	else 
	{
		auto newdata=alloc.allocate(size()+len);
		auto n=uninitialized_copy(sstart,sstart+pos,newdata);
		n=uninitialized_copy(c,c+len,n);
		n=uninitialized_copy(sstart+pos,send,n);
		sstart=newdata;
		send=scap=n;
	}
	return *this;
}
String &String::insert(size_t pos,size_t n,const char c)
{
	if(size()+n<capacity())
	{
		for(size_t i=0;i<n;i++)
		{
			alloc.construct(send+i,'0');
		}
		auto p=send;
		auto start=sstart+pos+n;
		while(p!=sstart+pos)
		{
			p--;
			*(p+n)=*(p);
		}
		send=send+n;
		for(size_t i=0;i<n;i++)
		{
			*(++start)=c;
		
	}
	}
	else 
	{
		auto newdata=alloc.allocate(size()+n);
		auto clen=uninitialized_copy(sstart,sstart+pos,newdata);
		for(size_t i=0;i<n;i++)
		{
			alloc.construct(clen+i,c);
		}
		clen=uninitialized_copy(sstart+pos,send,clen+n);
		sstart=newdata;
		send=scap=clen;
	}
	return *this;
}
void String::clear()
{
	auto p=send;
	while(p!=sstart)
	{
		alloc.destroy(--p);
	}
	send=p;
}
String &String::erase(size_t pos,size_t len)
{
	if(pos+len>=size()||len>size())
	{
		auto p=sstart+pos;
		while(p!=send)
		{
			alloc.destroy(p++);
		}
		send=sstart+pos;
	}
	else 
	{
		for(size_t i=0;i<len;i++)
		{
			alloc.destroy(sstart+pos+i);
		}
		auto p=sstart+pos+len;
		for(;p!=send;p++)
			*(p-len)=*p;
		for(p=p-len;p!=send;p++)
			alloc.destroy(p);
		send=p-len;
	}
	return *this;
}
size_t String::find(char c,size_t pos) const
{
	for(auto p=sstart+pos;p!=send;p++)
	{
		if(p>=send)
			break;
		if((*p)==c)
			return p-sstart;
	}
	return npos;
}
size_t String::find(const String &s1,size_t pos) const 
{
	if(s1.size()>(size()+pos))
		return npos;
	for(auto p=sstart+pos;p+s1.size()<=send;p++)
	{
		auto q=p;
		auto s1q=s1.sstart;
		while(*q==*s1q&&s1q<s1.send)
		{
			q++;
			s1q++;
		}
		if(s1q==s1.send)
			return p-sstart;
	}
	return npos;
}
size_t String::find(const char *c,size_t pos) const 
{
	auto len=strlen(c);
	if(len>(size()-pos))
		return npos;
	for(auto p=sstart+pos;p+len<=send;p++)
	{
		auto q=p;
		auto s1q=c;
		while(*q==*s1q&&*s1q!='\0')
		{
			q++;
			s1q++;
		}
		if(*s1q=='\0')
			return p-sstart;
		
	}
	return npos;
}
char &String::back()
{
	return *(send-1);
}
const char &String::back() const
{
	return *(send-1); 
}
char &String::front()
{
	return *(sstart);
}
const char &String::front() const 
{
	return *(sstart);
}
String String::substr(size_t pos,size_t len) const 
{
	if(sstart+pos>=sstart)
	{
		cout<<"超出范围"<<endl;
		exit(-1);
	}
	if(len==npos||sstart+pos+len>=send)
		len=send-(sstart+pos);
	auto newdata=alloc.allocate(pos+len);
	auto n=uninitialized_copy(sstart+pos,sstart+pos+len,newdata);
	String s;
	s.sstart=newdata;
	s.send=s.scap=n;
	return s;
}
void String::swap(char **c1,char **c2)
{
	char *t=*c1;
	*c1=*c2;
	*c2=t;
}
void String::swap(String &s1)
{
	swap(&sstart,&s1.sstart);
	swap(&send,&s1.send);
	swap(&scap,&s1.scap);
}
