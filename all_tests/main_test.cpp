#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>



//#ifndef OG
//# define OG
//#endif


// explicit allocator, outputing a message on cout
// each time alloc() is called
#include "explicit_allocator.v.hpp"

// two version of this file can be compiled
// "clang++ -DOG" to compile with orginial STL
#ifndef OG
    #include "../containers/vector/vector.hpp"
#else
    #include <vector>
    namespace ft = std;
#endif

void print_title(const char *s)
{
    std::cout << std::endl << "\x1B[32;1m" << s << "\x1B[0m" << std::endl;
}

void print_green(const char *s, int line = 0)
{
    if (line)
        std::cout << std::endl << "\x1B[32m" << "l." << line << " | " << s << "\x1B[0m" << std::endl;
    else
        std::cout << std::endl << "\x1B[32m" << s << "\x1B[0m" << std::endl;
}

class verbose
{
    int t;

    public:
    verbose(){};

    verbose(const int cpy):t(cpy)
    {std::cout << "basic called" << std::endl;}

    verbose(const verbose& cpy)
    { t = cpy.t; std::cout << "cpy constructor called" << std::endl;}

    verbose& operator=(const verbose& cpy)
    { t = cpy.t; std::cout << "operator= called" << std::endl; return *this;}
};

void vec_alloc_1by1_verbose(int init_size)
{
    print_green("Making vec of int of given size");
    ft::vector<verbose, Mallocator<verbose> > vec(init_size);

    std::cout << "vec.size() = " << vec.size() << std::endl;
    std::cout << "vec.cp() = " << vec.capacity() << std::endl;
    vec.insert(vec.end(), 3);
    vec.insert(vec.end(), 3);
    for (int i = 0; i<8; i++)
    {
        std::cout << "-";
        vec.insert(vec.end() - 2, 3);
        std::cout << std::endl;
    }
    for (int i = 0; i<4; i++)
        vec.insert(vec.end(), 3);
    print_green("and now delete things");
    std::cout << "vec.size() = " << vec.size() << std::endl;
    while (vec.size())
    {
        vec.erase(vec.begin());
        std::cout << std::endl;
    }
    print_green("nothing happens");
}

template<class vec>
void print_vec(vec &v)
{
    for (typename vec::iterator it = v.begin(); it < v.end() ; it++)
        std::cout << *it << ':';
    std::cout << std::endl;
}

void vec_alloc_1by1(int init_size)
{
    print_green("Making vec of int of given size");
    ft::vector<int, Mallocator<int> > vec(init_size);

    std::cout << "vec.size() = " << vec.size() << std::endl;
    vec.insert(vec.end(), 3);
    print_vec(vec);
    std::cout << std::endl;
    for (int i = 0; i<8; i++)
    {
        std::cout << "-";
        vec.insert(vec.end() - 1, i);
        print_vec(vec);
        std::cout << std::endl;
    }
    for (int i = 0; i<4; i++)
        vec.insert(vec.end(), 3);
    print_green("and now delete things");
    while (vec.size())
    {
        ft::vector<int, Mallocator<int> >::iterator tmp;
        tmp = vec.erase(vec.begin());
        if (tmp == vec.end())
            std::cout << "end" << std::endl;
        else
            std::cout << *tmp << std::endl;
        print_vec(vec);
    }
    print_green("nothing happens");
}

void vec_alloc_large()
{
    print_green("Making vec of int of size 6");
    ft::vector<int, Mallocator<int> > vec(6);

    print_green("insert 999 elems in it");
    vec.insert(vec.end(), 999, 2);
    print_green("add an other one");
    vec.push_back(2);

    print_green("assign the vec so it contains 3 ints");
    vec.assign(3, 6);
    std::cout << "vec.size() = " << vec.size() << std::endl;
    std::cout << "cbeg " << std::endl;
    std::cout << "vec.capacity() = " << vec.capacity() << std::endl;
}

