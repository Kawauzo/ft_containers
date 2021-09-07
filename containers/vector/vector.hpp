#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "../utils/iterator_utils.hpp"
# include "iterator.hpp"
# include <memory>

namespace ft
{

template <class T, class Alloc = std::allocator<T> > class vector
{

    /*
     * **************************************
     * ************ Iterators ***************
     * **************************************
    */
    public:

    class iterator
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
        iterator():_ptr(NULL){}
        iterator(iterator const &it):_ptr(it._ptr){}
        iterator(pointer p):_ptr(p){}

        // Assignement operator
        iterator& operator=(const iterator& it){ _ptr = it._ptr;
            return *this;
        }

        // Member access operators
        value_type& operator * (){return *_ptr;}
        value_type& operator [] (difference_type n){return * (_ptr + n);}
        pointer operator -> (){return _ptr;}

        // Pre-Increment/Decrement
        iterator& operator++() {_ptr++; return *this;}
        iterator& operator--() {_ptr--; return *this;}

        // Post-Increment/Decrement
        iterator operator++(int) {iterator copy(*this); _ptr++; return copy;}
        iterator operator--(int) {iterator copy(*this); _ptr--; return copy;}

        // Arithmetic operators
        iterator operator+(difference_type n) const{ iterator ret(_ptr + n); return ret; }
        iterator operator-(difference_type n) const{ iterator ret(_ptr - n); return ret; }
        difference_type operator-(iterator const &it) const{ difference_type ret = _ptr - it._ptr; return ret; }

        // Arithmetic Assignement operators
        iterator& operator+=(difference_type n) { _ptr += n; return *this; }
        iterator& operator-=(difference_type n) { _ptr -= n; return *this; }


        // Comparison operators
        bool operator==(iterator const &it) const { return _ptr == it._ptr; }
        bool operator!=(iterator const &it) const { return _ptr != it._ptr; }

        bool operator<(iterator const &it) const { return _ptr < it._ptr; }
        bool operator>(iterator const &it) const { return _ptr > it._ptr; }

        bool operator<=(iterator const &it) const { return _ptr <= it._ptr; }
        bool operator>=(iterator const &it) const { return _ptr >= it._ptr; }
    };


    /*
     * **************************************
     * ********** Member Types **************
     * **************************************
    */
    // ***** Basic Types *****

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
    iterator begin(){
        iterator ret(_ar);
        return ret;
    }

    iterator end(){
        iterator ret(_ar + _sz);
        return ret;
    }

    // ***** Subscript operator *****
    reference operator[](size_type pos){return *(_ar + pos);}

};

}
#endif
