/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:07:39 by majermou          #+#    #+#             */
/*   Updated: 2021/10/24 10:56:01 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "avl_tree.hpp"
#include "reverse_iterator.hpp"
#include "vector.hpp"

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
  typedef pair<const key_type,mapped_type>                value_type;
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
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

private:

  value_compare                                                 m_comp;
  allocator_type                                                m_allocator;
  Avl_tree<value_type,value_compare>                            m_Avl_tree;
  typedef typename Avl_tree<value_type,value_compare>::AvlNode  AvlNode;

public:

  explicit  map(const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type())
                : m_comp(comp), m_allocator(alloc),
                  m_Avl_tree(value_compare(m_comp)) {
  }
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : m_comp(comp), m_allocator(alloc), 
        m_Avl_tree(value_compare(comp)) {
    while (first != last) {
      m_Avl_tree.insert(ft::make_pair(first->first,first->second));
      first++;
    }
  }
  map (const map& x): m_comp(x.m_comp), m_allocator(x.m_allocator),
                      m_Avl_tree(value_compare(m_comp)) {
    const_iterator first = x.begin();
    const_iterator last = x.end();
    while (first != last) {
      m_Avl_tree.insert(ft::make_pair(first->first,first->second));
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
        m_Avl_tree.insert(ft::make_pair(first->first,first->second));
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
    return (*((insert(ft::make_pair(k,mapped_type()))).first)).second;
  }
  pair<iterator,bool> insert(const value_type& val) {
    AvlNode node = m_Avl_tree.search(val);

    if (!m_Avl_tree.getEndNode() || node == m_Avl_tree.getEndNode()) {
      m_Avl_tree.insert(val);
      return ft::make_pair(iterator(m_Avl_tree.search(val)), true);
    } else {
      return ft::make_pair(iterator(node), false);
    }
  }
  iterator insert(iterator position, const value_type& val) {
    AvlNode node = m_Avl_tree.search(val);

    if (!m_Avl_tree.getEndNode() || node == m_Avl_tree.getEndNode()) {
      insert(val);
    }
    return iterator(m_Avl_tree.search(val));
    position++;
  }
  template <class InputIterator>
  void insert (InputIterator first, InputIterator last) {
    while (first != last) {
      insert(ft::make_pair(first->first,first->second));
      first++;
    }
  }
  void erase (iterator position) {
    if (position != iterator(NULL)) {
      m_Avl_tree.remove(ft::make_pair(position->first,position->second));
    }
  }
  size_type erase (const key_type& k) {
    AvlNode node = m_Avl_tree.search(ft::make_pair(k,mapped_type()));
    
    if (!m_Avl_tree.getEndNode() || node == m_Avl_tree.getEndNode()) {
      return 0;
    }
    m_Avl_tree.remove(ft::make_pair(k,mapped_type()));
    return 1;
  }
  void erase (iterator first, iterator last) {
    ft::vector<ft::pair<key_type,mapped_type> > elementsTodelete;

    while (first != last) {
      elementsTodelete.push_back(ft::make_pair(first->first,first->second));
      first++;
    }
    while (elementsTodelete.size() > 0) {
      
      m_Avl_tree.remove(elementsTodelete.back());
      elementsTodelete.pop_back();
    }
  }
  void swap (map& x) {
    m_Avl_tree.swap(x.m_Avl_tree);
  }
  void clear() {
    m_Avl_tree.clear();
  }
  key_compare key_comp() const {
    return key_compare();
  }
  value_compare value_comp() const {
    return value_compare(m_comp);
  }
  iterator find(const key_type& k) {
    return iterator(m_Avl_tree.search(ft::make_pair(k,mapped_type())));
  }
  const_iterator find(const key_type& k) const {
    return const_iterator(m_Avl_tree.search(ft::make_pair(k,mapped_type())));
  }
  size_type count(const key_type& k) const {
    AvlNode node = m_Avl_tree.search(ft::make_pair(k,mapped_type()));
    
    if (!m_Avl_tree.getEndNode() || node == m_Avl_tree.getEndNode()) {
      return 0;
    }
    return 1;
  }
  iterator lower_bound(const key_type& k) {
    return iterator(m_Avl_tree.getLower_bound(ft::make_pair(k,mapped_type())));
  }
  const_iterator lower_bound(const key_type& k) const {
    return const_iterator(m_Avl_tree.getLower_bound(ft::make_pair(k,mapped_type())));
  }
  iterator upper_bound(const key_type& k) {
    return iterator(m_Avl_tree.getUpper_bound(ft::make_pair(k,mapped_type())));
  }
  const_iterator upper_bound(const key_type& k) const {
    return const_iterator(m_Avl_tree.getUpper_bound(ft::make_pair(k,mapped_type())));
  }
  ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
    AvlNode node = m_Avl_tree.search(ft::make_pair(k,mapped_type()));

    if (!m_Avl_tree.getEndNode() || node == m_Avl_tree.getEndNode()) {
      return ft::make_pair(lower_bound(k), lower_bound(k));
    }
    return ft::make_pair(const_iterator(node), upper_bound(k));
  }
  ft::pair<iterator,iterator>             equal_range (const key_type& k) {
    AvlNode node = m_Avl_tree.search(ft::make_pair(k,mapped_type()));

    if (!m_Avl_tree.getEndNode() || node == m_Avl_tree.getEndNode()) {
      return ft::make_pair(lower_bound(k), lower_bound(k));
    }
    return ft::make_pair(iterator(node), upper_bound(k));
  }
  allocator_type get_allocator() const {
    return allocator_type();
  }

  void  print() { m_Avl_tree.print();}
};
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
