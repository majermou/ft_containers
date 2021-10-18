/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:36:38 by majermou          #+#    #+#             */
/*   Updated: 2021/10/18 12:52:10 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

template <typename T1, typename T2>
struct pair {
    typedef T1              first_type;
    typedef T2              second_type;

    first_type      first;
    second_type     second;
    pair() : first(), second() {}
    template<typename U, typename V> pair(const pair<U,V>& pr): first(pr.first), second(pr.second) {
    }
    pair (const first_type& a, const second_type& b) : first(a), second(b) {}
    pair&   operator=(const pair& pr) {
        first = pr.first;
        second = pr.second;
        return *this;
    }
};

#endif // PAIR_HPP
