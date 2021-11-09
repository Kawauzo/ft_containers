#include "../tests.hpp"

typedef ft::map<int, int>  mpii;

void cppr_pair(){
    print_green("Tst ft::pair behaviour", __LINE__);
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
    print_green("Tst insert/erase", __LINE__);
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
    ////arbr.print();
    std::cout << "erase ret: " << arbr.erase(4) << '\n';
    std::cout << "erase ret: " << arbr.erase(4) << '\n';
    ////arbr.print();
    arbr.erase(arbr.find(45));
    ////arbr.print();
    arbr.erase(arbr.find(22));
    ////arbr.print();
    std::cout << "count ret: " << arbr.count(42) << '\n';
    std::cout << "count ret: " << arbr.count(4) << '\n';
    std::cout << "size: " << arbr.size() << '\n';
    arbr.clear();

    std::cout << "test operator[]: " << arbr[43] << '\n';
    std::cout << "test operator[]: " << arbr[-16] << '\n';


    std::cout << '\n';
    arbr.insert(ft::make_pair(3, 3));
    arbr.insert(ft::make_pair(1, 1));
    arbr.insert(ft::make_pair(6, 6));
    arbr.insert(ft::make_pair(7, 7));
    arbr.insert(ft::make_pair(10, 10));
    arbr.insert(ft::make_pair(13, 13));
    arbr.insert(ft::make_pair(14, 14));

    std::cout << '\n';

    ////arbr.print();

    for ( mpii::iterator it = arbr.begin(); it != arbr.end(); ++it)
        std::cout << (*it).first << std::endl;

    for ( mpii::iterator it = --arbr.end(); it != arbr.begin(); --it)
        std::cout << (*it).first << std::endl;
    std::cout << "size: " << arbr.size() << '\n';


    for ( mpii::reverse_iterator rit = arbr.rbegin(); rit != arbr.rend(); ++rit)
        std::cout << (*rit).first << std::endl;

}

void tst_const_error(mpii mapi)
{
    print_green("Tst const_iterator", __LINE__);
    mpii::const_iterator roland(mapi.begin());
    while (roland != mapi.end()){
        std::cout << roland->first << std::endl;
        //roland->second += 12; //shouldnt compile
        roland++;
    }

    mpii::iterator       it(mapi.begin());
    mpii::const_iterator cend(mapi.end());
    while (it != cend){
        std::cout << it->first << std::endl;
        //it->second += 12; //shouldnt compile
        it++;
    }

    mpii::const_reverse_iterator simon = mapi.rbegin();
    while (simon != mapi.rend()){
        std::cout << simon->first << std::endl;
        //simon->second += 12; //shouldnt compile
        simon++;
    }
}


void tst_custom_operator(){
    print_green("Tst map with custom comparison operator", __LINE__);
    typedef ft::map<int, int, std::greater<int> >  rev_mpii;
    rev_mpii arbr;

    arbr.insert(ft::make_pair(3, 3));
    arbr.insert(ft::make_pair(1, 1));
    arbr.insert(ft::make_pair(22, 2));
    arbr.insert(ft::make_pair(19, 2)); // try to break erase
    arbr.insert(ft::make_pair(4, 4));
    arbr.insert(ft::make_pair(2, 5));
    arbr.insert(ft::make_pair(89, 5));
    arbr.insert(ft::make_pair(17, 5));
    arbr.insert(arbr.begin(), ft::make_pair(45, 5)); // tst hint
    arbr.insert(ft::make_pair(-3, 5));
    arbr.insert(ft::make_pair(8, 5));
    arbr.insert(ft::make_pair(-1, 5));
    arbr.insert(ft::make_pair(42, 5));
    arbr.insert(ft::make_pair(43, 5));
    //arbr.print();

    std::cout << "not found result: ";
    std::cout << (arbr.find(6) == arbr.end()) << std::endl;
    arbr.erase(arbr.find(2));
    ////arbr.print();
    arbr.erase(arbr.find(4));
    ////arbr.print();
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

    print_green("tst max_size", __LINE__);
    std::cout << tst_cns.max_size() << std::endl;


}

