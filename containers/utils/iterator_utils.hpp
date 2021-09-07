#ifndef ITERATORHPP
# define ITERATORHPP

// cstddef needed for ptrdiff_t
# include <cstddef>

// iterator include needed for xxx_iterator_tags
# include <iterator>

namespace ft
{

// ****** iterator_traits ******
// Defines properties common to all iterators :
// difference_type:
// 	Type to express the result of subtracting one iterator from another.
//
// value_type:
// 	The type of the element the iterator can point to.
//
// pointer:
//	The type of a pointer to an element the iterator can point to.
//
// reference:
//  The type of a reference to an element the iterator can point to.
//
// iterator_category:
//  The iterator category. It can be one of those defined above

// obtain these types from the iterator itself
template <class Iterator> class iterator_traits
{
	typedef typename Iterator::difference_type difference_type;

	typedef typename Iterator::value_type value_type;

	typedef typename Iterator::pointer pointer;

	typedef typename Iterator::reference reference;

	typedef typename Iterator::iterator_category iterator_category;
};

// define these types for pointers
template <class T> class iterator_traits<T*>
{
	typedef ptrdiff_t difference_type;

	typedef T value_type;

	typedef T* pointer;

	typedef T& reference;

	typedef std::random_access_iterator_tag iterator_category;
};

// define these types for const pointers
template <class T> class iterator_traits<const T*>
{
	typedef ptrdiff_t difference_type;

	typedef T value_type;

	typedef const T* pointer;

	typedef const T& reference;

	typedef std::random_access_iterator_tag iterator_category;
};
}

#endif
