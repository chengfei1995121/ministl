#ifndef __MINISTL__VECTOR_H
#define __MINISTL__VECTOR_H 
#include<memory>
#include<alloca.h>
#include<iostream>
using namespace std;
template<typename T>
class Vector 
{
	public:
		typedef T             value_type;
		typedef T*            iterator;
		typedef const T*      const_iterator;
		typedef T&            reference;
		typedef size_t        size_type;


		Vector():element(nullptr),first_free(nullptr),cap(nullptr){}
		Vector(size_t len,const T&);
		Vector(const Vector&);
		iterator begin() noexcept;
		iterator end() noexcept;
		const iterator cbegin() const noexcept;
		const iterator cend() const noexcept;
		size_t size()const {return first_free-element;}
		size_t capacity()const {return cap-element;}
		bool empty() const noexcept;
		void v_check();
		void push_back(const value_type&);
		T &operator[](size_t pos);
		Vector &operator=(const Vector &);
		void free();
		T &at(size_t pos);
		T &front();
		T &back();
		const T &front() const;
		const T &back() const;
		const T &at(size_t pos) const;
		T *data();
		const T *data() const noexcept;
		void pop_back();
		iterator insert(const_iterator pos,const T &);
		iterator insert(const_iterator pos,size_t len,const T &);
		iterator erase(const_iterator pos);
		void clear() noexcept;
		void swap(Vector &);
		void resize(size_t n);
		void resize(size_t n,const T &);
		void reserve(size_t n);
		~Vector();
	private:
		allocator<T>   alloc;
		static const size_t   npos=-1;
		void reallocate();
		T  *element;
		T  *first_free;
		T  *cap;
};
template<typename T> Vector<T>::Vector(const Vector &v1)
{
	auto newdata=alloc.allocate(v1.size());
	auto size=uninitialized_copy(v1.element,v1.first_free,newdata);
	element=newdata;
	first_free=cap=size;
}
template<typename T> Vector<T>::Vector(size_t len,const T& value)
{
	auto newdata=alloc.allocate(len);
	size_t i;
	for(i=0;i<len;i++)
		alloc.construct(newdata+i,value);
	element=newdata;
	first_free=cap=element+len;
}
template<typename T> Vector<T>::~Vector(){free();}

