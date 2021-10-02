#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream> // TEMPORARY // TESTING

# include <memory> // needed for std::allocator
# include <limits> // needed for vector::max_size()

// type_traits, contains iterator_traits, enable_if, is_integral
# include "../utils/type_traits.hpp"
// iterators, contains reverse_iterator
# include "../utils/iterators.hpp"
// iterators, specific to vec
# include "vec_iterator.hpp"

// needed for macro below
#include <sstream>
// macro for fast string_streams
# define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

// macro for capacity increse
# define NEWCP (_sz == 0 ? 1 : _sz * 2)

namespace ft
{

template <class T, class Alloc = std::allocator<T> > class vector
{
public:

    /*
     * **************************************
     * ********** Member Types **************
     * **************************************
    */

    typedef T       value_type;
    typedef Alloc   allocator_type;

    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    /*
     * **************************************
     * ********* Iterator Types *************
     * **************************************
    */

    typedef vec_iterator<value_type, false>        iterator;
    typedef vec_iterator<const value_type, true>   const_iterator;

    typedef reverse_iterator<const_iterator>       const_reverse_iterator;
    typedef reverse_iterator<iterator>             reverse_iterator;



    /*
     * **************************************
     * ************ Variables ***************
     * **************************************
    */
private:

    allocator_type  _al;    // Allocator
    pointer         _ar;    // Underlying array
    size_type       _sz;    // this.size()
    size_type       _cp;    // this.capacity()

    /*
     * **************************************
     * ********* Private Functions **********
     * **************************************
     *
     * These are used to avoid rewriting code
    */
private:
    // Destroys and deallocate all vector content
    void empty_self() {
        for (unsigned int i = 0; i < _sz; i++)
            _al.destroy(_ar + i);
        if (_cp)
            _al.deallocate(_ar, _cp);
    }

    void realloc_self(size_type new_cp) {
        pointer old_ar = _ar;

        _ar = _al.allocate(new_cp);
        for (size_type i = 0; i < _sz; i++)
            _al.construct(_ar + i, *(old_ar + i));

        for (size_type i = 0; i < _sz; i++)
            _al.destroy(old_ar + i);
        _al.deallocate(old_ar, _cp);

        _cp = new_cp;
    }

    /*
     * **************************************
     * ********* Member Functions ***********
     * **************************************
    */
public:

    // ***** Constructors *****

    // Constructs an empty container with the given allocator alloc
    explicit vector(const allocator_type& alloc = allocator_type()):
        _al(alloc),
        _ar(0), _sz(0), _cp(0){}

    // Fill
    // Constructs a container with n elements.
    // Each element is a copy of val
    explicit vector(size_type n,
                    const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type()):
        _al(alloc),
        _ar(0),
        _sz(n),
        _cp(n)
    {
        if (n)
            _ar = _al.allocate(n);
        else
            _ar = 0;
        for (unsigned int i = 0; i < _sz; i++)
            _al.construct(_ar + i, val);
    }

    // Range:
    // Constructs a container with as many elements as the range [first,last),
    // with each element constructed from its corresponding element in that range,
    // in the same order.
    template <class InputIt>
    vector(typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type first, InputIt last,
            const allocator_type& alloc = allocator_type()):
        _al(alloc),
        _ar(0),
        _sz(0),
        _cp(0)
    {
        insert(end(), first, last);
    }

    // Copy:
    vector (const vector& cpy):
        _al(cpy._al),
        _ar(0),
        _sz(cpy._sz),
        _cp(cpy._cp)
    {
        if (_cp)
            _ar = _al.allocate(_cp);
        for (unsigned int i = 0; i < _sz; i++)
            _al.construct(_ar + i, cpy[i]);
    }

    // ***** Destructor *****
    ~vector(){ empty_self(); }

    // ***** Assignment operator *****
    vector& operator=(const vector& cpy) {
        empty_self();
       _sz = cpy._sz;
       _cp = cpy._cp;
       if (_cp)
           _ar = _al.allocate(_cp);
       for (unsigned int i = 0; i < _sz; i++)
            _al.construct(_ar + i, cpy[i]);
    }


    /*
     * **************************************
     * ************ Iterators ***************
     * **************************************
    */

    iterator begin() { iterator ret(_ar); return ret; }
    const_iterator begin() const { const_iterator ret(_ar); return ret; }

    reverse_iterator rbegin() { reverse_iterator ret(end()); return ret; }
    const_reverse_iterator rbegin() const { const_reverse_iterator ret(end()); return ret; }

    iterator end() { iterator ret(_ar + _sz); return ret; }
    const_iterator end() const { const_iterator ret(_ar + _sz); return ret; }

    reverse_iterator rend() { reverse_iterator ret(_ar); return ret; }
    const_reverse_iterator rend() const { const_reverse_iterator ret(_ar); return ret; }


    /*
     * **************************************
     * ************* Capacity ***************
     * **************************************
    */

    size_type size() const { return _sz; }

    // This is ugly but basicly it just divides max memory by size of T, and make sure it's above 1
    size_type max_size() const {
        return std::numeric_limits<difference_type>::max() / (sizeof(value_type) / 2 < 1 ? 1 : sizeof(value_type) / 2);
    }

    size_type capacity() const { return _cp; }

    bool empty() const { return !_sz  ? true : false; }

    // Resizes the container to contain n elements.
    // - If the current size is greater than n,
    //   the container is reduced to its first count elements.
    // - If the current size is less than n,
    //   additional copies of val are inserted
    void resize (size_type n, value_type val = value_type()) {
        if (n < _sz)
            for (size_type i = n; i < _sz; i++)
                _al.destroy(_ar + i);
        else if (_sz < n)
            insert(end(), n - _sz, val);
        _sz = n;
    }


    void reserve(size_type n){
        if (n > max_size())
            throw std::length_error("vector::reserve");
        if (n > _cp)
            realloc_self(n);
    }


    /*
     * **************************************
     * ********** Element Access ************
     * **************************************
    */

    reference       operator[](size_type pos)       { return *(_ar + pos);}
    const_reference operator[](size_type pos) const { return *(_ar + pos);}

private:
    // Used to throw the same exception
    // as std::vector when trying at() out of bounds
    void _at_range_check(size_type n) {
        if ( n >= _sz)
            throw (std::length_error(SSTR("vector::_M_range_check: __n (which is "
                   << n << ") >= this->size() (which is " << _sz << ')')));
    }
public:
    reference       at(size_type pos)       { _at_range_check(pos); return *(_ar + pos);}
    const_reference at(size_type pos) const { _at_range_check(pos); return *(_ar + pos);}



    /*
     * **************************************
     * ************ Modifiers ***************
     * **************************************
    */

    // Push back
    void push_back (const value_type& val){
        if (_sz >= _cp) {
            pointer old_ar = _ar;
            _ar = _al.allocate(NEWCP);
            for (size_type i = 0; i < _sz; i++)
                _al.construct(_ar + i, *(old_ar + i));
            _al.construct(_ar + _sz, val);
            for (size_type i = 0; i < _sz; i++)
                _al.destroy(old_ar + i);
            _al.deallocate(old_ar, _cp);
            _cp = NEWCP;
        }
        else
            _al.construct(_ar + _sz, val);
        ++_sz;
    }

    // Pop Back
    void pop_back() { _al.destroy(_ar + --_sz); }


    // Inserts value before pos
    iterator insert( iterator pos, const T& value ) {
        size_type goal = pos - begin();

        if (!_sz && _cp)
            _al.construct(_ar + goal, value);
        else if (_sz < _cp) {
            size_type i = _sz;
            _al.construct(_ar + i, *(_ar + i - 1));
            i--;
            while (i > goal) {
                *(_ar + i) = *(_ar + i - 1);
                i--;
            }
            *(_ar + goal) = value;
        }
        else {
            pointer xar = _ar;
            _ar = _al.allocate(NEWCP);
            size_type i = 0;
            while (i < goal) {
                _al.construct(_ar + i, *(xar + i));
                i++;
            }
            _al.construct(_ar + i, value);
            while (i < _sz) {
                 _al.construct(_ar + i + 1, *(xar + i));
                 i++;
            }
            while (i > 0)
                _al.destroy(xar + --i);
            if (_cp)
                _al.deallocate(xar, _cp);
            _cp = NEWCP;
        }
        _sz++;
        return iterator(_ar + goal);
    }

    // Inserts count copies of the value before pos
    void insert( iterator pos, size_type count, const T& value ) {
        size_type goal = pos - begin();
        size_type new_sz = _sz + count;
        size_type i = 0;

        if (count == 0)
            return;
        if (count == 1)
            return (void) insert(pos, value);
        if (!_sz && _cp)
            while (i < new_sz)
               _al.construct(_ar + i++, value);
        else if (new_sz < _cp) {
            while (new_sz - i > _sz) {
                if (_sz - i > goal)
                    _al.construct(_ar + new_sz - i, *(_ar +_sz - i));
                else
                    _al.construct(_ar + new_sz - i, value);
                i++;
            }
            while (new_sz - i >= goal) {
                if (new_sz - i > goal + count)
                    _ar[new_sz - i] = *(_ar + _sz - i);
                else
                    _ar[new_sz - i] = value;
                i++;
            }
        }
        else {
            pointer old_ar = _ar;
            _ar = _al.allocate(std::max( NEWCP, new_sz));
            while (i < goal) {
                _al.construct(_ar + i, *(old_ar + i));
                i++;
            }
            while (i < goal + count)
                _al.construct(_ar + i++, value);
            while (i < new_sz) {
                _al.construct(_ar + i, *(old_ar + i - count));
                i++;
            }
            for (i = 0; i < _sz; i++)
                _al.destroy(old_ar + i);
            if (_cp)
                _al.deallocate(old_ar, _cp);
            _cp = std::max( NEWCP, new_sz);
        }
        _sz = new_sz;
    }

    template <class InputIt>
    void insert(iterator pos,
                typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type first,
                InputIt last)
    {
        _insert_pv(pos, first, last,
                  typename iterator_traits<InputIt>::iterator_category());
    }

private:
    template <class InputIt>
    void _insert_pv(iterator pos, InputIt first, InputIt last, std::input_iterator_tag) {
        if (!_cp)
            while (first != last) {
                pos = insert(pos, *first);
                ++first;
                ++pos;
            }
        else {
            vector tmp(first, last);
            insert(pos, tmp.begin(), tmp.end());
        }
    }

    template <class InputIt>
    void _insert_pv(iterator pos, InputIt first, InputIt last, std::forward_iterator_tag) {
        size_type goal = pos - begin();
        size_type range = last - first;
        size_type new_sz = _sz + range;
        size_type i = 0;

        if (range == 0)
            return;
        if (new_sz < _cp) {
            while (new_sz - i > _sz) {
                if (_sz - i > goal)
                    _al.construct(_ar + new_sz - i, *(_ar +_sz - i));
                else
                    _al.construct(_ar + new_sz - i, value_type());
                i++;
            }
            while (new_sz - i > goal + range) {
                _ar[new_sz - i] = *(_ar + _sz - i);
                i++;
            }
            while (first != last)
                *(_ar + goal++) = *first++;
        }
        // Adapter ce qu' il y a en dessous ET aussi retester le insert count parceque il y a des trucs chelous dedans (premier if entre autres)
        else {
            pointer old_ar = _ar;
            _ar = _al.allocate(std::max(NEWCP, new_sz));
            while (i < goal) {
                _al.construct(_ar + i, *(old_ar + i));
                i++;
            }
            while (i < goal + range)
                _al.construct(_ar + i++, *first++);
            while (i < new_sz) {
                _al.construct(_ar + i, *(old_ar + i - range));
                i++;
            }
            for (i = 0; i < _sz; i++)
                _al.destroy(old_ar + i);
            if (_cp)
                _al.deallocate(old_ar, _cp);
            _cp = std::max(NEWCP, new_sz);
        }
        _sz = new_sz;

    }

public:

    void erase( iterator pos ) {
        size_type ptr = pos - begin();
        while (ptr < _sz - 1) {
            *(_ar + ptr) = *(_ar + ptr + 1);
            ptr++;
        }
        _al.destroy(_ar + _sz--);
    }

    void swap(vector &x) {
        pointer    tmp_ar = x._ar;
        size_type  tmp_sz = x._sz;
        size_type  tmp_cp = x._cp;

        x._ar = _ar;
        x._sz = _sz;
        x._cp = _cp;

        _ar = tmp_ar;
        _sz = tmp_sz;
        _cp = tmp_cp;
    }

    void clear() {
        for (size_type i = 0; i < _sz; i++)
            _al.destroy(_ar + i);
        _sz = 0;
    }

    /*
     * **************************************
     * ************ Allocator ***************
     * **************************************
    */

    allocator_type get_allocator() const { return _al;}


};



}

# undef NEWCP
#endif
