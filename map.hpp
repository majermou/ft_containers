/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:07:39 by majermou          #+#    #+#             */
/*   Updated: 2021/10/10 17:48:35 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "make_pair.hpp"
#include <iostream>

namespace ft {
template  <
            typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<pair<const Key,T> >
          >
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

private:

public:

};
}

#endif // MAP_HPP
