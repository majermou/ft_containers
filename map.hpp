/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:07:39 by majermou          #+#    #+#             */
/*   Updated: 2021/10/11 12:59:31 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "avl.hpp"
#include "make_pair.hpp"
#include <iostream>

namespace ft {
template  < typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<pair<const Key,T> > >
class map {

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
  //
  //
  //
  //
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

  Avl<key_type,mapped_type>   m_Avl_tree;

public:

  // explicit  map(const key_compare& comp = key_compare(),
  //               const allocator_type& alloc = allocator_type()) {
  // }
  // // template <class InputIterator>
  // // map(InputIterator first, InputIterator last,
  // //      const key_compare& comp = key_compare(),
  // //      const allocator_type& alloc = allocator_type());
  // // map (const map& x);
  ~map() {

  }
  // // map& operator=(const map& x);

  bool empty() const {
    return m_Avl_tree.isEmpty();
  }
  size_type size() const {
    return m_Avl_tree.m_size();
  }
  size_type max_size() const {
    return m_Avl_tree.getMaxSize();
  }
  // mapped_type& operator[](const key_type& k) {
  //   (*((this->insert(make_pair(k,mapped_type()))).first)).second;
  // }
  // pair<iterator,bool> insert (const value_type& val);
  // iterator insert (iterator position, const value_type& val);
  // template <class InputIterator>
  //   void insert (InputIterator first, InputIterator last);

  // void erase (iterator position);	
  size_type erase (const key_type& k) {
    m_Avl_tree.remove(make_pair(k, mapped_type()));
    return 1;
  }
  // void erase (iterator first, iterator last);
  // void swap (map& x);
  void clear() {
    m_Avl_tree.clear();
  }
  key_compare key_comp() const {
    return key_compare();
  }
  value_compare value_comp() const {
    return value_compare();
  }
  allocator_type get_allocator() const {
    return allocator_type();
  }

};
}

#endif // MAP_HPP
