#ifndef VEC_ITERATOR_HPP
# define VEC_ITERATOR_HPP

// needed for iterator_traits
# include "../utils/type_traits.hpp"

namespace ft
{

template <class T> class vec_iterator
{
    public:
    // iterator_traits
    typedef T                               value_type;
    typedef ptrdiff_t                       difference_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::random_access_iterator_tag iterator_category;

    private:
    T* _ptr; // only variable, iterator position

    public:
    // Constructors
    vec_iterator():_ptr(NULL){}
    vec_iterator(vec_iterator const &it):_ptr(it._ptr){}
    vec_iterator(pointer p):_ptr(p){}

    // Assignement operator
    vec_iterator& operator=(const vec_iterator& it){ _ptr = it._ptr;
        return *this;
    }

    // Member access operators
    value_type& operator * (){return *_ptr;}
    value_type& operator [] (difference_type n){return * (_ptr + n);}
    pointer operator -> (){return _ptr;}

    // Pre-Increment/Decrement
    vec_iterator& operator++() {_ptr++; return *this;}
    vec_iterator& operator--() {_ptr--; return *this;}

    // Post-Increment/Decrement
    vec_iterator operator++(int) {vec_iterator copy(*this); _ptr++; return copy;}
    vec_iterator operator--(int) {vec_iterator copy(*this); _ptr--; return copy;}

    // Arithmetic operators
    vec_iterator operator+(difference_type n) const{ vec_iterator ret(_ptr + n); return ret; }
    vec_iterator operator-(difference_type n) const{ vec_iterator ret(_ptr - n); return ret; }
    difference_type operator-(vec_iterator const &it) const{ difference_type ret = _ptr - it._ptr; return ret; }

    // Arithmetic Assignement operators
    vec_iterator& operator+=(difference_type n) { _ptr += n; return *this; }
    vec_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }


    // Comparison operators
    bool operator==(vec_iterator const &it) const { return _ptr == it._ptr; }
    bool operator!=(vec_iterator const &it) const { return _ptr != it._ptr; }

    bool operator<(vec_iterator const &it) const { return _ptr < it._ptr; }
    bool operator>(vec_iterator const &it) const { return _ptr > it._ptr; }

    bool operator<=(vec_iterator const &it) const { return _ptr <= it._ptr; }
    bool operator>=(vec_iterator const &it) const { return _ptr >= it._ptr; }
};

// Outside class definitions //

// operator+ with difference_type as lhs
template <class T>
vec_iterator<T> operator+(typename vec_iterator<T>::difference_type n, vec_iterator<T> it)
{ vec_iterator<T> ret(it + n); return ret; }

}
#endif
