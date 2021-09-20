#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

// cstddef needed for ptrdiff_t
# include <cstddef>

// iterator include needed for xxx_iterator_tags
# include <iterator>

namespace ft
{

// ****** iterator_traits ******
// Defines properties common to all iterators :
// difference_type:
//  Type to express the result of subtracting one iterator from another.
//
// value_type:
//  The type of the element the iterator can point to.
//
// pointer:
//  The type of a pointer to an element the iterator can point to.
//
// reference:
//  The type of a reference to an element the iterator can point to.
//
// iterator_category:
//  The iterator category. It can be one of those defined above

// obtain these types from the iterator itself
template <class Iterator> struct iterator_traits
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


// ****** iterator_traits ******
template <bool Cond, class T = void> struct enable_if {};
template <class T> struct enable_if<true, T> { typedef T type; };

// ****** is_integral ******
//  Implementation of is_integral
//  struct that has a boolean value which is set to false,
//  except if the type passed to it is one of these:
//  - bool
//  - char
//  - char16_t
//  - char32_t
//  - wchar_t
//  - signed char
//  - short int
//  - int
//  - long int
//  - long long int
//  - unsigned char
//  - unsigned short int
//  - unsigned int
//  - unsigned long int
//  - unsigned long long int
//

// Basis of is_integral struct
template <bool B, typename T>
struct is_integral_base {
 typedef T type;
 static const bool value = B;
};

// This template inherits from the base struct above,
// and sets its value depending on the type passed to it,
// the first one is generic and sets it to false
// all the specilizations below it are set to true
template <typename> struct is_integral_type :
    public is_integral_base<false, bool> {};

template <> struct is_integral_type<bool> :
    public is_integral_base<true, bool> {};
template <> struct is_integral_type<char> :
    public is_integral_base<true, char> {};
template <> struct is_integral_type<signed char> :
    public is_integral_base<true, signed char> {};
template <> struct is_integral_type<short int> :
    public is_integral_base<true, short int> {};
template <> struct is_integral_type<int> :
    public is_integral_base<true, int> {};
template <> struct is_integral_type<long int> :
    public is_integral_base<true, long int> {};
template <> struct is_integral_type<long long int> :
    public is_integral_base<true, long long int> {};
template <> struct is_integral_type<unsigned char> :
    public is_integral_base<true, unsigned char> {};
template <> struct is_integral_type<unsigned short int> :
    public is_integral_base<true, unsigned short int> {};
template <> struct is_integral_type<unsigned int> :
    public is_integral_base<true, unsigned int> {};
template <> struct is_integral_type<unsigned long int> :
    public is_integral_base<true, unsigned long int> {};
template <> struct is_integral_type<unsigned long long int> :
    public is_integral_base<true, unsigned long long int> {};

// Final is_integral template, which will be the one we really use
// It passes the T type to is_integral_type
template <typename T>
struct is_integral : public is_integral_type<T> { };

// ***** end *****

}
#endif
