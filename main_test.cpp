#include "vector.hpp"
#include "explicit_allocator.hpp"
#include <vector>
#include <iostream>

template <class vec>
void test_vec()
{
	vec tst1;
}

void vec_alloc_1by1()
{
	std::vector<int, Mallocator<int> > vec(6);

	std::cout << "vec.size() = " << vec.size() << std::endl;
	for (int i = 0; i<35; i++)
	{
		std::cout << "-";
		vec.insert(vec.end(), 3);
	}
	for (int i = 0; i<10000; i++)
		vec.insert(vec.end(), 3);
	std::cout << std::endl << "and now delete things" << std::endl;
	while (vec.size())
		vec.erase(vec.begin());
}

void vec_alloc_large()
{
	std::vector<int, Mallocator<int> > vec(6);


	vec.insert(vec.end(), 999, 2);
	std::cout << "inserted 999 elements" << std::endl << std::endl;
	vec.push_back(2);
	vec.assign(3, 6);
	std::cout << "vec.size() = " << vec.size() << std::endl;
	std::cout << "vec.capacity() = " << vec.capacity() << std::endl;
}

int main()
{
	//vec_alloc_1by1();
	vec_alloc_large();
	test_vec<std::vector<int> >();
	test_vec<ft::vector<int> >();
}
