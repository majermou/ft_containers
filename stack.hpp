/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:17:13 by majermou          #+#    #+#             */
/*   Updated: 2021/10/20 19:21:51 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack {

public:

    typedef T                   value_type;
    typedef Container           container_type;
    typedef size_t              size_type;

protected:

    container_type              c;

public:

    explicit stack(const container_type _c = container_type()): c(_c) {
    }
    bool empty() const {
        return c.empty();
    }
    size_type size() const {
        return c.size();
    }
    value_type& top() {
        return c.back();
    }
    const value_type& top() const {
        return c.back();
    }
    void push (const value_type& val) {
        c.push_back(val);
    }
    void pop() {
        c.pop_back();
    }

    template<typename U, typename I>
    friend bool operator==(const stack<U,I>& lhs, const stack<U,I>& rhs);
    template<typename U, typename I>
    friend bool operator!=(const stack<U,I>& lhs, const stack<U,I>& rhs);
    template<typename U, typename I>
    friend bool operator< (const stack<U,I>& lhs, const stack<U,I>& rhs);
    template<typename U, typename I>
    friend bool operator<=(const stack<U,I>& lhs, const stack<U,I>& rhs);
    template<typename U, typename I>
    friend bool operator>(const stack<U,I>& lhs, const stack<U,I>& rhs);
    template<typename U, typename I>
    friend bool operator>=(const stack<U,I>& lhs, const stack<U,I>& rhs);

}; // class stack

template <class T, class Container>
bool    operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.c == rhs.c;
}
template <class T, class Container>
bool    operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !(lhs.c == rhs.c);
}
template <class T, class Container>
bool    operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.c < rhs.c;
}
template <class T, class Container>
bool    operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return lhs.c <= rhs.c;
}
template <class T, class Container>
bool    operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !(lhs.c <= rhs.c);
}
template <class T, class Container>
bool    operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return !(lhs.c < rhs.c);
}

} // namespace ft

#endif // STACK_HPP