template <class vec>
void tst_vec_iterators()
{
    print_title("vectors tsts");
    print_green("allocate two vecs", __LINE__);
    vec tst1(25, 6);
    {
        int tmp = 0;
        for (typename vec::iterator it = tst1.begin(); it < tst1.end(); it++)
            *it =  tmp++;
    }
    vec tst2(2, 90);
    //tst1.insert(tst1.end(), 2);
    typename vec::iterator y(&tst1[0]);

    // cpluplus.com random_access_iterators operations,
    // as listed in link below
    typename vec::iterator a = tst1.begin() + 12;
    typename vec::iterator b = tst1.begin() + 5;
    print_green("tst vec iterators operations (https://www.cplusplus.com/reference/iterator/RandomAccessIterator/)");
    print_green("a == b", __LINE__);
    std::cout << (a == b) << std::endl;
    print_green("a != b", __LINE__);
    std::cout << (a != b) << std::endl;

    print_green("*a", __LINE__);
    std::cout << *a << std::endl;
    print_green("*a = t", __LINE__);
    *a = 4;
    std::cout << *a << std::endl;

    print_green("a++ == a_bis++", __LINE__);
    typename vec::iterator a_bis(a);
    std::cout << (a++ == a_bis++) << std::endl;
    std::cout << (a == a_bis) << std::endl;
    print_green("++a == ++a_bis", __LINE__);
    std::cout << (++a == ++a_bis) << std::endl;

    print_green("a-- == a_bis--", __LINE__);
    std::cout << (a-- == a_bis--) << std::endl;
    std::cout << (a == a_bis) << std::endl;
    print_green("--a == --a_bis", __LINE__);
    std::cout << (--a == --a_bis) << std::endl;

    print_green("*a++", __LINE__);
    std::cout << *a++ << std::endl;
    std::cout << *a << std::endl;

    print_green("*a--", __LINE__);
    std::cout << *a-- << std::endl;
    std::cout << *a << std::endl;

    print_green("a + n", __LINE__);
    std::cout << *(a + 1) << std::endl;

    print_green("n + a", __LINE__);
    std::cout << *(1 + a) << std::endl;

    print_green("a - n", __LINE__);
    std::cout << *(a - 1) << std::endl;

    print_green("a - b", __LINE__);
    std::cout << a - b << std::endl;

    print_green("a < b", __LINE__);
    std::cout << (a < b) << std::endl;

    print_green("a > b", __LINE__);
    std::cout << (a > b) << std::endl;

    print_green("a <= b", __LINE__);
    std::cout << (a <= b) << std::endl;

    print_green("a >= b", __LINE__);
    std::cout << (a >= b) << std::endl;

    print_green("a += 2", __LINE__);
    std::cout << *a << std::endl;
    a += 2;
    std::cout << *a << std::endl;

    print_green("a -= 2", __LINE__);
    std::cout << *a << std::endl;
    a -= 2;
    std::cout << *a << std::endl;

    print_green("a[n]", __LINE__);
    std::cout << a[2] << std::endl;


    //tsting uninitialized iterators and end iterators values
    typename vec::iterator c;
    typename vec::iterator d;
    print_green("tst iterators end values and comparisons", __LINE__);
    std::cout << (tst1.end() != tst2.end()) << std::endl;
    std::cout << (tst2.begin() + 2 == tst2.end()) << std::endl;
    std::cout << (tst2.begin() < c) << std::endl;
    std::cout << (d == c ) << std::endl;
    std::cout << * (3 + tst1.begin()) << std::endl;

    print_green("edit []", __LINE__);
    std::cout << tst1.begin()[1] << std::endl;
    tst1.begin()[1] = 35;
    std::cout << tst1.begin()[1] << std::endl;

    print_green("edit *", __LINE__);
    *(tst1.begin() + 1) = 42;
    std::cout << tst1.begin()[1] << std::endl;
    std::cout << (tst1.begin() == y) << std::endl;
    std::cout << (*y) << std::endl;

    print_green("diff between its", __LINE__);
    std::cout << (tst1.begin() - tst1.begin()) << std::endl;
    std::cout << (tst1.begin() - tst1.end()) << std::endl;


    print_green("it built from pointer", __LINE__);
    int n = 4;
    int *p = &n;
    typename vec::iterator  j(p);
    std::cout << *j << std::endl;

    print_green("it function advance()", __LINE__);
    j = tst1.begin();
    *(j + 2) = 58;
    std::cout << *j << std::endl;
    std::advance(j, 2);
    std::cout << *j << std::endl;

    print_green("algortihm find() tst", __LINE__);
    j = std::find(tst1.begin(), tst1.end(), 58);
    std::cout << *j << std::endl;

    vec tst_ins(tst2);
    print_green("tst insert (basic)", __LINE__);
    print_vec(tst_ins);
    std::cout << *tst_ins.insert(tst_ins.begin() + 2, 18)
    << std::endl;
    print_vec(tst_ins);
    std::cout << *tst_ins.insert(tst_ins.begin(), 56)
    << std::endl;
    print_vec(tst_ins);
    std::cout << *tst_ins.insert(tst_ins.begin(), 1129)
    << std::endl;
    print_vec(tst_ins);
    std::cout << *tst_ins.insert(tst_ins.begin() + 2, 9328)
    << std::endl;
    print_vec(tst_ins);
    std::cout << *tst_ins.insert(tst_ins.begin() + 2, -4532)
    << std::endl;
    print_vec(tst_ins);



    vec tst_ins_cnt(tst2);
    print_green("tst insert count elems()", __LINE__);
    print_vec(tst_ins_cnt);
    tst_ins_cnt.insert(tst_ins_cnt.begin() - 2, 0, 1);
    print_vec(tst_ins_cnt);
    tst_ins_cnt.insert(tst_ins_cnt.begin() + 0, 2, 12);
    print_vec(tst_ins_cnt);
    tst_ins_cnt.insert(tst_ins_cnt.begin() + 2, 3, 1);
    print_vec(tst_ins_cnt);
    tst_ins_cnt.insert(tst_ins_cnt.begin() + 2, 2, 2);
    print_vec(tst_ins_cnt);
    tst_ins_cnt.insert(tst_ins_cnt.begin() + 2, 1, 3);
    print_vec(tst_ins_cnt);
    print_green("tst insert count 1 elem() after clear", __LINE__);
    tst_ins_cnt.clear();
    tst_ins_cnt.insert(tst_ins_cnt.begin(), 1, 3);
    print_green("tst insert count 1 elem() after clear", __LINE__);
    tst_ins_cnt.clear();
    tst_ins_cnt.clear();
    tst_ins_cnt.insert(tst_ins_cnt.begin(), 10, 3);

    print_green("tst swap", __LINE__);
    print_vec(tst2);
    print_vec(tst1);
    tst1.swap(tst2);
    print_vec(tst2);
    print_vec(tst1);

    vec empty;
    empty.swap(tst2);
    print_vec(tst2);
    print_vec(empty);
    empty.swap(tst2);

    vec tst_asgn = tst1;
    print_green("tst assign(count, val)", __LINE__);
    print_vec(tst_asgn);
    std::cout << "cp: " << tst_asgn.capacity() << std::endl;
    tst_asgn.assign(45, 1);
    print_vec(tst_asgn);
    std::cout << "cp: " << tst_asgn.capacity() << std::endl;
    tst_asgn.assign(5, 42);
    print_vec(tst_asgn);
    std::cout << "cp: " <<  tst_asgn.capacity() << std::endl;
    tst_asgn.assign(34, 68);
    print_vec(tst_asgn);
    std::cout << "cp: " <<  tst_asgn.capacity() << std::endl;
    tst_asgn.assign(0, 68);
    print_vec(tst_asgn);
    std::cout << "cp: " <<  tst_asgn.capacity() << std::endl;
    tst_asgn.clear();
    std::cout << "cp: " <<  tst_asgn.capacity() << std::endl;



    vec tst_asgn2;
    print_green("assign(range) :  (cp++)", __LINE__);
    std::cout << tst_asgn2.capacity() << std::endl;
    tst_asgn2.assign(tst2.begin(), tst2.begin() + 12);
    print_vec(tst2);

    print_green("assign(range) :  (size--)", __LINE__);
    std::cout << tst_asgn2.capacity() << std::endl;
    tst_asgn2.assign(tst2.begin() + 1, tst2.begin() + 10);
    print_vec(tst_asgn2);
    std::cout << tst_asgn2.capacity() << std::endl;

    print_green("assign(range) :  (size++, same cp)", __LINE__);
    tst_asgn2.assign(tst2.begin(), tst2.begin() + 6);
    print_vec(tst_asgn2);
    std::cout << tst_asgn2.capacity() << std::endl;

    print_green("assign(range) :  (cp++)", __LINE__);
    tst_asgn2.assign(tst2.begin() + 5, tst2.begin() + 20);
    print_vec(tst_asgn2);
    std::cout << tst_asgn2.capacity() << std::endl;

    print_green("assign(range) :  (empty)", __LINE__);
    tst_asgn2.assign(tst2.begin(), tst2.begin());
    print_vec(tst_asgn2);
    std::cout << tst_asgn2.capacity() << std::endl;




    print_green("tst pop_back", __LINE__);
    while (!tst1.empty())
    {
        print_vec(tst1);
        std::cout << tst1.size() << std::endl;
        tst1.pop_back();
    }
    print_vec(tst1);

    print_green("tst push_back", __LINE__);
    for (int i = 0; i < 56; i++)
        tst1.push_back(i);
    print_vec(tst1);



    std::cout << std::endl;
    vec tst_res(5, 6);
    print_green("tst resize()", __LINE__);
    print_vec(tst_res);
    tst_res.resize(16);
    print_vec(tst_res);
    tst_res.resize(18, 3);
    print_vec(tst_res);
    tst_res.resize(20, 4);
    print_vec(tst_res);
    tst_res.resize(2, 6);
    print_vec(tst_res);

    int *pn = NULL;
    typename vec::iterator  jn(pn);
    std::cout << (jn == c) << std::endl;

    for (typename vec::const_iterator it = tst1.begin(); it < tst1.end(); it++)
        std::cout << *it << ' ';
    std::cout << std::endl;

    typename vec::iterator *J = new typename vec::iterator;
    delete J;

    print_green("tst assign empty its");
    vec nul;
    vec test(3, 0);
    test.assign(nul.begin(), nul.end());

    print_green("tst operator=()", __LINE__);
    vec foo (3,0);
    vec bar (5,0);
    bar = foo;
    std::cout << "Capacity of foo: " << int(foo.capacity()) << '\n';
    std::cout << "Capacity of bar: " << int(bar.capacity()) << '\n';
    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
    foo = vec();
    std::cout << "Capacity of foo: " << int(foo.capacity()) << '\n';
    std::cout << "Capacity of bar: " << int(bar.capacity()) << '\n';
    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';


    std::cout << "tst1 cp/sz " << int(tst1.size()) << '/' << int(tst1.capacity()) << '\n';

    vec  erange = tst1;
    print_vec(erange);

    print_green("test erase(range)");

    std::cout << *erange.erase(erange.begin() + 3, erange.begin() + 8) << std::endl;
    std::cout << erange.size() << '\n';
    print_vec(erange);
    std::cout << (erange.erase(erange.end() - 8, erange.end()) == erange.end()) << std::endl;
    print_vec(erange);
    std::cout << *erange.erase(erange.begin() + 3, erange.begin() + 3) << std::endl;
    print_vec(erange);
}

