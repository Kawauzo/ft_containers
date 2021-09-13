#ifndef VECTOR_HPP
# define VECTOR_HPP

// needed for std::allocator
# include <memory>

// iterators, specific to vec
# include "vec_iterator.hpp"

// macro for capacity increse
# define NEWCP(cp) (cp == 0 ? 1 : cp * 2)

namespace ft
{

template <class T, class Alloc = std::allocator<T> > class vector
{
    public:

    /*
     * **************************************
     * ************ Iterators ***************
     * **************************************
    */

    typedef vec_iterator<T>         iterator;
    typedef vec_iterator<const T>   const_iterator;

    /*
     * **************************************
     * ********** Member Types **************
     * **************************************
    */

    typedef T                   value_type;
    typedef Alloc               allocator_type;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;

    typedef typename allocator_type::size_type size_type;




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
     * ********* Member Functions ***********
     * **************************************
    */
    public:

    // ***** Constructors *****
    //
    // - Default
    explicit vector(const allocator_type& alloc = allocator_type()):
        _al(alloc),
        _ar(0), _sz(0), _cp(0){}
    //
    // - Fill
    explicit vector(size_type n,
                    const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type()):
        _al(alloc),
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


    // ***** Destructor *****
    ~vector()
    {
        for (unsigned int i = 0; i < _sz; i++)
            _al.destroy(_ar + i);
        _al.deallocate(_ar, _cp);
    }

    // ***** Iterators *****
    iterator begin(){ iterator ret(_ar); return ret; }
    const_iterator begin() const { const_iterator ret(_ar); return ret; }

    iterator end() { iterator ret(_ar + _sz); return ret; }
    const_iterator end() const { const_iterator ret(_ar + _sz); return ret; }

    // ***** Subscript operator *****
    reference operator[](size_type pos){return *(_ar + pos);}

    // ***** Capacity *****
    bool empty() const { if (!_sz) return true; else return false; }
    size_type size() const { return _sz; }
    size_type capacity() const { return _cp; }

    // ***** Modifiers *****
    iterator insert( iterator pos, const T& value )
    {
        size_type goal = pos - begin();

        if (_sz < _cp)
        {
            size_type i = _sz;
            _al.construct(_ar + i, *(_ar + i - 1));
            *(_ar + goal) = value;
            while (i > goal + 1)
            {
                *(_ar + i) = *(_ar + i - 1);
                i--;
            }
        }
        else
        {
            pointer xar = _ar;
            _ar = _al.allocate(NEWCP(_cp));
            size_type i = 0;
            while (i < goal)
            {
                _al.construct(_ar + i, *(xar + i));
                i++;
            }
            _al.construct(_ar + i, value);
            while (i < _sz)
            {
                 _al.construct(_ar + i + 1, *(xar + i));
                 i++;
            }
            while (i > 0)
                _al.destroy(xar + i--);
            if (_cp)
                _al.deallocate(xar, _cp);
            _cp = NEWCP(_cp);
        }
        _sz++;
        return pos;
    }

    void erase(iterator pos)
    {
        size_type ptr = pos - begin();
        while (ptr < _sz - 1)
        {
            *(_ar + ptr) = *(_ar + ptr + 1);
            ptr++;
        }
        _al.destroy(_ar + _sz--);
    }

};

}
#endif
