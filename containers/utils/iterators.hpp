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
    value_type& operator*() {
        iterator_type cpy(_base);
        return *(--cpy); // <== returns the content of prev
    }
    value_type& operator [] (difference_type n){
        iterator_type cpy(_base);
        return * (--cpy - n);
    }
    pointer operator -> (){
        iterator_type cpy(_base);
        return --cpy; // <== returns the content of prev
    }

    // Pre-Increment/Decrement (++i)
    reverse_iterator& operator++() { --_base; return *this; }
    reverse_iterator& operator--() { ++_base; return *this; }

    // Post-Increment/Decrement (i++)
    reverse_iterator operator++(int) {reverse_iterator copy(*this); _base--; return copy;}
    reverse_iterator operator--(int) {reverse_iterator copy(*this); _base++; return copy;}

    // Arithmetic operators
    reverse_iterator operator+(difference_type n) const{ reverse_iterator ret(_base - n); return ret; }
    reverse_iterator operator-(difference_type n) const{ reverse_iterator ret(_base + n); return ret; }

    // Arithmetic Assignement operators
    reverse_iterator& operator+=(difference_type n) { _base -= n; return *this; }
    reverse_iterator& operator-=(difference_type n) { _base += n; return *this; }

    bool operator!=(reverse_iterator const &it) const {
        return _base != it._base;
    }

    iterator_type base() const {return _base;}
};

}

#endif