void tst_uplow_bounds(){
    print_green("Tst lower/upper_bound", __LINE__);

    //print_green("tst upper_bound and lower_bound", __LINE__);

    ft::map<char,int> mymap;
    ft::map<char,int>::iterator itlow,itup;

    mymap['a']=20;
    mymap['b']=40;
    mymap['c']=60;
    mymap['d']=80;
    mymap['e']=100;

    itlow=mymap.lower_bound ('b');  // itlow points to b
    itup=mymap.upper_bound ('d');   // itup points to e (not d!)

    mymap.erase(itlow,itup);        // erases [itlow,itup)

    // print content:
    for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    ft::map<char,int>::const_iterator citlow = mymap.lower_bound('z');
    std::cout << (citlow == mymap.end()) << '\n';
}

void tst_equal_range(){
    print_green("Tst equal_range", __LINE__);
    //print_green("tst equal_range()", __LINE__);
    ft::map<char,int> mymap;

    mymap['a']=10;
    mymap['b']=20;
    mymap['c']=30;

    ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
    ret = mymap.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void tst_fld_size(){
    print_green("Tst sz/max_sz", __LINE__);
    ft::map<const int, std::string> ui;
    ui.insert(ft::make_pair(58966, "hello coco"));
    std::cout << "size: " << ui.size() << std::endl;
    ui.erase(58966);
    std::cout << "size: " << ui.size() << std::endl;
    ui.insert(ft::make_pair(58966, "hello coco"));
    std::cout << "size: " << ui.size() << std::endl;
    std::cout << "max_size: " << ui.max_size() << std::endl;
}

template <typename T>
void	mapTest_Insert1Elem(T& cont)
{
    print_green("Test strange inserts", __LINE__);
	std::string name("insert 1 elem:");
	std::cout << "\n---------------------\n";
	T tmp = cont;
	std::cout << "size of tmp = " << tmp.size() << std::endl;

	// Allows to value initialize (case size is 0, we can't insert cont.begin())
	typename T::value_type* x = new typename T::value_type();
        //tmp.print();

	if (cont.size())
	{
		std::cout << "return value (testing boolean): " << tmp.insert(*(tmp.begin())).second<<std::endl;
        std::cout << "size of tmp = " << tmp.size() << std::endl;

		typename T::value_type pa(tmp.begin()->first, tmp.begin()->second);
        //tmp.print();
		tmp.erase(tmp.begin());
        //tmp.print();
		std::cout << "return value (testing iterator, the mapped content): " << tmp.insert(pa).first->second<<std::endl;
        //tmp.print();
	}
	std::cout << "return value (testing iterator, the key): " << (tmp.insert(*x)).first->first;

   std::cout << "size of tmp = " << tmp.size();
   for (ft::map<int,std::string>::iterator it=tmp.begin(); it!=tmp.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';

	delete x;
}

void tst_failed_ones(){
    ft::map<int, std::string> tst4;
    tst4.insert(ft::make_pair(78, "hello coco"));
    tst4.insert(ft::make_pair(190, "j'arrive"));
    mapTest_Insert1Elem(tst4);
}

void tst_relationals(){
    print_green("Test relational operators", __LINE__);
    ft::map<char,int> foo;
    ft::map<char,int> bar;
    foo['a']=100;
    foo['b']=200;
    bar['a']=10;
    bar['z']=1000;

    // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void map_all_tests(){
    print_green(__FILE__);

    cppr_pair();
    tst_binarytree();
    tst_custom_operator();
    tst_range_cpy();
    tst_uplow_bounds();
    tst_equal_range();
    tst_fld_size();
    tst_relationals();

    tst_failed_ones();
}

//int main(){ map_all_tests(); }
