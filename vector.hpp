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
	class reverse_iterator : public iterator
	{
	};
	typedef const reverse_iterator const_reverse_iterator;
	typedef typename allocator_type::size_type size_type;

	/*
	 * **************************************
	 * ************ Variables ***************
	 * **************************************
	*/
	private:
	allocator_type _al;
	T* _ar;
	size_type _sz;
	size_type _cp;

	/*
	 * **************************************
	 * ********* Member Functions ***********
	 * **************************************
	*/
	public:
	// - - - Constructors
	// - Default
	explicit vector(const allocator_type& alloc = allocator_type()):
		_al(alloc),
		_ar(0), _sz(0), _cp(0){}

	// - Fill
	explicit vector(size_type n,
					const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()):
		_al(alloc),
		_ar(_al.allocate(n)),
		_sz(n),
		_cp(n)
	{
		for (unsigned int i = 0; i < _sz; i++)
			_al.construct(_ar + i, val);
	}
	

	// - - - Destructor
	~vector()
	{
		for (unsigned int i = 0; i < _sz; i++)
			_al.destroy(_ar + i);
		_al.deallocate(_ar, _sz);
	}

};

}

#endif
