#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>



//#ifndef OG
//#define OG
//#endif


// explicit allocator, outputing a message on cout
// each time alloc() is called
#include "explicit_allocator.v.hpp"

// two version of this file can be compiled
// "clang -DOG" to compile with orginial STL
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
        vec.erase(vec.begin());
        print_vec(vec);
    }
    print_green("nothing happens");
}

/*
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
*/

template <class vec>
void test_vec_iterators()
{
    print_title("vectors tests");
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
    print_green("test vec iterators operations (https://www.cplusplus.com/reference/iterator/RandomAccessIterator/)");
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


    //testing uninitialized iterators and end iterators values
    typename vec::iterator c;
    typename vec::iterator d;
    print_green("test iterators end values and comparisons", __LINE__);
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

    int *pn = NULL;
    typename vec::iterator  jn(pn);
    std::cout << (jn == c) << std::endl;

    typename vec::iterator *J = new typename vec::iterator;
    delete J;
}

void test_vec_strings()
{
    typedef ft::vector<std::string, Mallocator<std::string> > vec;
    std::string tab[6] = {"asdf", "ui", "hjfkd", "alo", "fd", "up"};

    print_green("test vec range constructor with C array", __LINE__);
    vec vrng(tab, tab+6);
    print_vec(vrng);

    print_green("test vec range constructor with two equal iterators (empty cont)", __LINE__);
    vec vrng_empty(tab, tab);
    print_vec(vrng_empty);

    print_green("test vec cpy constructor", __LINE__);
    vec vcpy(vrng);
    print_vec(vcpy);
    vec emptyrng(tab, tab+6);

    print_green("end of scope, destroy vectors", __LINE__);
}

struct aba{
    const std::string prout;
    aba():prout("tst"){};
};

int main()
{
    vec_alloc_1by1(1);
    print_green("");
    //vec_alloc_large();

    test_vec_strings();
    print_green("");
    test_vec_iterators<ft::vector<int,Mallocator<int> > >();

    ft::vector<aba> j(3);
    ft::vector<aba>::iterator c = j.begin();
    std::cout << c->prout << std::endl;

    ft::vector<aba> j2(3);
    ft::vector<aba>::iterator c2 = j2.begin();
    std::cout << c2->prout << std::endl;
}
