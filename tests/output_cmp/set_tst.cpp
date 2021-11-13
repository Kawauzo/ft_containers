#include "../tests.hpp"

typedef ft::set<std::string>  spii;

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

// Cppl constructor
void cpplus_set_construct(){
    print_green("tst set construct", __LINE__);

  ft::set<int> first;                           // empty set of ints

  int myints[]= {10,20,30,40,50};
  ft::set<int> second (myints,myints+5);        // range

  ft::set<int> third (second);                  // a copy of second

  ft::set<int> fourth (second.begin(), second.end());  // iterator ctor.

  ft::set<int,classcomp> fifth;                 // class as Compare

  bool(*fn_pt)(int,int) = fncomp;
  ft::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

}

void cpplus_set_assign(){
    print_green("tst set assignment operator", __LINE__);
  int myints[]={ 12,82,37,64,15 };
  ft::set<int> first (myints,myints+5);   // set with 5 ints
  ft::set<int> second;                    // empty set

  second = first;                          // now second contains the 5 ints
  first = ft::set<int>();                 // and first is empty

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
}

void print(std::string comment, ft::set<char, int> & set) {
    std::cout << comment << "{";
    for (ft::set<char, int>::iterator it = set.begin(); it != set.end(); ++it) {
        std::cout << "{" << *it << "}";
    }
    std::cout << "}\n";
};


void cpplus_set_begin(){
    print_green("tst begin/end", __LINE__);

  int myints[] = {75,23,65,42,13};
  ft::set<int> myset (myints,myints+5);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';
}

void cpplus_set_rbegin(){
    print_green("tst rbegin/rend", __LINE__);
    int myints[] = {21,64,17,78,49};
  ft::set<int> myset (myints,myints+5);

  ft::set<int>::reverse_iterator rit;

  std::cout << "myset contains:";
  for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
    std::cout << ' ' << *rit;

  std::cout << '\n';
}

void cpplus_set_size(){
    print_green("tst set size()", __LINE__);
    ft::set<int> myset;

    myset.insert(20);
    myset.insert(30);
    myset.insert(10);

    std::cout << "myset contains:";
    while (!myset.empty()) {
         std::cout << ' ' << *myset.begin();
         myset.erase(myset.begin());
    }
    std::cout << '\n';
}

void cpplus_set_max_size(){
    print_green("tst set max_size()", __LINE__);
    int i;
    ft::set<int> myset;

    if (myset.max_size()>1000) {
        for (i=0; i<1000; i++) myset.insert(i);
        std::cout << "The set contains 1000 elements.\n";
    }
    else std::cout << "The set could not hold 1000 elements.\n";
}

void cpplus_set_count(){
    print_green("tst count", __LINE__);

  ft::set<int> myset;

  // set some initial values:
  for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12

  for (int i=0; i<10; ++i)
  {
    std::cout << i;
    if (myset.count(i)!=0)
      std::cout << " is an element of myset.\n";
    else
      std::cout << " is not an element of myset.\n";
  }
}