/*
 * En gros une fonction pour tster le bon fonctionnement
 * des iterators input only (ne peut etre deref qu'une fois)
*/
//small "true" input iterator
class inputIt
{
    public:
    typedef int                      value_type;
    typedef ptrdiff_t                difference_type;
    typedef int*                     pointer;
    typedef int&                     reference;
    typedef std::input_iterator_tag  iterator_category;

    typedef ft::vector<int>::iterator base_t;
    private:
    base_t base;

    public:
    inputIt(inputIt & cpy):base(cpy.base) {}
    inputIt(base_t &bse):base(bse) {}
    inputIt operator++(int) {inputIt copy(*this); base++; return copy;}
    inputIt& operator++() {base++; return *this;}
    value_type& operator[](difference_type n) {return base[n];}

    value_type& operator * (){return *base;}
    bool operator!=(inputIt &it) const { return base != it.base;}
    bool operator==(inputIt &it) const { return base == it.base;}
};

void tst_vec_strings()
{
    typedef ft::vector<std::string, Mallocator<std::string> > vec;
    std::string tab[6] = {"asdf", "ui", "hjfkd", "alo", "fd", "up"};

    print_green("tst vec range constructor with C array", __LINE__);
    vec vrng(tab, tab+6);
    print_vec(vrng);

    print_green("tst vec empty range constructor", __LINE__);
    vec vrng_empty(tab, tab);
    print_vec(vrng_empty);

    print_green("tst vec cpy constructor", __LINE__);
    vec vcpy(vrng);
    print_vec(vcpy);

    print_green("tst empty vec cpy constructor", __LINE__);
    vec vcpy_empty(vrng_empty);
    print_vec(vcpy_empty);

    print_green("tst front / tst back", __LINE__);
    std::cout << vrng.front() << std::endl;
    std::cout << vrng.back() << std::endl;

    print_green("tst at", __LINE__);
    std::cout << vrng.at(2) << std::endl;
    try { std::cout << vrng.at(122) << std::endl; }
    catch (std::exception &e) {std::cout << e.what() << std::endl;}
    try { std::cout << vrng.at(-1) << std::endl; }
    catch (std::exception &e) {std::cout << e.what() << std::endl;}
    std::cout << vrng.at(2) << std::endl;

    print_green("end of scope, destroy vectors", __LINE__);
}

