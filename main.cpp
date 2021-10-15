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
    // tree.print();

    // // std::cout << tree.search(9) << std::endl;
    // tree.remove(make_pair(9,0));
    // // std::cout << tree.search(9) << std::endl;
    // tree.print();

    std::map<char,int> mymap;

    mymap['1'] = 1;
    mymap['2'] = 2;
    mymap['3'] = 3;
    mymap['4'] = 4;

    for (std::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); it++)
    {
        std::cout << it->first << "=>" << it->second << std::endl;
    }

    return 0;
}







// template<typename _Tp>
// struct _Rb_tree_iterator
// {
//   typedef _Tp  value_type;
//   typedef _Tp& reference;
//   typedef _Tp* pointer;
//   typedef bidirectional_iterator_tag    iterator_category;
//   typedef ptrdiff_t                     difference_type;
//   typedef _Rb_tree_iterator<_Tp>        _Self;
//   typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
//   typedef _Rb_tree_node<_Tp>*           _Link_type;

//   _Rb_tree_iterator()
//   : _M_node() { }
//   explicit
//   _Rb_tree_iterator(_Link_type __x)
//   : _M_node(__x) { }
//   reference
//   operator*() const
//   { return static_cast<_Link_type>(_M_node)->_M_value_field; }
//   pointer
//   operator->() const
//   { return &static_cast<_Link_type>(_M_node)->_M_value_field; }
//   _Self&
//   operator++()
//   {
//     _M_node = _Rb_tree_increment(_M_node);
//     return *this;
//   }
//   _Self
//   operator++(int)
//   {
//     _Self __tmp = *this;
//     _M_node = _Rb_tree_increment(_M_node);
//     return __tmp;
//   }
//   _Self&
//   operator--()
//   {
//     _M_node = _Rb_tree_decrement(_M_node);
//     return *this;
//   }
//   _Self
//   operator--(int)
//   {
//     _Self __tmp = *this;
//     _M_node = _Rb_tree_decrement(_M_node);
//     return __tmp;
//   }

//   bool
//   operator==(const _Self& __x) const
//   { return _M_node == __x._M_node; }

//   bool
//   operator!=(const _Self& __x) const
//   { return _M_node != __x._M_node; }
//   _Base_ptr _M_node;

// };
