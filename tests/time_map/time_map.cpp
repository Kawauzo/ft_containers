#include "../tests.hpp"

#ifndef RSEED
# define RSEED 89
#endif

#define MAX_K 2147483647

void large_stack(){
    typedef ft::map<int, std::string> mapi;
    mapi mp;

    for (int i = 0; i < 9999; ++i)
        mp.insert(ft::make_pair(rand() % MAX_K, "ui"));

    for (int i = 0; i < 9999; ++i){
        mapi::iterator it = mp.find(rand() % MAX_K);
        if (it != mp.end())
            std::cout  <<  it->first << std::endl;
    }

    for (int i = 0; i < 9999; ++i)
        std::cout  << mp.size() << std::endl;

    for (int i = 0; i < 999; ++i)
        mp.erase(rand() % MAX_K);

    for (int i = 0; i < 9999; ++i)
        mp.insert(ft::make_pair(rand() % MAX_K, "non"));

}

int main(){
    srand(RSEED);
    large_stack();
}