void tst_vec_inputit()
{
    print_green("");
    typedef ft::vector<int> vec_mute;
    typedef ft::vector<int, Mallocator<int> > vec;


    int ar[] = {39, 13, 56, 89, 56, 76, 32, 5413 , 5, 14, 543, 5431, 432};
    vec_mute michel(ar, ar+13);
    vec_mute::iterator mbeg(michel.begin());
    inputIt beg(mbeg);
    vec_mute::iterator mend(michel.end());
    inputIt end(mend);

    vec_mute bigone(45, 1);
    vec_mute::iterator bbeg(bigone.begin());
    inputIt bigbeg(bbeg);
    vec_mute::iterator bend(bigone.end());
    inputIt bigend(bend);


    print_green("original vector. we'll do 2 more based on it", __LINE__);
    print_green("but with pure input_iterators");
    print_vec(michel);

    print_green("true input_iterators with range constructor", __LINE__);
    vec tst1(beg, end);
    print_vec(tst1);

    print_green("true input_iterators with range insert empty", __LINE__);
    vec tst2;
    tst2.insert(tst2.end(), beg, end);

    print_green("true input_iterators with range insert at mid range", __LINE__);
    tst2.insert(tst2.end() - 5, beg, end);
    print_vec(tst2);

    vec_mute::iterator smol(michel.begin() + 5);
    inputIt ssmol(smol);

    print_green("true input_iterators with assign (size--)", __LINE__);
    std::cout << tst2.capacity() << std::endl;
    tst2.assign(beg, ssmol);
    print_vec(tst2);
    std::cout << tst2.capacity() << std::endl;

    print_green("true input_iterators with assign (size++, same cp)", __LINE__);
    tst2.assign(beg, end);
    print_vec(tst2);
    std::cout << tst2.capacity() << std::endl;

    print_green("true input_iterators with assign (cp++)", __LINE__);
    tst2.assign(bigbeg, bigend);
    print_vec(tst2);
    std::cout << tst2.capacity() << std::endl;

    print_green("true input_iterators with assign (empty)", __LINE__);
    tst2.assign(bigbeg, bigbeg);
    print_vec(tst2);
    std::cout << tst2.capacity() << std::endl;


    print_green("end of scope", __LINE__);
}

