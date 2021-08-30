#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"
# include <memory>

namespace ft
{

template <class T, class Alloc = std::allocator<T> > class vector
{
    /*
     * **************************************
     * ********** Member Types **************
     * **************************************
    */
    public:

    // ***** Basic Types *****

    typedef T                   value_type;

    typedef Alloc               allocator_type;

    typedef value_type&         reference;

    typedef const value_type&   const_reference;

    typedef value_type*         pointer;

    typedef const value_type*   const_pointer;

    typedef typename allocator_type::size_type size_type;
 
    // ***** Iterators *****
    //
    class iterator
    {
        public:
        // iterator_traits
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef random_access_iterator_tag  iterator_category;

        private:
        T* _pos; //only variable, iterator position

        public:
        iterator() {};
    };

    /*
     * **************************************
     * ************ Variables ***************
     * **************************************
    */
    private:

    allocator_type  _al;    // Allocator

    T*              _ar;    // Underlying array

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

};

}

#endif
