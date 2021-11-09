#include "../tests.hpp"
#include <deque>

void cppr_ctr(){
    ft::stack<int> c1;
    c1.push(5);
    std::cout << c1.size() << '\n';

    ft::stack<int> c2(c1);
    std::cout << c2.size() << '\n';

    int tab[] =  {3, 1, 4, 1, 5};
    ft::vector<int> vec(tab, tab+5);
    ft::stack<int, ft::vector<int> > c3(vec);
    std::cout << c3.size() << '\n';
}

void reportStackSize(const ft::stack<int>& s)
{
    std::cout << s.size() << " elements on stack\n";
}

void reportStackTop(const ft::stack<int>& s)
{
    // Leaves element on stack
    std::cout << "Top element: " << s.top() << '\n';
}

void cppr_top(){
    ft::stack<int> s;
    s.push(2);
    s.push(6);
    s.push(51);

    reportStackSize(s);
    reportStackTop(s);

    reportStackSize(s);
    s.pop();

    reportStackSize(s);
    reportStackTop(s);
}

void cppc_ctr(){
  std::deque<int> mydeque (3,100);          // deque with 3 elements
  ft::vector<int> myvector (2,200);        // vector with 2 elements

  ft::stack<int> first;                    // empty stack
  ft::stack<int, std::deque<int> > second (mydeque);         // stack initialized to copy of deque

  ft::stack<int> third;  // empty stack using vector
  ft::stack<int, ft::vector<int> > fourth (myvector);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';
}

void cppc_empty(){
   ft::stack<int> mystack;
  int sum (0);

  for (int i=1;i<=10;i++) mystack.push(i);

  while (!mystack.empty())
  {
     sum += mystack.top();
     mystack.pop();
  }

  std::cout << "total: " << sum << '\n';
}

void cppc_top(){
  ft::stack<int> mystack;

  mystack.push(10);
  mystack.push(20);

  mystack.top() -= 5;

  std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void cppc_pushpop(){
  ft::stack<int> mystack;

  for (int i=0; i<5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';
}

void stack_all_tests(){
    cppr_ctr();
    cppr_top();
    cppc_ctr();
    cppc_pushpop();
    cppc_top();
    cppc_empty();
}