struct aba{
    const std::string elem;
    aba():elem("tst"){};
};

void tst_vec_arrow_operator()
{

    print_green("tst -> operator on vector iterator", __LINE__);
    ft::vector<aba> j(3);
    ft::vector<aba>::iterator c = j.begin();
    std::cout << c->elem << std::endl;

    ft::vector<aba> j2(3);
    ft::vector<aba>::iterator c2 = j2.begin();
    std::cout << c2->elem << std::endl;

    ft::vector<aba>::reverse_iterator cr = j.rbegin();
    std::cout << cr->elem << std::endl;
}


void tst_vec_reverse_it()
{
    typedef ft::vector<int, Mallocator<int> > vec;

    vec tst;
    for (int i = 0; i < 10; ++i)
        tst.push_back(i);
    print_vec(tst);
    vec::reverse_iterator it = tst.rbegin();
    while ( it != tst.rend())
    {
        std::cout << *it << std::endl;
        ++it;
    }

    //from cppreference
    vec::reverse_iterator rv = tst.rbegin();
    vec::reverse_iterator rvend = tst.rend();
    std::cout << *(++rv) << ' ';
    std::cout << *(--rv) << ' ';
    std::cout << *(rv + 3) << ' ';
    rv += 3;
    std::cout << rv[0] << ' ';
    std::cout << rv[1] << ' ';
    std::cout << rv[2] << ' ';
    rv -= 3;
    std::cout << rv[0] << ' ';
    vec::reverse_iterator rvp = 3 + rv;
    std::cout << rvp[2] << ' ';
    std::cout << *(3 + rvp) << ' ';
    std::cout << rvp[2] << ' ';
    std::cout << rvend - rv << ' ';
    std::cout << rv - rvend << ' ';

    print_green("tst max_size()", __LINE__);
    std::cout << tst.max_size() << std::endl;

    vec::reverse_iterator x = tst.rend() - tst.size();
    vec::reverse_iterator y = tst.rend() - tst.size();
    vec::reverse_iterator z = tst.rbegin() + 1;
    std::cout << std::endl
        << std::boolalpha
        << "*x == " << *x << '\n' // 9
        << "*y == " << *y << '\n' // 9
        << "*z == " << *z << '\n' // 8
        << "x == y ? " << (x == y) << '\n' // true
        << "x != y ? " << (x != y) << '\n' // false
        << "x <  y ? " << (x <  y) << '\n' // false
        << "x <= y ? " << (x <= y) << '\n' // true
        << "x == z ? " << (x == z) << '\n' // false
        << "x != z ? " << (x != z) << '\n' // true
        << "x <  z ? " << (x <  z) << '\n' // true!
        << "x <= z ? " << (x <= z) << '\n' // true
        ;
    std::cout << std::endl;

    vec::const_reverse_iterator cit = tst.rbegin();
	std::cout << "(const_ite - it): " << (cit - x - 2) << std::endl;
	std::cout << "(const_ite - it): " << (cit - z) << std::endl;
}

