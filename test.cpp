#include <vector>
#include <iostream>
#include <algorithm>
#include "vector.hpp"

#define ns ft

class alpha {
    public:
    alpha() {
        std::cout << "alpha has been constructed\n";
    }
};

int main(void)
{
  ns::vector<int> first;
  ns::vector<int> second;
  ns::vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  ns::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';


  std::cout << "capacity of first: " << int (first.capacity()) << '\n';
  std::cout << "capacity of second: " << int (second.capacity()) << '\n';
  std::cout << "capacity of third: " << int (third.capacity()) << '\n';
  





    std::cout << "iterator : \n";
    ns::vector<int>::iterator ibegin = second.begin();
    ns::vector<int>::iterator iend = second.end();
    while (ibegin != iend) {
        std::cout << *ibegin++ << ' ';
    }
    std::cout << std::endl;
    

    // std::sort(vect.begin(), vect.end());
    // std::reverse(vect.begin(), vect.end());

    // std::cout << "const_iterator  AFTER sorting and reversing : \n";
    // ns::vector<int>::const_iterator cbegin = vect.begin();
    // ns::vector<int>::const_iterator cend = vect.end();
    // while (cbegin != cend) {
    //     std::cout << *cbegin++ << ' ';
    // }
    // std::cout << std::endl;

    // std::cout << "reverse_iterator : \n";
    // ns::vector<int>::reverse_iterator rbegin = vect.rbegin();
    // ns::vector<int>::reverse_iterator rend = vect.rend();
    // while (rbegin != rend) {
    //     std::cout << *rbegin++ << ' ';
    // }
    // std::cout << std::endl;

    // std::cout << "const_reverse_iterator : \n";
    // ns::vector<int>::const_reverse_iterator crbegin = vect.rbegin();
    // ns::vector<int>::const_reverse_iterator crend = vect.rend();
    // while (crbegin != crend) {
    //     std::cout << *crbegin++ << ' ';
    // }
    // std::cout << std::endl;

    return 0;
}
