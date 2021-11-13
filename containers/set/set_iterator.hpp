#ifndef SET_ITERATOR_HPP
# define SET_ITERATOR_HPP

// needed for iterator_traits
# include "../utils/type_traits.hpp"


namespace ft
{

template <class T, class node_type> class set_iterator
{
    public:
    // iterator_traits
    typedef T                                value_type;
    typedef ptrdiff_t                        difference_type;
    typedef T*                               pointer;
    typedef T&                               reference;
    typedef std::bidirectional_iterator_tag  iterator_category;

    private:
    node_type* _ptr; // only variable, iterator position


    public:
    // Const conversion
    operator set_iterator<const T, const node_type> () const {
        return (set_iterator<const T, const node_type> (this->_ptr));
    }
    // Constructors
    set_iterator():_ptr(NULL){}
    set_iterator(set_iterator const &it):_ptr(it._ptr){}

    set_iterator(node_type* p):_ptr(p){}

    // Assignement operator
    set_iterator& operator=(const set_iterator& it){
        _ptr = it._ptr;
        return *this;
    }

    // Member access operators
    value_type& operator * () const {return *_ptr->val;}
    pointer operator -> () const {return _ptr->val;}

    // Pre-increment
    set_iterator& operator++() {
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
    set_iterator operator++(int) { set_iterator copy(*this); ++*this; return copy;}

    // Pre-decrement
    set_iterator& operator--() {
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
    set_iterator operator--(int) { set_iterator copy(*this); --*this; return copy;}


    // Comparison operators
    bool operator==(set_iterator const &it) const { return _ptr == it._ptr; }
    bool operator!=(set_iterator const &it) const { return _ptr != it._ptr; }

    bool operator<(set_iterator const &it) const { return _ptr < it._ptr; }
    bool operator>(set_iterator const &it) const { return _ptr > it._ptr; }

    bool operator<=(set_iterator const &it) const { return _ptr <= it._ptr; }
    bool operator>=(set_iterator const &it) const { return _ptr >= it._ptr; }

    // Needed for const comparisons
        node_type* base() const {
            return _ptr;
        }

}; // end of set_iterator

/* for iterator != const_iterator */
template<typename T_L, typename N_L, typename T_R, typename N_R>
bool operator!=(const set_iterator<T_L, N_L> lhs,
          const set_iterator<T_R, N_R> rhs) {
    return (lhs.base() != rhs.base());
}

} // end of ft namespace

#endif

