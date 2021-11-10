#include "../tests.hpp"

void large_stack(){
    ft::stack<int> ls;

    for(int i = 0; i < 9999; ++i){
        ls.push(i);
        std::cout << ls.top();
    }
    while (ls.size())
        ls.pop();
}


int main(){
    large_stack();
}