void tst_vec_capacity()
{
    typedef ft::vector<int> vec;

    vec tst(14, 42);

    print_green("tst resize()", __LINE__);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    tst.resize(1);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    tst.resize(tst.capacity() + 1);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    tst.resize(tst.capacity() + 130);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    tst.resize(tst.capacity() + 1);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;

    print_green("tst reserve()", __LINE__);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    tst.reserve(1);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    tst.reserve(tst.capacity() + 1);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    try { tst.reserve(tst.max_size() + 1); }
    catch (std::exception &e) { std::cout << e.what() << std::endl; }
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    tst.reserve(tst.capacity() + 130);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;
    tst.reserve(tst.capacity() + 1);
    std::cout << tst.capacity()  << '|' << tst.size() << std::endl;

}

void failed_testers(){
    print_green("tst assign/insert with bidirectionnal its");
	std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	ft::vector<int> vct(lst.begin(), lst.end());
    print_vec(vct);
    std::cout << vct.size();

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
    print_vec(vct);
    std::cout << vct.size();

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
    print_vec(vct);
    std::cout << vct.size();
}

void tst_const_error()
{
    typedef ft::vector<std::string> vec;
    vec vs(10, "42");

    vec::const_iterator roland(vs.begin());
    while (roland != vs.end()){
        std::cout << *roland << std::endl;
        // *roland += "fortytwy"; //shouldnt compile
        roland++;
    }

    vec::iterator       it(vs.begin());
    vec::const_iterator cend(vs.end());
    while (it != cend){
        std::cout << *it << std::endl;
        // *it += "fortytwy"; //shouldnt compile
        it++;
    }

    vec::const_reverse_iterator simon = vs.rbegin();
    while (simon != vs.rend()){
        std::cout << *simon << std::endl;
        // *simon += "fortytwy"; //shouldnt compile
        simon++;
    }
}

