#include <iostream>
#include <vector>
#include <map>
#include "vector.hpp"
// #include "map.hpp"

// #define ns ft

// class alpha {
//     public:
//     alpha() {
//         std::cout << "alpha has been constructed\n";
//     }
// };

// int main(void)
// {
//     ns::vector<int> vect(10);

//     vect.push_back(4);
//     vect.push_back(0);
//     vect.push_back(-1);
//     vect.push_back(10);
//     vect.push_back(3);
    
//     std::cout << "iterator : \n";
//     ns::vector<int>::iterator begin = vect.begin();
//     ns::vector<int>::iterator end = vect.end();
//     while (begin != end) {
//         std::cout << *begin++ << ' ';
//     }
//     std::cout << std::endl;


//     std::sort(vect.begin(), vect.end());
//     std::reverse(vect.begin(), vect.end());

//     std::cout << "const_iterator  AFTER sorting and reversing : \n";
//     ns::vector<int>::const_iterator cbegin = vect.begin();
//     ns::vector<int>::const_iterator cend = vect.end();
//     while (cbegin != cend) {
//         std::cout << *cbegin++ << ' ';
//     }
//     std::cout << std::endl;

//     std::cout << "reverse_iterator : \n";
//     ns::vector<int>::reverse_iterator rbegin = vect.rbegin();
//     ns::vector<int>::reverse_iterator rend = vect.rend();
//     while (rbegin != rend) {
//         std::cout << *rbegin++ << ' ';
//     }
//     std::cout << std::endl;

//     std::cout << "const_reverse_iterator : \n";
//     ns::vector<int>::const_reverse_iterator crbegin = vect.rbegin();
//     ns::vector<int>::const_reverse_iterator crend = vect.rend();
//     while (crbegin != crend) {
//         std::cout << *crbegin++ << ' ';
//     }
//     std::cout << std::endl;

//     return 0;
// }


// map::value_comp
#include <iostream>
#include <map>

int main ()
{
  std::map<char,int> mymap;

  mymap['x']=   1001;
  mymap['z']=   2002;
  mymap['y']=   3003;

  std::cout << "mymap contains:\n";

  std::pair<char,int> highest = *mymap.rbegin();          // last element

  std::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

  return 0;
}
