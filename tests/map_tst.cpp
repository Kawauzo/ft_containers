#include "tests.hpp"
#include <cstdlib>
#include <ctime>

typedef ft::map<int, int>  mpii;

void cppr_pair(){
    ft::pair <std::string,double> product1;                     // default constructor
    ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
    ft::pair <std::string,double> product3 (product2);          // copy constructor
    product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)
    product2.first = "shoes";                  // the type of first is string
    product2.second = 39.90;                   // the type of second is double
    std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
    std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
    std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

    ft::pair <std::string,int> planet, homeplanet;
    planet = ft::make_pair("Earth",6371);
    homeplanet = planet;
    std::cout << "Home planet: " << homeplanet.first << '\n';
    std::cout << "Planet size: " << homeplanet.second << '\n';
    ft::pair<int,char> foo (10,'z');
    ft::pair<int,char> bar (90,'a');

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

    bar.first = 10;
    std::cout << "\n";
    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

    bar.second = 'z';
    std::cout << "\n";
    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void tst_binarytree(){
    mpii arbr;

    arbr.insert(ft::make_pair(3, 3));
    arbr.insert(ft::make_pair(1, 1));
    arbr.insert(ft::make_pair(2, 2));
    arbr.insert(ft::make_pair(4, 4));
    arbr.insert(ft::make_pair(5, 5));
    for (int i = 1; i<=5; i++)
        arbr.find(i);
    arbr.find(6);
    //arbr.print();
    std::cout << "size: " << arbr.size() << '\n';
    arbr.clear();


    srand((unsigned)time(0));
    for (int i = 0; i < 13; i++){
        int elem = rand() % 99;
        arbr.insert(ft::make_pair(elem, 8));
        std::cout << elem << " / ";
    }
        std::cout << '\n';
    /*
    arbr.insert(ft::make_pair(3, 3));
    arbr.insert(ft::make_pair(1, 1));
    arbr.insert(ft::make_pair(6, 6));
    arbr.insert(ft::make_pair(7, 7));
    arbr.insert(ft::make_pair(10, 10));
    arbr.insert(ft::make_pair(13, 13));
    arbr.insert(ft::make_pair(14, 14));
    */

    std::cout << '\n';

    //arbr.print();

    for ( mpii::iterator it = arbr.begin(); it != arbr.end(); ++it)
        std::cout << (*it).first << std::endl;

    for ( mpii::iterator it = --arbr.end(); it != arbr.begin(); --it)
        std::cout << (*it).first << std::endl;
    std::cout << "size: " << arbr.size() << '\n';
}

void tst_const_error(mpii mapi)
{
    mpii::const_iterator roland(mapi.begin());
    while (roland != mapi.end()){
        std::cout << roland->first << std::endl;
        //roland->first += 12; //shouldnt compile
        roland++;
    }

    mpii::iterator       it(mapi.begin());
    mpii::const_iterator cend(mapi.end());
    while (it != cend){
        std::cout << it->first << std::endl;
        //it->first += 12; //shouldnt compile
        it++;
    }

    /*
    mpii::const_reverse_iterator simon = mapi.rbegin();
    while (simon != mapi.rend()){
        std::cout << *simon << std::endl;
        // *simon += "fortytwy"; //shouldnt compile
        simon++;
    }
    */
}



void map_all_tests(){

    cppr_pair();
    tst_binarytree();
}

//int main(){ map_all_tests(); }
