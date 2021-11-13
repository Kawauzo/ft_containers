#include "../tests.hpp"

#ifndef RSEED
# define RSEED 178
#endif

#define MAX_K 2147483647

void large_set(){
    typedef ft::set<int> seti;
    seti mp;

    for (int i = 0; i < 9999; ++i)
        mp.insert(rand() % MAX_K);

    for (int i = 0; i < 9999; ++i){
        seti::iterator it = mp.find(rand() % MAX_K);
        if (it != mp.end())
            std::cout  <<  *it << std::endl;
    }

    for (int i = 0; i < 9999; ++i)
        std::cout  << mp.size() << std::endl;

    for (int i = 0; i < 999; ++i)
        mp.erase(rand() % MAX_K);

    for (int i = 0; i < 9999; ++i)
        mp.insert(rand() % MAX_K);

}

int main(){
    srand(RSEED);
    large_set();
}
