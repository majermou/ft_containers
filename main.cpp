#include <iostream>
#include <map>
#include "map.hpp"

int main()
{
    Avl<int,int>    tree;

    for (size_t i = 0; i < 10; i++)
    {
        tree.insert(make_pair(i,9));
    }
    tree.print();

    // std::cout << tree.search(9) << std::endl;
    tree.remove(make_pair(9,0));
    // std::cout << tree.search(9) << std::endl;
    tree.print();


    return 0;
}