template<typename T> bool Vector<T>::empty() const noexcept 
{
	if(size())
		return false;
	else 
		return true;
}
template<typename T> void Vector<T>::v_check(){
	if(capacity()==size())
		reallocate();
}
template<typename T> typename Vector<T>::iterator Vector<T>::begin() noexcept
{
	return element;
}
template<typename T> typename Vector<T>::iterator Vector<T>::end() noexcept
{
	return first_free;
}
template<typename T> const typename Vector<T>::iterator Vector<T>::cbegin() const noexcept 
{
	return element;
}
template<typename T> const typename Vector<T>::iterator Vector<T>::cend() const noexcept 
{
	return first_free;
}
template<typename T> void Vector<T>::free()
{
	if(element)
	{
		for(auto p=first_free;p!=element;)
			alloc.destroy(--p);
		alloc.deallocate(element,cap-element);
	}
}
template<typename T> void Vector<T>::reallocate()
{
	size_t len=size()?2*size():1;
	auto newdata=alloc.allocate(len);
	auto dest=newdata;
	auto elem=element;
	for(size_t i=0;i<size();i++)
		alloc.construct(dest++,*elem++);
	free();
	first_free=dest;
	element=newdata;
	cap=element+len;
}
template<typename T> void Vector<T>::push_back(const value_type &value)
{
	v_check();
	alloc.construct(first_free++,value);
}
template<typename T> T &Vector<T>::operator[](size_t pos)
{
	return *(element+pos);
}
template<typename T> Vector<T> &Vector<T>::operator=(const Vector &v)
{
	auto newdata=alloc.allocate(v.size());
	free();
	auto n=uninitialized_copy(v.element,v.first_free,newdata);
	element=newdata;
	first_free=cap=n;
}
template<typename T> T &Vector<T>::at(size_t pos)
{
	if(element+pos<first_free)
		return *(element+pos);
	else 
	{
		cout<<"超出范围"<<endl;
		exit(-1);
	}
}
template<typename T> const T &Vector<T>::at(size_t pos) const 
{
	if(element+pos<first_free)
		return *(element+pos);
	else 
		{
			cout<<"超出范围"<<endl;
			exit(-1);
		}

}
template<typename T> T &Vector<T>::front()
{
	return *element;
}
template<typename T> T &Vector<T>::back()
{
	return *(first_free-1);
}
template<typename T> const T &Vector<T>::front() const
{
	return *element;
}
template<typename T> const T &Vector<T>::back() const
{
	return *(first_free-1);
}
template<typename T> T *Vector<T>::data()
{
	return element;
}
template<typename T> const T *Vector<T>::data() const noexcept 
{
	return element;
}
template<typename T> void Vector<T>::pop_back()
{
	if(element)
	{
		alloc.destroy(--first_free);
	}
}
template<typename T> typename Vector<T>::iterator Vector<T>::insert(const_iterator pos,const T &value)
{
	auto len=pos-element;
	v_check();
	alloc.construct(first_free++);
	for(auto i=first_free-1;i!=element+len;i--)
	{
		*i=*(i-1);	
	}
	*(element+len)=value;
	return element+len;
}
template<typename T> typename Vector<T>::iterator Vector<T>::insert(const_iterator pos,size_t len,const T &value)
{
	if(size()+len<=capacity())
	{
		auto pos_size=pos-element;
		for(size_t i=0;i<len;i++)
		{
			alloc.construct(first_free+i);
		}
		for(auto p=first_free-1;p!=pos-1;p--)
			*(p+len)=*p;
		for(size_t i=0;i<len;i++)
			*(element+pos_size+i)=value;
		first_free=first_free+len;
		return element+pos_size;
	}
	else {
	auto pos_size=pos-element;
	auto allocate_size=size()+len<(size()+len)*2?(size()+len)*2:size()+len;
	auto newdata=alloc.allocate(allocate_size);
	auto n=uninitialized_copy(element,element+pos_size,newdata);
	for(size_t i=0;i<len;i++)
		alloc.construct(n++,value);
	n=uninitialized_copy(element+pos_size,first_free,n);
	free();
	element=newdata;
	first_free=n;
	cap=element+allocate_size;
	return element+pos_size;
	}
}
template<typename T> typename Vector<T>::iterator Vector<T>::erase(const_iterator pos)
{
	auto pos_size=pos-element;
	for(auto i=element+pos_size;i!=first_free-1;i++)
		*i=*(i+1);
	alloc.destroy(--first_free);
	return element+pos_size;
}
template<typename T> void Vector<T>::clear() noexcept
{
	auto i=first_free;
	for(;i!=element;)
	{
		alloc.destroy(--i);
	}
	first_free=i;
}
template<typename T> void swap_value(T *&first,T *&second)
{
	T* t;
	t=first;
	first=second;
	second=t;
}
template<typename T> void Vector<T>::swap(Vector &v)
{
	swap_value(element,v.element);
	swap_value(first_free,v.first_free);
	swap_value(cap,v.cap);
}
template<typename T> void Vector<T>::resize(size_t n)
{
	if(n<size())
	{
		auto i=first_free;
		while(i!=element+n)
			alloc.destroy(--i);
		first_free=i;
	}
	else 
	{
		if(n<=capacity())
		{
			auto len=n-size();
			for(size_t i=0;i<len;i++)
				alloc.construct(first_free++,T());
		}
		else 
		{
			size_t allocate_size=n<size()*2?size()*2:n;
			auto newdata=alloc.allocate(allocate_size);
			auto copy_pos=uninitialized_copy(element,first_free,newdata);
			auto len=n-size();
			for(size_t i=0;i<len;i++)
				alloc.construct(copy_pos++,T());
			free();
			element=newdata;
			first_free=copy_pos;
			cap=newdata+allocate_size;
		}
	}
}
template<typename T> void Vector<T>::resize(size_t n,const T &value)
{
	if(n<size())
	{
		auto i=first_free;
		while(i!=element+n)
			alloc.destroy(--i);
		first_free=i;
	}
	else 
	{
		if(n<=capacity())
		{
			auto len=n-size();
			for(size_t i=0;i<len;i++)
				alloc.construct(first_free++,value);
		}
		else 
		{
			size_t allocate_size=n<size()*2?size()*2:n;
			auto newdata=alloc.allocate(allocate_size);
			auto copy_pos=uninitialized_copy(element,first_free,newdata);
			auto len=n-size();
			for(size_t i=0;i<len;i++)
				alloc.construct(copy_pos++,value);
			free();
			element=newdata;
			first_free=copy_pos;
			cap=newdata+allocate_size;
		}
	}

}
template<typename T> void Vector<T>::reserve(size_t n)
{
	if(n>capacity())
	{
		auto newdata=alloc.allocate(n);
		auto copy_pos=uninitialized_copy(element,first_free,newdata);
		free();
		element=newdata;
		first_free=copy_pos;
		cap=element+n;
	}
}
#endif
