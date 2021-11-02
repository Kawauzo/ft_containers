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
    arbr.insert(ft::make_pair(22, 2));
    arbr.insert(ft::make_pair(4, 4));
    arbr.insert(ft::make_pair(2, 5));
    arbr.insert(ft::make_pair(89, 5));
    arbr.insert(ft::make_pair(17, 5));
    arbr.insert(ft::make_pair(45, 5));
    arbr.insert(ft::make_pair(-3, 5));
    arbr.insert(ft::make_pair(8, 5));
    arbr.insert(ft::make_pair(-1, 5));
    arbr.insert(ft::make_pair(42, 5));
    arbr.insert(ft::make_pair(43, 5));

    std::cout << "not found result: ";
    std::cout << (arbr.find(6) == arbr.end()) << std::endl;
    std::cout << "size: " << arbr.size() << '\n';
    arbr.erase(arbr.find(2));
    //arbr.print();
    std::cout << "erase ret: " << arbr.erase(4) << '\n';
    std::cout << "erase ret: " << arbr.erase(4) << '\n';
    //arbr.print();
    arbr.erase(arbr.find(45));
    //arbr.print();
    arbr.erase(arbr.find(22));
    //arbr.print();
    std::cout << "count ret: " << arbr.count(42) << '\n';
    std::cout << "count ret: " << arbr.count(4) << '\n';
    std::cout << "size: " << arbr.size() << '\n';
    arbr.clear();

    std::cout << "test operator[]: " << arbr[43] << '\n';
    std::cout << "test operator[]: " << arbr[-16] << '\n';

    for (int i = 0; i < 13; i++){
        int elem = rand() % 99;
        std::cout << arbr.insert(ft::make_pair(elem, 8)).second;
        std::cout << "." << elem << " / ";
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


void tst_custom_operator(){
    typedef ft::map<int, int, std::greater<int> >  rev_mpii;
    rev_mpii arbr;

    arbr.insert(ft::make_pair(3, 3));
    arbr.insert(ft::make_pair(1, 1));
    arbr.insert(ft::make_pair(22, 2));
    arbr.insert(ft::make_pair(4, 4));
    arbr.insert(ft::make_pair(2, 5));
    arbr.insert(ft::make_pair(89, 5));
    arbr.insert(ft::make_pair(17, 5));
    arbr.insert(ft::make_pair(45, 5));
    arbr.insert(ft::make_pair(-3, 5));
    arbr.insert(ft::make_pair(8, 5));
    arbr.insert(ft::make_pair(-1, 5));
    arbr.insert(ft::make_pair(42, 5));
    arbr.insert(ft::make_pair(43, 5));

    std::cout << "not found result: ";
    std::cout << (arbr.find(6) == arbr.end()) << std::endl;
    //arbr.print();
    arbr.erase(arbr.find(2));
    //arbr.print();
    arbr.erase(arbr.find(4));
    //arbr.print();
    arbr.erase(arbr.find(45));
    //arbr.print();
    arbr.erase(arbr.find(22));
    //arbr.print();
    std::cout << "size: " << arbr.size() << '\n';

    for ( rev_mpii::iterator it = arbr.begin(); it != arbr.end(); ++it)
        std::cout << (*it).first << std::endl;

    for ( rev_mpii::iterator it = --arbr.end(); it != arbr.begin(); --it)
        std::cout << (*it).first << std::endl;
    std::cout << "size: " << arbr.size() << '\n';
}

void tst_range_cpy(){
    ft::pair<int, int> tab[] = {ft::make_pair(12, 1),
                                ft::make_pair(27, 1),
                                ft::make_pair(98, 1),
                                ft::make_pair(8, 1),
                                ft::make_pair(-2, 1),
                                ft::make_pair(8, 1),
                                ft::make_pair(76, 1),
                                ft::make_pair(11, 1),
                                ft::make_pair(3, 1) };
    mpii tst_ins;
    tst_ins.insert(tab, tab+8);
    for ( mpii::iterator it = tst_ins.begin(); it != tst_ins.end(); ++it)
        std::cout << (*it).first << std::endl;
    std::cout << "size: " << tst_ins.size() << '\n';

    mpii tst_cns(tst_ins.begin(), tst_ins.end());
    for ( mpii::iterator it = tst_cns.begin(); it != tst_cns.end(); ++it)
        std::cout << (*it).first << std::endl;
    std::cout << "size: " << tst_cns.size() << '\n';

    mpii tst_cpy(tst_cns);
    for ( mpii::iterator it = tst_cns.begin(); it != tst_cns.end(); ++it)
        std::cout << (*it).first << std::endl;
    std::cout << "size: " << tst_cns.size() << '\n';



}

void map_all_tests(){
    srand((unsigned)time(0));

    cppr_pair();
    tst_binarytree();
    tst_custom_operator();
    tst_range_cpy();
}

//int main(){ map_all_tests(); }
