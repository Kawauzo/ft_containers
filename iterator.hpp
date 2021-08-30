#ifndef ITERATORHPP
# define ITERATORHPP

// cstddef needed for ptrdiff_t
# include <cstddef>

namespace ft
{

// ****** Iterator Category Tags ******
// Empty structures used by iterator_traits
// to identify iterator categories

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};


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

	typedef random_access_iterator_tag iterator_category;
};

// define these types for const pointers
template <class T> class iterator_traits<const T*>
{
	typedef ptrdiff_t difference_type;

	typedef T value_type;

	typedef const T* pointer;

	typedef const T& reference;

	typedef random_access_iterator_tag iterator_category;
};
}

#endif
