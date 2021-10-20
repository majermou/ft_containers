/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:51:41 by majermou          #+#    #+#             */
/*   Updated: 2021/10/20 16:04:16 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_PAIR_HPP
#define MAKE_PAIR_HPP

#include "pair.hpp"

namespace ft {

template <class T1, class T2>
ft::pair<T1,T2> make_pair(T1 x, T2 y) {
    return ft::pair<T1, T2>(x, y);
}
}

#endif // MAKE_PAIR_HPP
