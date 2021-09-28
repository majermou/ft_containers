#include "vector.hpp"
#include <algorithm>

int main(void) {

    ft::vector<int> integers;

    for (int i = 0; i < 20; ++i)
        integers.push_back(i);

    ft::vector<int>::iterator it = integers.begin();
    while (it != integers.end())
        std::cout << *it++ << ", ";
    std::cout << '\n'; 

    return 0;
}