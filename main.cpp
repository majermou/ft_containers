#include <iostream>
#include "map.hpp"
#include <map>

int main()
{
    // Avl<pair<int,int>,ft::map<int,int>::value_compare>    tree;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     tree.insert(make_pair(i,9));
    // }
    // tree.print();
    srand(time(NULL));
    ft::map<const int,int> mymap;
    for (size_t i = 1; i <= 10; i++)
    {
        mymap.insert(make_pair(rand()%100,i));
        // mymap[i] = i;
    }

    mymap.print();
    // std::cout << mymap.begin()->first << std::endl;
    // std::cout << (mymap.end())->first << std::endl;

    for (ft::map<const int, int>::iterator it = mymap.begin();it != mymap.end(); it++) {
        // std::cout << "lolo\n";
        std::cout << it->first  << '\n';
    }

    return 0;
}
