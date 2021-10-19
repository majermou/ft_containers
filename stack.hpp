/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:17:13 by majermou          #+#    #+#             */
/*   Updated: 2021/10/19 19:55:47 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
template <class T, class Container = ft::vector<T> >
class stack {

public:

    typedef T                   value_type;
    typedef Container           container_type;
    typedef size_t              size_type;

private:

    typedef stack<T,Container>      Self;
    container_type                  m_ctnr;

public:

    explicit stack(const container_type& ctnr = container_type()):m_ctnr(ctnr) {
    }
    bool empty() const {
        return m_ctnr.empty();
    }
    size_type size() const {
        return m_ctnr.size();
    }
    value_type& top() {
        return m_ctnr.back();
    }
    const value_type& top() const {
        return m_ctnr.back();
    }
    void push (const value_type& val) {
        m_ctnr.push_back(val);
    }
    void pop() {
        m_ctnr.pop_back();
    }

    friend bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
    friend bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
    friend bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
    friend bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
    friend bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
    friend bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);

}; // class stack

template <class T, class Container>
bool    operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.m_ctnr == rhs.m_ctnr;
}
template <class T, class Container>
bool    operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !(lhs.m_ctnr == rhs.m_ctnr);
}
template <class T, class Container>
bool    operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.m_ctnr < rhs.m_ctnr;
}
template <class T, class Container>
bool    operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.m_ctnr <= rhs.m_ctnr;
}
template <class T, class Container>
bool    operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !(lhs.m_ctnr <= rhs.m_ctnr);
}
template <class T, class Container>
bool    operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !(lhs.m_ctnr < rhs.m_ctnr);
}

} // namespace ft

#endif // STACK_HPP