void tst_vec_comparison() {
    typedef ft::vector<std::string> vec;

    vec vs(120, "char ");

    char alpha = 0;
    for (vec::iterator it = vs.begin(); it != vs.end(); it++)
        *it += alpha++;

    vec vs2(vs);

    print_green("tst vector equality", __LINE__);
    std::cout << (vs == vs2) << std::endl;
    std::cout << (vs != vs2) << std::endl;
    vs.push_back("alo");
    std::cout << (vs == vs2) << std::endl;
    std::cout << (vs != vs2) << std::endl;
    vs.pop_back();
    std::cout << (vs == vs2) << std::endl;
    std::cout << (vs != vs2) << std::endl;
    vs[2] = "non";
    std::cout << (vs == vs2) << std::endl;
    std::cout << (vs != vs2) << std::endl;

    vs[2] = vs2[2];
    print_green("tst vector comparisons (lexicographical compare)", __LINE__);
    std::cout << (vs < vs2) << std::endl;
    std::cout << (vs > vs2) << std::endl;
    std::cout << (vs <= vs2) << std::endl;
    std::cout << (vs >= vs2) << std::endl;
    print_green("diff a/b", __LINE__);
    vs[3] += 'a';
    vs2[3] += 'b';
    std::cout << (vs < vs2) << std::endl;
    std::cout << (vs > vs2) << std::endl;
    std::cout << (vs <= vs2) << std::endl;
    std::cout << (vs >= vs2) << std::endl;
    print_green("diff vs1 has more elem", __LINE__);
    vs[3] = vs2[3];
    vs.push_back("oui oui ");
    std::cout << (vs < vs2) << std::endl;
    std::cout << (vs > vs2) << std::endl;
    std::cout << (vs <= vs2) << std::endl;
    std::cout << (vs >= vs2) << std::endl;
}

void tst_vec_rev_to_it() {
    std::string arr[] = {"oui", "jul", "raymond", "patrick", "soufler"};
    typedef ft::vector<std::string> vec;
    vec v1(arr, arr + 5);
    // vec::iterator v1_it = v1.rbegin();
    // std doesn't compile ^ no conversion from reverse to iterator
}

void tst_capacity_assign() {
    std::string arr[] = {"oui", "jul", "raymond"};
    typedef ft::vector<std::string> vec;
    vec v1_dup(arr, arr+3);
    vec v1(10, "zz");
    v1 = v1_dup;
    print_green("vec.capacity == vec_dup.capacity", __LINE__);
    std::cout << (v1.capacity() == v1_dup.capacity()) << std::endl;
}

template <typename T>
void    vectorTest_InsertNElem(T& cont)
{
    T tmp = cont;
    std::cout << "size of tmp = " << tmp.size();

    // Allows to value initialize (case size is 0, we can't assign cont[0])
    typename T::value_type* x = new typename T::value_type ();
    std::cout <<std::endl; print_vec(tmp);
    if (cont.size())
    {
        *x = cont.front();
        typename T::iterator it = tmp.begin();
        ++it;
        tmp.insert(it, 5, *x);
    }
    std::cout <<std::endl; print_vec(tmp);
    tmp.insert(tmp.begin(), 5, *x);
    std::cout <<std::endl; print_vec(tmp);
    tmp.insert(tmp.end(), 5, *x);

    std::cout << "size of tmp = " << tmp.size();
    std::cout <<std::endl; print_vec(tmp);

    delete x;
}

