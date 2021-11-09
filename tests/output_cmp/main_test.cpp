#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>



//#ifndef OG
//# define OG
//#endif

// all testing functions declared here
#include "../tests.hpp"

void print_title(const char *s)
{
    std::cout << std::endl << "\x1B[32;1m" << s << "\x1B[0m" << std::endl;
}

void print_green(const char *s, int line)
{
    if (line)
        std::cout << std::endl << "\x1B[32m" << "l." << line << " | " << s << "\x1B[0m" << std::endl;
    else
        std::cout << std::endl << "\x1B[32m" << s << "\x1B[0m" << std::endl;
}


int main() {
    vector_all_tests();
    stack_all_tests();
    map_all_tests();
}
