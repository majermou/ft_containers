/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_traits.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:26:56 by majermou          #+#    #+#             */
/*   Updated: 2021/10/06 19:52:07 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP 
#define ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iostream>

struct   input_iterator_tag { };
struct   output_iterator_tag { };
struct   forward_iterator_tag : public input_iterator_tag { };
struct   bidirectional_iterator_tag : public forward_iterator_tag { };
struct   random_access_iterator_tag : public bidirectional_iterator_tag{ };

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
    typedef ptrdiff_t                   difference_type;
    typedef T                           value_type;
    typedef T*                          pointer;
    typedef T&                          reference;
    typedef random_access_iterator_tag  iterator_category;
};

template<class T>
struct __iterator_traits<const T*> {
    typedef ptrdiff_t                   difference_type;
    typedef T                           value_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
    typedef random_access_iterator_tag  iterator_category;
};

#endif // ITERATOR_TRAITS_HPP