void vector_insert_tests_maker(){
    int tabi[] = {58966, 2147483647, 256, -214748, 3648, 0, -1, 2, 3, 4, 5};
    ft::vector<int> tstint(tabi, tabi + 10);
    vectorTest_InsertNElem(tstint);

    tstint = ft::vector<int>(12, 8);
    vectorTest_InsertNElem(tstint);

    std::string tabs[] = {"hello coco", "j'arrive", "oui-oui", "kafeolait", "jul d'ananas", "jul d'ananas"};
    ft::vector<std::string> tstring(tabs, tabs + 6);
    vectorTest_InsertNElem(tstring);
}

template <typename T>
void    vectorTest_Erase1Elem(T& cont)
{
    std::string name("erase 1 elem:");
    std::cout << "\n---------------------";

    typename T::value_type* x = new typename T::value_type ();

    // Erase first elem
    if (cont.size() > 1)
    {
         std::cout << "----- erase first elem -----";

        T tmp = cont;
         std::cout << "size of tmp = " << tmp.size();

        print_vec(tmp);
        typename T::iterator iter = tmp.erase(tmp.begin());
        if (tmp.size())
            {   std::cout << "return value: " << *iter << '\n'; }
        print_vec(tmp);

        for (typename T::iterator it = tmp.begin(); it != iter; ++it)
            std::cout << *it << " | ";

        std::cout << "size of tmp = " << tmp.size() << '\n';

        // checking if everything was correcty destroyed and if we can push_back on erased values
        for (int i = 0; i < 20; ++i)
            tmp.push_back(*x);
    }

    // Erase last elem
    if (cont.size())
    {
         std::cout << "----- erase last elem -----";

        T tmp = cont;
         std::cout << "size of tmp = " << tmp.size() << '\n';

        typename T::iterator iter = tmp.erase(tmp.end() - 1);
        print_vec(tmp);


        for (typename T::iterator it = tmp.begin(); it != iter; ++it)
            std::cout << *it << " | ";

        std::cout << "size of tmp = " << tmp.size() << '\n';

        // checking if everything was correcty destroyed and if we can push_back on erased values
        for (int i = 0; i < 20; ++i)
            tmp.push_back(*x);
        print_vec(tmp);
    }

    // Erase one elem
    if (cont.size() > 1)
    {
        std::cout << "----- erase second elem -----";

        T tmp = cont;
        std::cout << "size of tmp = " << tmp.size() << '\n';

        typename T::iterator iter = tmp.erase(tmp.begin() + 1);
        if (tmp.size() > 2)
            { std::cout << "return value: " << *iter; }
        print_vec(tmp);


        for (typename T::iterator it = tmp.begin(); it != iter; ++it)
            std::cout << *it << " | ";


        // checking if everything was correcty destroyed and if we can push_back on erased values
        for (int i = 0; i < 20; ++i)
            tmp.push_back(*x);
        print_vec(tmp);
    }

    delete x;
}

void vector_delete_tests(){
    std::string tabs[] = {"raviolis du nord est", "raviolis du nord est", "raviolis du nord est"};
    ft::vector<std::string> tstring(tabs, tabs + 3);
    vectorTest_Erase1Elem(tstring);
}

void tst_derniereminute(){
    typedef ft::vector<std::string> vec;
    vec vs(20,"");
    while(vs.size() > 2)
        vs.pop_back();
    std::string tab[] = {"1", "2", "2", "4", "3", "2", "1", "2", "3", "4", "3", };
    vs.insert(vs.begin() + 1, tab, tab+11);
    print_vec(vs);
}

int main()
{
    vec_alloc_1by1(1);
    print_green("");
    vec_alloc_large();

    tst_vec_strings();
    print_green("");
    tst_vec_iterators<ft::vector<int,Mallocator<int> > >();
    tst_vec_inputit();
    tst_vec_arrow_operator();
    tst_vec_reverse_it();
    tst_vec_capacity();
    tst_vec_comparison();
    tst_capacity_assign();

    vector_insert_tests_maker();
    vector_delete_tests();

    tst_derniereminute();
}
