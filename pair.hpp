/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:36:38 by majermou          #+#    #+#             */
/*   Updated: 2021/10/24 11:31:14 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
template <typename T1, typename T2>
struct pair {
    typedef T1      first_type;
    typedef T2      second_type;

    first_type      first;
    second_type     second;
    pair() : first(), second() {}
    template<typename U, typename V>
    pair(const pair<U,V>& pr): first(pr.first), second(pr.second) {}
    pair (const first_type& a, const second_type& b) : first(a), second(b) {}
    pair&   operator=(const pair& pr) {
        first = pr.first;
        second = pr.second;
        return *this;
    }

    template <class U1, class U2>
    friend bool operator==(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
    template <class U1, class U2>
    friend bool operator!=(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
    template <class U1, class U2>
    friend bool operator<(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
    template <class U1, class U2>
    friend bool operator<=(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
    template <class U1, class U2>
    friend bool operator>(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
    template <class U1, class U2>
    friend bool operator>=(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
};

template <class T1, class T2>
bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}
template <class T1, class T2>
bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return !(lhs == rhs);
}
template <class T1, class T2>
bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}
template <class T1, class T2>
bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return !(rhs < lhs);
}	
template <class T1, class T2>
bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return rhs < lhs;
}
template <class T1, class T2>
bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return !(lhs < rhs);
}

}

#endif // PAIR_HPP
