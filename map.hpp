/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:07:39 by majermou          #+#    #+#             */
/*   Updated: 2021/10/18 14:11:53 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "avl.hpp"
#include "reverse_iterator.hpp"

template<typename T> struct Iterator;
template<typename T> struct ConstIterator;

namespace ft {
template  < typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<pair<const Key,T> > > class map {
public:

  typedef Key                                             key_type;
  typedef T                                               mapped_type;
  typedef pair<key_type,mapped_type>                      value_type;
  typedef Compare                                         key_compare;
  typedef Alloc                                           allocator_type;
  typedef typename allocator_type::reference              reference;
  typedef typename allocator_type::const_reference        const_refernce;
  typedef typename allocator_type::pointer                pointer;
  typedef typename allocator_type::const_pointer          const_pointer;
  typedef typename allocator_type::difference_type        difference_type;
  typedef typename allocator_type::size_type              size_type;
  typedef Iterator<value_type>                            iterator;
  typedef ConstIterator<value_type>                       const_iterator;
  typedef ReverseIterator<iterator>                       reverse_iterator;
  typedef ReverseIterator<const_iterator>                 const_reverse_iterator;

  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map;
  protected:
    key_compare   comp;
    value_compare(key_compare c) : comp(c) {}
  public:
    value_compare() {}
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

private:

  Avl<value_type,value_compare>   m_Avl_tree;
  typedef typename Avl<value_type,value_compare>::AvlNode AvlNode;
  typedef ft::map<key_type,mapped_type>   Self;

public:

  explicit  map() {
  }
  template <class InputIterator>
  map(InputIterator first, InputIterator last) {
    while (first != last) {
      m_Avl_tree.insert(make_pair(first->first,first->second));
      first++;
    }
  }
  map (const map& x) {
    const_iterator first = x.begin();
    const_iterator last = x.end();
    while (first != last) {
      m_Avl_tree.insert(make_pair(first->first,first->second));
      first++;
    }
  }
  ~map() {
  }
  map& operator=(const map& x) {
    if (this != &x) {
      clear();
      const_iterator first = x.begin();
      const_iterator last = x.end();
      while (first != last) {
        m_Avl_tree.insert(make_pair(first->first,first->second));
        first++;
      }
    }
    return *this;
  }

  iterator begin() {
    return iterator(m_Avl_tree.getMinValNode());
  }
  const_iterator begin() const {
    return const_iterator(m_Avl_tree.getMinValNode());
  }
  iterator end() {
    return iterator(m_Avl_tree.getEndNode());
  }
  const_iterator end() const {
    return const_iterator(m_Avl_tree.getEndNode());
  }
  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() {
    return reverse_iterator(begin());
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  bool empty() const {
    return m_Avl_tree.isEmpty();
  }
  size_type size() const {
    return m_Avl_tree.getSize();
  }
  size_type max_size() const {
    return m_Avl_tree.getMaxSize();
  }

  mapped_type& operator[] (const key_type& k) {
    return (*((insert(pr::make_pair(k,mapped_type()))).first)).second;
  }
  pair<iterator,bool> insert(const value_type& val) {
    AvlNode node = m_Avl_tree.search(val);

    if (node == NULL) {
      m_Avl_tree.insert(val);
      return pr::make_pair(iterator(m_Avl_tree.search(val)), true);
    } else {
      return pr::make_pair(iterator(node), false);
    }
  }
  iterator insert(iterator position, const value_type& val) {
    insert(val);
    return position;
    //need to be improved (effecient insertion with position)
  }
  template <class InputIterator>
  void insert (InputIterator first, InputIterator last) {
    while (first != last) {
      insert(pr::make_pair(first->first,first->second));
      first++;
    }
  }
  void erase (iterator position) {
    m_Avl_tree.remove(pr::make_pair(position->first,mapped_type()));
  }
  size_type erase (const key_type& k) {
    AvlNode node = m_Avl_tree.search(pr::make_pair(k,mapped_type()));
    if (node != NULL) {
      m_Avl_tree.remove(pr::make_pair(k,mapped_type()));
      return 1;
    }
    return 0;
  }
  void erase (iterator first, iterator last) {
    while (first != last) {
      m_Avl_tree.remove(pr::make_pair(first->first,mapped_type()));
      first++;
    }
  }

  //swap
  void swap (map& x) {
    Self  tree;

    tree.insert(x.begin(), x.end());
    x.clear();
    x.insert(begin(), end());
    clear();
    insert(tree.begin(), tree.end());
    tree.clear();
  }

  void clear() {
    m_Avl_tree.clear();
  }

  key_compare key_comp() const {
    return key_compare();
  }
  value_compare value_comp() const {
    return value_compare();
  }

  iterator find(const key_type& k) {
    return iterator(m_Avl_tree.search(pr::make_pair(k,mapped_type())));
  }
  const_iterator find(const key_type& k) const {
    return const_iterator(m_Avl_tree.search(pr::make_pair(k,mapped_type())));
  }
  size_type count(const key_type& k) const {
    AvlNode node = m_Avl_tree.search(pr::make_pair(k,mapped_type()));
    
    if (node == NULL) {
      return 0;
    }
    return 1;
  }
  // iterator lower_bound (const key_type& k) {
    
  // }
  // const_iterator lower_bound (const key_type& k) const {
    
  // }




  void    print() {
    m_Avl_tree.print();
  }





  allocator_type get_allocator() const {
    return allocator_type();
  }
};
}

template<typename NodePtr>
NodePtr  Avl_tree_increment(NodePtr x) {
  if (x->right) {
    x = x->right;
    while (x->left) {
      x = x->left;
    }
  } else {
    NodePtr y = x->parent;
    while (x == y->right) {
      x = y;
      y = y->parent;
    }
    if (x->right != y) {
      x = y;
    }
  }
  return x;
}

template<typename NodePtr>
NodePtr Avl_tree_decrement(NodePtr x) {
  if (x->left) {
    NodePtr y = x->left;
    while (y->right) {
      y = y->right;
    }
    x = y;
  } else {
    NodePtr y = x->parent;
    while (x == y->left) {
      x = y;
      y = y->parent;
    }
    x = y;
  }
  return x;
}

template<typename T>
struct Iterator{
  typedef T                                 value_type;
  typedef T*                                pointer;
  typedef T&                                reference;
  typedef ptrdiff_t                         difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef Iterator<T>                       Self;
  typedef typename Node<T>::NodePtr         NodePtr;

  Iterator(): m_node() {}
  explicit Iterator(NodePtr x): m_node(x) {}

  reference operator*() const {
    return (m_node)->data;
  }
  pointer operator->() const {
    return &(m_node)->data;
  }
  Self  operator++() {
    m_node = Avl_tree_increment<NodePtr>(m_node);
    return *this;
  }
  Self operator++(int) {
    Self tmp = *this;
    m_node = Avl_tree_increment<NodePtr>(m_node);
    return tmp;
  }
  Self  operator--() {
    m_node = Avl_tree_decrement<NodePtr>(m_node);
    return *this;
  }
  Self  operator--(int) {
    Self tmp = *this;
    m_node = Avl_tree_decrement<NodePtr>(m_node);
    return tmp;
  }
  bool  operator==(const Self& x) const {
    return m_node == x.m_node;
  }
  bool  operator!=(const Self& x) const {
    return m_node != x.m_node;
  }

  NodePtr       m_node;
};

template<typename T>
struct ConstIterator {
  typedef T                                 value_type;
  typedef const T*                          pointer;
  typedef const T&                          reference;
  typedef ptrdiff_t                         difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;
  typedef Iterator<T>                       iterator;
 
  typedef ConstIterator<T>                  Self;
  typedef typename Node<T>::Const_NodePtr   NodePtr;

  ConstIterator(): m_node() { }
  explicit ConstIterator(NodePtr x): m_node(x) { }
  ConstIterator(const iterator& it): m_node(it.m_node) { }

  reference operator*() const {
    return (m_node)->data;
  }
  pointer operator->() const {
    return &(m_node)->data;
  }
  Self& operator++() {
    m_node = Avl_tree_increment<NodePtr>(m_node);
    return *this;
  }
  Self  operator++(int) {
    Self tmp = *this;
    m_node = Avl_tree_increment<NodePtr>(m_node);
    return tmp;
  }
  Self& operator--() {
    m_node = Avl_tree_decrement<NodePtr>(m_node);
    return *this;
  }
  Self  operator--(int) {
    Self tmp = *this;
    m_node = Avl_tree_decrement<NodePtr>(m_node);
    return tmp;
  }
  bool  operator==(const Self& x) const {
    return m_node == x.m_node;
  }
  bool  operator!=(const Self& x) const {
    return m_node != x.m_node;
  }

  NodePtr   m_node;
};

template<typename NodePtr>
inline bool operator==(const Iterator<NodePtr>& x, const ConstIterator<NodePtr>& y) {
  return x.m_node == y.m_node;
}

template<typename NodePtr>
inline bool operator!=(const Iterator<NodePtr>& x, const ConstIterator<NodePtr>& y) {
  return x.m_node != y.m_node;
}

#endif // MAP_HPP
