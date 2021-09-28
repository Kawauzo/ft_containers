#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "type_traits.hpp"

namespace ft
{


/*
 * Reverse iterator Template
*/

template<typename Iter>
class reverse_iterator {

    // Underlying base iterator
    Iter _base;

public:
    // Typedefs, based on Iter iterator_traits
    typedef Iter iterator_type;
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;


    explicit reverse_iterator(iterator_type itr): _base(itr) {}

    // Member access operators
    value_type& operator*() const {
        return *(_base - 1); // <== returns the content of prev
    }
    value_type& operator [] (difference_type n) const {
        return _base[-n - 1];
    }
    pointer operator -> () const {
        //iterator_type cpy(_base);
        //--cpy;
        return (_base - 1).operator->();
    }

    // Pre-Increment/Decrement (++i)
    reverse_iterator& operator++() { --_base; return *this; }
    reverse_iterator& operator--() { ++_base; return *this; }

    // Post-Increment/Decrement (i++)
    reverse_iterator operator++(int) { reverse_iterator copy(*this); _base--; return copy;}
    reverse_iterator operator--(int) { reverse_iterator copy(*this); _base++; return copy;}

    // Arithmetic operators
    reverse_iterator operator+(difference_type n) const{ reverse_iterator ret(_base - n); return ret; }
    reverse_iterator operator-(difference_type n) const{ reverse_iterator ret(_base + n); return ret; }

    // Arithmetic Assignement operators
    reverse_iterator& operator+=(difference_type n) { _base -= n; return *this; }
    reverse_iterator& operator-=(difference_type n) { _base += n; return *this; }

    iterator_type base() const {return _base;}
};

// Outside class operators
template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
    { return lhs.base() == rhs.base(); }

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
    { return lhs.base() != rhs.base(); }

template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
    { return lhs.base() > rhs.base(); }

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
    { return lhs.base() >= rhs.base(); }

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
    { return lhs.base() < rhs.base(); }

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
    { return lhs.base() <= rhs.base(); }

// Arithmetic: n +- it
template< class Iter >
reverse_iterator<Iter>
    operator+( typename reverse_iterator<Iter>::difference_type n,
               const reverse_iterator<Iter>& it ) {
    reverse_iterator<Iter> cpy(it);
    return it + n;
}

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type
    operator-( const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs ){
    return rhs.base() - lhs.base();
}

}

#endif
