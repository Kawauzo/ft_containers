#include "../tests.hpp"


void large_vec(){
    ft::vector<int> lv(999999, 42);

    lv.insert(lv.begin() + lv.size() / 2, 9999, 43);
    std::cout << lv.size() << '\n';

    lv.erase(lv.begin() + lv.size() / 4, lv.end() - lv.size() / 4);
    std::cout << lv.size() << '\n';

    lv.resize(lv.size() / 2);
    std::cout << lv.size() << '\n';

    lv.resize(lv.size() * 5);
    std::cout << lv.size() << '\n';

    std::cout << (lv < lv) << '\n';

    for (size_t i = 0; i < 4000; i++ ){
        lv.insert(lv.end() - i, i);
    }

    lv.clear();
}


int main(){
    large_vec();
}
