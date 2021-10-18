/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:51:41 by majermou          #+#    #+#             */
/*   Updated: 2021/10/18 13:32:56 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_PAIR_HPP
#define MAKE_PAIR_HPP

#include "pair.hpp"


namespace pr {

template <class T1, class T2>
pair<T1,T2> make_pair(T1 x, T2 y) {
    return pair<T1, T2>(x, y);
}

}

#endif // MAKE_PAIR_HPP
