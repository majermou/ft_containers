/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:11:55 by majermou          #+#    #+#             */
/*   Updated: 2021/10/19 14:44:34 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

template <typename InputIterator1, typename InputIterator2>
bool    equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2) {
    while (first1!=last1) {
        if (!(*first1 == *first2))
            return false;
        ++first1;
        ++first2;
    }
    return true;
}

template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
bool    equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,BinaryPredicate pred) {
    while (first1!=last1) {
        if (!(pred(*first1,*first2)))
            return false;
        ++first1;
        ++first2;
    }
    return true;
}

#endif // EQUAL_HPP
