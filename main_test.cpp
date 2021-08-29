#include "vector.hpp"
#include "explicit_allocator.hpp"
#include <vector>
#include <iostream>

void print_green(const char *s)
{
	std::cout << "\x1B[32m" << s << "\x1B[0m" << std::endl;
}


void vec_alloc_1by1(int init_size)
{
	print_green("Making vec of int of given size");
	std::vector<int, Mallocator<int> > vec(init_size);

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
	std::vector<int, Mallocator<int> > vec(6);

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
void test_vec()
{
	vec tst1(2);
	tst1.insert(tst1.end(), 2);
}

int main()
{
	//vec_alloc_1by1(0);
	print_green("");
	//vec_alloc_large();
	
	test_vec<std::vector<int,Mallocator<int> > >();
	Mallocator<int> prout;
	print_green("");
	//test_vec<ft::vector<int,Mallocator<int> > >();
}
