#ifndef SPAN_H__
#define SPAN_H__
#include<cstddef>
#include<iterator>
#include<stdexcept>
#include<utility>

template<typename T>
class span
{
	T *b,*e;
public:
	span()=default;
	template<typename X>
	span(X *_b,X *_e):b((T*)(_b)),e((T*)(_e)){}
	template<typename X>
	span(X *_b,std::size_t s):b((T*)(_b)),e(b+s){}
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	reference at(size_type i)
	{
		if(i<e-b)
			return b[i];
		throw std::out_of_range("span<T> out of range");
	}
	const_reference at(size_type i) const
	{
		if(i<e-b)
			return b[i];
		throw std::out_of_range("span<T> out of range");
	}
	reference operator[](size_type i)
	{
		return b[i];
	}
	const_reference operator[](size_type i) const
	{
		return b[i];
	}
	reference front()
	{
		return *b;
	}
	const_reference front() const
	{
		return *b;
	}
	reference back()
	{
		return e[-1];
	}
	const_reference back() const
	{
		return e[-1];
	}
	size_type size() const noexcept
	{
		return e-b;
	}
	size_type max_size() const
	{
		return -1;
	}
	bool empty() const noexcept
	{
		return b==e;
	}
	void swap(const span& other) noexcept
	{
		using std::swap;
		swap(b,other.b);
		swap(e,other.e);
	}
	
	T* data() noexcept
	{
		return b;
	}
	
	const T* data() const noexcept
	{
		return b;
	}
	
	const_iterator begin() const noexcept
	{
		return b;
	}
	iterator begin() noexcept
	{
		return b;
	}
	const_iterator cbegin() const noexcept
	{
		return b;
	}
	const_iterator end() const noexcept
	{
		return e;
	}
	iterator end() noexcept
	{
		return e;
	}
	const_iterator cend() const noexcept
	{
		return e;
	}
	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(e);
	}
	const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(e);
	}
	const_reverse_iterator crbegin() const noexcept
	{
		return const_reverse_iterator(e);
	}
	reverse_iterator rend() noexcept
	{
		return reverse_iterator(b);
	}
	const_reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator(b);
	}
	const_reverse_iterator crend() const noexcept
	{
		return const_reverse_iterator(b);
	}
};

#endif