#include "tree_printer.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>

void tst_print_map() {
    map_printer<int, int> arbr;
    std::vector<int> inserted;


    int x = 42;
    // insert x elem
    for (int i = 0; i < x; i++){
        int elem = rand() % 99;
        if (arbr.insert(ft::make_pair(elem, 8)).second)
            inserted.push_back(elem);
    }
    arbr.print();

    x = 23;
    // erase x elem
    for (int i = 0; i < x; i++){
        int index = rand() % inserted.size();
        std::cout << "erase: " << inserted[index] << '\n';
        arbr.erase(inserted[index]);
        inserted.erase(inserted.begin() + index);
        arbr.print();
    }

    arbr.print();
   // insert x elem
    for (int i = 0; i < x; i++){
        int elem = rand() % 99;
        if (arbr.insert(ft::make_pair(elem, 8)).second)
            inserted.push_back(elem);
    }
    arbr.print();


}

int main(){
    srand((unsigned)time(0));
    tst_print_map();
}