void cpplus_set_insert(){
    print_green("tst set insert()", __LINE__);
    ft::set<int> myset;
    ft::set<int>::iterator it;
    ft::pair<ft::set<int>::iterator,bool> ret;

    // set some initial values:
    for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50

    ret = myset.insert(20);               // no new element inserted

    if (ret.second==false) it=ret.first;  // "it" now points to element 20

    myset.insert (it,25);                 // max efficiency inserting
    myset.insert (it,24);                 // max efficiency inserting
    myset.insert (it,26);                 // no max efficiency inserting

    int myints[]= {5,10,15};              // 10 already in set, not inserted
    myset.insert (myints,myints+3);

    std::cout << "myset contains:";
    for (it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void cpplus_set_erase(){
    print_green("tst set erase()", __LINE__);
    ft::set<int> myset;
    ft::set<int>::iterator it;

    // insert some values:
    for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

    it = myset.begin();
    ++it;                                         // "it" points now to 20

    myset.erase (it);

    myset.erase (40);

    it = myset.find (60);
    myset.erase (it, myset.end());

    std::cout << "myset contains:";
    for (it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void cpplus_set_swap(){
    print_green("tst set swap()", __LINE__);

    int myints[]={12,75,10,32,20,25};
    ft::set<int> first (myints,myints+3);     // 10,12,75
    ft::set<int> second (myints+3,myints+6);  // 20,25,32

    first.swap(second);

    std::cout << "first contains:";
    for (ft::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "second contains:";
    for (ft::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void cpplus_set_clear(){
    print_green("tst set clear()", __LINE__);
    ft::set<int> myset;

    myset.insert (100);
    myset.insert (200);
    myset.insert (300);

    std::cout << "myset contains:";
    for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    myset.clear();
    myset.insert (1101);
    myset.insert (2202);

    std::cout << "myset contains:";
    for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void cpplus_set_key_comp(){
    print_green("tst set key_comp", __LINE__);
    ft::set<int> myset;
    int highest;

    ft::set<int>::key_compare mycomp = myset.key_comp();

    for (int i=0; i<=5; i++) myset.insert(i);

    std::cout << "myset contains:";

    highest=*myset.rbegin();
    ft::set<int>::iterator it=myset.begin();
    do {
        std::cout << ' ' << *it;
    } while ( mycomp(*(++it),highest) );

    std::cout << '\n';
}

void cpplus_set_value_comp(){
    print_green("tst set value_comp", __LINE__);
    ft::set<int> myset;

    ft::set<int>::value_compare mycomp = myset.value_comp();

    for (int i=0; i<=5; i++) myset.insert(i);

    std::cout << "myset contains:";

    int highest=*myset.rbegin();
    ft::set<int>::iterator it=myset.begin();
    do {
        std::cout << ' ' << *it;
    } while ( mycomp(*(++it),highest) );

    std::cout << '\n';
}

void cpplus_set_find(){
    print_green("tst set find()", __LINE__);
    ft::set<int> myset;
    ft::set<int>::iterator it;

    // set some initial values:
    for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

    it=myset.find(20);
    myset.erase (it);
    myset.erase (myset.find(40));

    std::cout << "myset contains:";
    for (it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}




void cpplus_set_lower_upper_bound(){
    print_green("tst lower_upper_bound", __LINE__);
  ft::set<int> myset;
  ft::set<int>::iterator itlow,itup;

  for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

  itlow=myset.lower_bound (30);                //       ^
  itup=myset.upper_bound (60);                 //                   ^

  myset.erase(itlow,itup);                     // 10 20 70 80 90

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void cpplus_set_equal_range(){
    print_green("tst equal_range", __LINE__);
    ft::set<int> myset;

  for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

  ft::pair<ft::set<int>::const_iterator,ft::set<int>::const_iterator> ret;
  ret = myset.equal_range(30);

  std::cout << "the lower bound points to: " << *ret.first << '\n';
  std::cout << "the upper bound points to: " << *ret.second << '\n';
}

void tst_set_binarytree(){
    print_green("Tst insert/erase", __LINE__);
    spii arbr;

    arbr.insert("324");
    arbr.insert("327");
    arbr.insert("327");
    arbr.insert("325");
    arbr.insert("327");
    arbr.insert("334");
    arbr.insert("340");
    arbr.insert("346");
    arbr.insert("345");
    arbr.insert("324");
    arbr.insert("394");
    arbr.insert("337");
    arbr.insert("377");

    std::cout << "not found result: ";
    std::cout << (arbr.find("667") == arbr.end()) << std::endl;
    std::cout << "size: " << arbr.size() << '\n';
    arbr.erase(arbr.find("394"));
    ////arbr.print();
    std::cout << "erase ret: " << arbr.erase("346") << '\n';
    std::cout << "erase ret: " << arbr.erase("327") << '\n';
    ////arbr.print();
    arbr.erase(arbr.find("324"));
    ////arbr.print();
    arbr.erase(arbr.find("377"));
    ////arbr.print();
    std::cout << "count ret: " << arbr.count("345") << '\n';
    std::cout << "count ret: " << arbr.count("327") << '\n';
    std::cout << "size: " << arbr.size() << '\n';
    arbr.clear();

    std::cout << '\n';
    arbr.insert("667");
    arbr.insert("657");
    arbr.insert("637");
    arbr.insert("641");
    arbr.insert("620");
    arbr.insert("566");
    arbr.insert("267");

    std::cout << '\n';

    for ( spii::iterator it = arbr.begin(); it != arbr.end(); ++it)
        std::cout << *it << std::endl;

    for ( spii::iterator it = --arbr.end(); it != arbr.begin(); --it)
        std::cout << *it << std::endl;
    std::cout << "size: " << arbr.size() << '\n';


    for ( spii::reverse_iterator rit = arbr.rbegin(); rit != arbr.rend(); ++rit)
        std::cout << *rit << std::endl;

}

void tst_set_const_error(spii seti)
{
    print_green("Tst const_iterator", __LINE__);
    spii::const_iterator roland(seti.begin());
    while (roland != seti.end()){
        std::cout << *roland << std::endl;
        roland++;
    }

    spii::iterator       it(seti.begin());
    spii::const_iterator cend(seti.end());
    while (it != cend){
        std::cout << *it << std::endl;
        it++;
    }

    spii::const_reverse_iterator simon = seti.rbegin();
    while (simon != seti.rend()){
        std::cout << *simon << std::endl;
        simon++;
    }
}


void tst_set_custom_operator(){
    print_green("Tst set with custom comparison operator", __LINE__);
    typedef ft::set<int, std::greater<int> >  rev_spii;
    rev_spii arbr;

    arbr.insert(1);
    arbr.insert(1);
    arbr.insert(22);
    arbr.insert(19); // try to break erase
    arbr.insert(4);
    arbr.insert(2);
    arbr.insert(89);
    arbr.insert(17);
    arbr.insert(arbr.begin(), 45); // tst hint
    arbr.insert(-3);
    arbr.insert(8);
    arbr.insert(-1);
    arbr.insert(42);
    arbr.insert(43);
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

    for ( rev_spii::iterator it = arbr.begin(); it != arbr.end(); ++it)
        std::cout << *it << std::endl;

    for ( rev_spii::iterator it = --arbr.end(); it != arbr.begin(); --it)
        std::cout << *it << std::endl;
    std::cout << "size: " << arbr.size() << '\n';
}

void tst_set_range_cpy(){
    std::string tab[] = {"12", "27", "98", "8", "-2", "8", "76", "11", "3" };

    spii tst_ins;
    tst_ins.insert(tab, tab+8);
    for ( spii::iterator it = tst_ins.begin(); it != tst_ins.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "size: " << tst_ins.size() << '\n';

    spii tst_cns(tst_ins.begin(), tst_ins.end());
    for ( spii::iterator it = tst_cns.begin(); it != tst_cns.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "size: " << tst_cns.size() << '\n';

    spii tst_cpy(tst_cns);
    for ( spii::iterator it = tst_cns.begin(); it != tst_cns.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "size: " << tst_cns.size() << '\n';

    print_green("tst max_size", __LINE__);
    std::cout << tst_cns.max_size() << std::endl;


}

void tst_set_fld_size() {
    print_green("Tst sz/max_sz", __LINE__);
    ft::set<int> ui;
    ui.insert(58966);
    std::cout << "size: " << ui.size() << std::endl;
    ui.erase(58966);
    std::cout << "size: " << ui.size() << std::endl;
    ui.insert(58966);
    std::cout << "size: " << ui.size() << std::endl;
}

template <typename T>
void	setTest_Insert1Elem(T& cont)
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

		tmp.erase(tmp.begin());
	}
	std::cout << "return value (testing iterator, the key): " << *(tmp.insert(*x)).first;

   std::cout << "size of tmp = " << tmp.size();
   for (ft::set<std::string>::iterator it=tmp.begin(); it!=tmp.end(); ++it)
      std::cout << *it << '\n';

	delete x;
}

void tst_set_failed_ones(){
    ft::set<std::string> tst4;
    tst4.insert("hello coco");
    tst4.insert("j'arrive");
    setTest_Insert1Elem(tst4);
}

void tst_set_relationals(){
    print_green("Test relational operators", __LINE__);
    ft::set<int> foo;
    ft::set<int> bar;
    foo.insert(100);
    foo.insert(200);
    bar.insert(10);
    bar.insert(1000);

    // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void set_all_tests(){
    print_green(__FILE__);

    cpplus_set_construct();
    cpplus_set_assign();

    cpplus_set_begin();
    cpplus_set_rbegin();
    cpplus_set_size();
    cpplus_set_max_size();
    cpplus_set_insert();
    cpplus_set_erase();
    cpplus_set_swap();
    cpplus_set_clear();
    cpplus_set_key_comp();
    cpplus_set_value_comp();
    cpplus_set_find();
    cpplus_set_count();
    cpplus_set_lower_upper_bound();
    cpplus_set_equal_range();

    tst_set_binarytree();
    tst_set_custom_operator();
    tst_set_range_cpy();
    tst_set_fld_size();
    tst_set_relationals();

    tst_set_failed_ones();
}

//int main(){ set_all_tests(); }
