#include <vector>
#include <iostream>
#include <algorithm>
#include "vector.hpp"

#define ns ft

int main(void)
{
    ns::vector<int> vect;

    vect.push_back(1);
    vect.push_back(0);
    vect.push_back(4);
    vect.push_back(2);

    // std::cout << "iterator : \n";
    // ns::vector<int>::iterator begin = vect.begin();
    // ns::vector<int>::iterator end = vect.end();
    // while (begin != end) {
    //     std::cout << *begin++ << ' ';
    // }
    // std::cout << std::endl;

    bool val = (typeid(std::iterator_traits<ns::vector<int>::iterator>::value_type) == typeid(int)) ? 1: 0;

    std::cout << val;


    // std::sort(begin, end);
    // std::reverse(begin, end);
    
    // std::cout << "const_iterator : \n";
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
