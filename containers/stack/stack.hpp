#ifndef STACK_HPP
# define STACK_HPP

// Default underlying container is vector
# include "../vector/vector.hpp"

namespace ft {

template<
    class T,
    class Container = ft::vector<T>
> class stack {

public:

    /*
     * **************************************
     * ********** Member Types **************
     * **************************************
    */

    typedef Container   container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

protected:

    /*
     * **************************************
     * ********* Member Objects *************
     * **************************************
    */

    container_type c; //Underlying container

public:

    /*
     * **************************************
     * ********* Member Functions ***********
     * **************************************
    */

    // ***** Constructors *****

    // default or underlying cont copy constructor
    explicit stack( const Container& cont = Container() ) : c(cont) {}
    // stack copy constructor
    stack( const stack& other ) : c(other.c) {}

    // ***** Destructor *****
    ~stack() {}

    // ***** Assignment operator *****
    stack& operator=( const stack& other ){
        c = other.c;
        return *this;
    }

    /*
     * **************************************
     * ********** Element Access ************
     * **************************************
    */

    // ***** top *****
    // Accesses the top element
    reference       top()       { return c.back(); }
    const_reference top() const { return c.back(); }

    /*
     * **************************************
     * ************* Capacity ***************
     * **************************************
    */

    // ***** empty *****
    bool empty() const { return c.empty(); }

    // ***** size *****
    size_type size() const { return c.size(); }

    /*
     * **************************************
     * ************ Modifiers ***************
     * **************************************
    */

    // ***** push *****
    void push( const value_type& value ) { c.push_back(value); }


    // ***** pop *****
    void pop() { c.pop_back(); }

    /*
     * **************************************
     * ********** Relational Ope ************
     * **************************************
    */

    friend bool operator==( const ft::stack<T,Container>& lhs,
                     const ft::stack<T,Container>& rhs ){
        return lhs.c == rhs.c;
    }


    friend bool operator!=( const ft::stack<T,Container>& lhs,
                     const ft::stack<T,Container>& rhs ){
        return lhs.c != rhs.c;
    }

    friend bool operator<( const ft::stack<T,Container>& lhs,
                    const ft::stack<T,Container>& rhs ){
        return lhs.c < rhs.c;
    }

    friend bool operator<=( const ft::stack<T,Container>& lhs,
                    const ft::stack<T,Container>& rhs ){
        return lhs.c <= rhs.c;
    }

    friend bool operator>( const ft::stack<T,Container>& lhs,
                    const ft::stack<T,Container>& rhs ){
        return lhs.c > rhs.c;
    }

    friend bool operator>=( const ft::stack<T,Container>& lhs,
                    const ft::stack<T,Container>& rhs ){
        return lhs.c >= rhs.c;
    }
};
// End of Stack scope


}
#endif
