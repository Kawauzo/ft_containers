#ifndef VECTOR_HPP
# define VECTOR_HPP

// needed for std::allocator
# include <memory>

// iterators, specific to vec
# include "vec_iterator.hpp"

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
        _ar(_al.allocate(n)),
        _sz(n),
        _cp(n)
    {
        for (unsigned int i = 0; i < _sz; i++)
            _al.construct(_ar + i, val);
    }


    // ***** Destructor *****
    ~vector()
    {
        for (unsigned int i = 0; i < _sz; i++)
            _al.destroy(_ar + i);
        _al.deallocate(_ar, _sz);
    }

    // ***** Iterators *****
    iterator begin(){ iterator ret(_ar); return ret; }
    const_iterator begin() const { const_iterator ret(_ar); return ret; }

    iterator end() { iterator ret(_ar + _sz); return ret; }
    const_iterator end() const { const_iterator ret(_ar + _sz); return ret; }

    // ***** Subscript operator *****
    reference operator[](size_type pos){return *(_ar + pos);}

};

}
#endif
