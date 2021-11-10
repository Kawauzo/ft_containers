#include "../tests.hpp"

#ifndef RSEED
# define RSEED 89
#endif

void large_vec(){
    ft::stack<int> ls;

    ls.insert(ls.begin() + ls.size() / 2, 9999, 43);
    std::cout << ls.size() << '\n';

    ls.erase(ls.begin() + ls.size() / 4, ls.end() - ls.size() / 4);
    std::cout << ls.size() << '\n';

    ls.resize(ls.size() / 2);
    std::cout << ls.size() << '\n';

    ls.resize(ls.size() * 5);
    std::cout << ls.size() << '\n';

    std::cout << (ls < ls) << '\n';

    for (size_t i = 0; i < 4000; i++ ){
        ls.insert(ls.end() - i, i);
    }

    ls.clear();
}


int main(){
    srand(RSEED);
    large_vec();
}
