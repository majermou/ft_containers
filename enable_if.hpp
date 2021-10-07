/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:21:48 by majermou          #+#    #+#             */
/*   Updated: 2021/10/07 18:36:18 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<bool Cond, class T = void> struct enable_if {};

template<class T> struct enable_if<true, T> {
    typedef T type;
};