#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{
	/*				
	 * Member Types	
	*/				
	typedef T					value_type;
	typedef Alloc	 			allocator_type;
	typedef value_type&		 	reference;
	typedef const value_type&	const_reference;
	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;
	class iterator
	{
	};
	typedef const iterator const_iterator;
	class reverse_iterator : public iterator
	{
	};
	typedef const reverse_iterator const_reverse_iterator;

	/*
	 * Variables
	*/
	private:
	T* _arr;
	Alloc _all;

	/*
	 * Member Functions
	*/
	public:
};

}

#endif
