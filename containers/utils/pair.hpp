#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

/*
 * **************************************
 * ************ ft::pair ****************
 * **************************************
*/

template<
    class T1,
    class T2
> struct pair {
public:

    /*
     * **************************************
     * ********** Member Types **************
     * **************************************
    */

    typedef T1   first_type;
    typedef T2   second_type;

    /*
     * **************************************
     * ********* Member Objects *************
     * **************************************
    */

    first_type  first;
    second_type second;

    /*
     * **************************************
     * ********* Member Functions ***********
     * **************************************
    */

    // ***** Constructors *****

    // default constructor, value initializes first and second
    pair() : first(first_type()), second(second_type()) {}

    // initializes first with x and second with y
    pair( const T1& x, const T2& y ) : first(x), second(y) {}

    // initializes first with p.first and second with p.second
    template< class U1, class U2 >
    pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}

    // ***** copy assignment operator *****
    pair& operator=( const pair& other ) {
        first = other.first;
        second = other.second;
        return *this;
    }


};

/*
 * ****************************************
 * * Pair non-member relational operators *
 * ****************************************
*/
template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
    return (lhs.first == rhs.first && lhs.second == rhs.second) ? true : false;
}

template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
    return !(lhs == rhs);
}

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
    if (lhs.first < rhs.first)
        return true;
    if (rhs.first < lhs.first)
        return false;
    if (lhs.second < rhs.second)
        return true;
    return false;
}

template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
    return (lhs == rhs || lhs < rhs);
}


template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
    return (lhs != rhs && !(lhs < rhs));
}

template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
    return (lhs == rhs || lhs > rhs);
}
// --------------------------------------------
//          End of ft::pair
// --------------------------------------------


/*
 * **************************************
 * ********* ft::make_pair **************
 * **************************************
*/
template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
    return ( pair<T1,T2>(x,y) );
}

}
#endif
