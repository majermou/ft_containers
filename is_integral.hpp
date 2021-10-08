/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:21:44 by majermou          #+#    #+#             */
/*   Updated: 2021/10/08 17:16:09 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <iostream>

template<typename> struct is_integral: public std::false_type {};
template<> struct is_integral<bool>: public std::true_type {};
template<> struct is_integral<char>: public std::true_type {};
template<> struct is_integral<char32_t>: public std::true_type {};
template<> struct is_integral<char16_t>: public std::true_type {};
template<> struct is_integral<wchar_t>: public std::true_type {};
template<> struct is_integral<signed char>: public std::true_type {};
template<> struct is_integral<short int>: public std::true_type {};
template<> struct is_integral<int>: public std::true_type {};
template<> struct is_integral<long int>: public std::true_type {};
template<> struct is_integral<long long int>: public std::true_type {};
template<> struct is_integral<unsigned char>: public std::true_type {};
template<> struct is_integral<unsigned short int>: public std::true_type {};
template<> struct is_integral<unsigned int>: public std::true_type {};
template<> struct is_integral<unsigned long int>: public std::true_type {};
template<> struct is_integral<unsigned long long int>: public std::true_type {};

#endif // IS_INTEGRAL_HPP
