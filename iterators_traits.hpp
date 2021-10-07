/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_traits.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:26:56 by majermou          #+#    #+#             */
/*   Updated: 2021/10/07 12:26:05 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP 
#define ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iostream>

template<class Iterator>
struct __iterator_traits {
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::reference            reference;
    typedef typename Iterator::iterator_category    iterator_category;
};

template<class T>
struct __iterator_traits<T*> {
    typedef ptrdiff_t                           difference_type;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef std::random_access_iterator_tag     iterator_category;
};

template<class T>
struct __iterator_traits<const T*> {
    typedef ptrdiff_t                           difference_type;
    typedef T                                   value_type;
    typedef const T*                            pointer;
    typedef const T&                            reference;
    typedef std::random_access_iterator_tag     iterator_category;
};

#endif // ITERATOR_TRAITS_HPP
