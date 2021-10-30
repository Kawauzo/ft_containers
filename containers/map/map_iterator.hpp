#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

// needed for iterator_traits
# include "../utils/type_traits.hpp"


namespace ft
{

template <class T, class node_type> class map_iterator
{
    public:
    // iterator_traits
    typedef T                                value_type;
    typedef ptrdiff_t                        difference_type;
    typedef T*                               pointer;
    typedef T&                               reference;
    typedef std::bidirectional_iterator_tag  iterator_category;

    private:
    public: // TEMPORARY, FOR TESTING PURPOSE
    node_type* _ptr; // only variable, iterator position


    public:
    // Constructors
    map_iterator():_ptr(NULL){}
    map_iterator(map_iterator const &it):_ptr(it._ptr){}

    map_iterator(node_type* p):_ptr(p){}

    // Assignement operator
    map_iterator& operator=(const map_iterator& it){
        _ptr = it._ptr;
        return *this;
    }

    value_type& operator * () const {return *_ptr->val;}

    // Pre-increment
    map_iterator& operator++() {
        if (_ptr->r){
            _ptr = _ptr->r;
            while (_ptr->l)
                _ptr = _ptr->l;
            return *this;
        }
        if (!_ptr->r /*&& !_ptr->l*/){
            node_type* parent = _ptr->parent;
            while (true){
                if (_ptr == parent->l){
                    _ptr = parent;
                    return *this;
                }
                _ptr = parent;
                parent = _ptr->parent;
            }
        }
        return *this;
    }

    // Post-increment
    map_iterator operator++(int) { map_iterator copy(*this); ++*this; return copy;}

    // Pre-decrement
    map_iterator& operator--() {
        if (_ptr->l){
            _ptr = _ptr->l;
            while (_ptr->r)
                _ptr = _ptr->r;
            return *this;
        }
        if (!_ptr->l /*&& !_ptr->l*/){
            node_type* parent = _ptr->parent;
            while (true){
                if (_ptr == parent->r){
                    _ptr = parent;
                    return *this;
                }
                _ptr = parent;
                parent = _ptr->parent;
            }
        }
        return *this;
    }

    // Post-decrement
    map_iterator operator--(int) { map_iterator copy(*this); --*this; return copy;}


    // Comparison operators
    bool operator==(map_iterator const &it) const { return _ptr == it._ptr; }
    bool operator!=(map_iterator const &it) const { return _ptr != it._ptr; }

    bool operator<(map_iterator const &it) const { return _ptr < it._ptr; }
    bool operator>(map_iterator const &it) const { return _ptr > it._ptr; }

    bool operator<=(map_iterator const &it) const { return _ptr <= it._ptr; }
    bool operator>=(map_iterator const &it) const { return _ptr >= it._ptr; }


}; // end of map_iterator

} // end of ft namespace

#endif

