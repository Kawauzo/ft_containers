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
    // Const conversion
    operator vec_iterator<const T> () const {
        return (vec_iterator<const T>(this->_ptr));
    }

    // Constructors
    vec_iterator():_ptr(NULL){}
    vec_iterator(vec_iterator const &it):_ptr(it._ptr){}

    vec_iterator(pointer p):_ptr(p){}

    // Assignement operator
    vec_iterator& operator=(const vec_iterator& it){
        _ptr = it._ptr;
        return *this;
    }

    // Member access operators
    value_type& operator * () const {return *_ptr;}
    value_type& operator [] (difference_type n) const {return * (_ptr + n);}
    pointer operator -> () const {return _ptr;}

    // Pre-Increment/Decrement (++i)
    vec_iterator& operator++() {_ptr++; return *this;}
    vec_iterator& operator--() {_ptr--; return *this;}

    // Post-Increment/Decrement (i++)
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

    // Needed for const comparisons
    pointer base() const {
        return _ptr;
    }
};

// Outside class definitions //

// const_iterator and iterator comparisons
/* for iterator == const_iterator */
template<typename T_L, typename T_R>
typename vec_iterator<T_L>::difference_type
operator==(const vec_iterator<T_L> lhs,
          const vec_iterator<T_R> rhs) {
    return (lhs.base() == rhs.base());
}

/* for iterator != const_iterator */
template<typename T_L, typename T_R>
typename vec_iterator<T_L>::difference_type
operator!=(const vec_iterator<T_L> lhs,
          const vec_iterator<T_R> rhs) {
    return (lhs.base() != rhs.base());
}

/* for iterator < const_iterator */
template<typename T_L, typename T_R>
typename vec_iterator<T_L>::difference_type
operator<(const vec_iterator<T_L> lhs,
          const vec_iterator<T_R> rhs) {
    return (lhs.base() < rhs.base());
}

/* for iterator > const_iterator */
template<typename T_L,
         typename T_R>
typename vec_iterator<T_L>::difference_type
operator>(const vec_iterator<T_L> lhs,
          const vec_iterator<T_R> rhs) {
    return (lhs.base() > rhs.base());
}

/* for iterator <= const_iterator */
template<typename T_L, typename T_R>
typename vec_iterator<T_L>::difference_type
operator<=(const vec_iterator<T_L> lhs,
          const vec_iterator<T_R> rhs) {
    return (lhs.base() <= rhs.base());
}

/* for iterator >= const_iterator */
template<typename T_L,
         typename T_R>
typename vec_iterator<T_L>::difference_type
operator>=(const vec_iterator<T_L> lhs,
          const vec_iterator<T_R> rhs) {
    return (lhs.base() >= rhs.base());
}

/* for iterator - const_iterator */
template<typename T_L, typename T_R>
typename vec_iterator<T_L>::difference_type
operator-(const vec_iterator<T_L> lhs,
          const vec_iterator<T_R> rhs) {
    return (lhs.base() - rhs.base());
}

// operator+ with difference_type as lhs
template <class T>
vec_iterator<T> operator+(typename vec_iterator<T>::difference_type n, vec_iterator<T> it) {
    vec_iterator<T> ret(it + n); return ret;
}

}
#endif
