#include <iostream>
#include <string>
#include <iterator>

#ifndef OG
    #include "../containers/vector.hpp"
    #include "explicit_allocator.hpp"
#else
    #include <vector>
    namespace ft = std;
#endif

void print_title(const char *s)
{
	std::cout << std::endl << "\x1B[32;1m" << s << "\x1B[0m" << std::endl;
}

void print_green(const char *s)
{
	std::cout << std::endl << "\x1B[32m" << s << "\x1B[0m" << std::endl;
}

/*
void vec_alloc_1by1(int init_size)
{
	print_green("Making vec of int of given size");
	ft::vector<int, Mallocator<int> > vec(init_size);

	std::cout << "vec.size() = " << vec.size() << std::endl;
	for (int i = 0; i<35; i++)
	{
        std::cout << "-";
		vec.insert(vec.end(), 3);
	}
	for (int i = 0; i<10000; i++)
		vec.insert(vec.end(), 3);
	print_green("and now delete things");
	while (vec.size())
		vec.erase(vec.begin());
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
*/

template <class vec>
void test_vec()
{
    print_title("vectors tests");
    print_green("allocate two vecs");
	vec tst1(2, 6);
	vec tst2(2, 90);
	//tst1.insert(tst1.end(), 2);
    typename vec::iterator c;
    typename vec::iterator d;
    typename vec::iterator y(&tst1[0]);

    print_green("test end iterators comparison");
    std::cout << (tst1.end() != tst2.end()) << std::endl;
    std::cout << (tst2.begin() + 2 == tst2.end()) << std::endl;
    std::cout << (tst2.begin() < c) << std::endl;
    std::cout << (d == c ) << std::endl;
    std::cout << * (tst1.begin() + 3) << std::endl;

    print_green("edit []");
    std::cout << tst1.begin()[1] << std::endl;
    tst1.begin()[1] = 35;
    std::cout << tst1.begin()[1] << std::endl;

    print_green("edit *");
    *(tst1.begin() + 1) = 42;
    std::cout << tst1.begin()[1] << std::endl;
    std::cout << (tst1.begin() == y) << std::endl;
    std::cout << (*y) << std::endl;

    print_green("diff between its");
    std::cout << (tst1.begin() - tst1.begin()) << std::endl;
    std::cout << (tst1.begin() - tst1.end()) << std::endl;


    print_green("it built from pointer");
    int n = 4;
    int *p = &n;
    typename vec::iterator  j(p);
    std::cout << *j << std::endl;

    /*
    print_green("it function advance()");
    j = tst1.begin();
    *(j + 2) = 58;
    std::cout << *j << std::endl;
    std::advance(j, 2);
    std::cout << *j << std::endl;
    */

    int *pn = NULL;
    typename vec::iterator  jn(pn);
    std::cout << (jn == c);
}

struct aba{
    const std::string prout;
    aba():prout("tst"){};
};

int main()
{
	//vec_alloc_1by1(0);
	print_green("");
	//vec_alloc_large();

	print_green("");
    test_vec<ft::vector<int,Mallocator<int> > >();

    ft::vector<aba> j(3);
    ft::vector<aba>::iterator c = j.begin();
    std::cout << c->prout << std::endl;

    ft::vector<aba> j2(3);
    ft::vector<aba>::iterator c2 = j2.begin();
    std::cout << c2->prout << std::endl;
}
