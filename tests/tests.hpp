#ifndef TESTS_HPP
# define TESTS_HPP

#include <algorithm>
#include <string>
#include <iostream>

// two version of this file can be compiled
// "clang++ -DOG" to compile with orginial STL
#ifndef OG
    #include "../containers/vector/vector.hpp"
    #include "../containers/stack/stack.hpp"
    #include "../containers/map/map.hpp"
    #include "../containers/set/set.hpp"
#else
    #include <vector>
    #include <stack>
    #include <map>
    #include <set>
    namespace ft = std;
#endif

// Format utils
void print_title(const char *s);
void print_green(const char *s, int line = 0);

void vector_all_tests();
void stack_all_tests();
void map_all_tests();
void set_all_tests();

#endif
