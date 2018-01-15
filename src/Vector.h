#ifndef __MINISTL__VECTOR_H
#define __MINISTL__VECTOR_H 
#include<memory>
#include<alloca.h>
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
		T *begin() noexcept;
		T *end() noexcept;
		const T *begin() const noexcept;
		const T *end() const noexcept;
		size_t size()const {return first_free-element;}
		size_t capacity()const {return cap-element;}
		void v_check();
		void push_back(const value_type&);
		T &operator[](size_t n);
		void free();
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
template<typename T> void Vector<T>::v_check(){
	if(capacity()==size())
		reallocate();
}
template<typename T> T* Vector<T>::begin() noexcept
{
	return element;
}
template<typename T> T* Vector<T>::end() noexcept
{
	return first_free;
}
template<typename T> const T* Vector<T>::begin() const noexcept 
{
	return element;
}
template<typename T> const T* Vector<T>::end() const noexcept 
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
template<typename T> T &Vector<T>::operator[](size_t n)
{
	return *(element+n);
}
#endif
