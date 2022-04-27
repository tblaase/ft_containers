/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:19:31 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/26 16:44:15 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <limits>
#include <sstream>
#include <typeinfo>
#include <iostream>

namespace ft
{
	template<class T1, class T2>
		struct pair
		{
			public:
					typedef T1 first_type;
					typedef T2 second_type;

					first_type first;
					second_type second;

					// default pair constructor
					pair(): first(), second()
					{}

					// pair copy constructor
					template<class U, class V>
						pair(const pair<U, V> &src): first(src.first), second(src.second)
						{}

					// pair constructor
					pair(const first_type &a, second_type &b): first(a), second(b)
					{}

					// overload for = for pairs
					pair &operator=(const pair &src)
					{
						if (*this == src)
							return (*this);
						this->first = src.first;
						this->second = src.second;
						return (*this);
					}
		};

	// Overload opperators for pairs
	template<class T1, class T2>
		bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{
			return (lhs.first == rhs.first && lhs.second == rhs.second);
		}

	template<class T1, class T2>
		bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{
			return !(lhs == rhs);
		}

	template<class T1, class T2>
		bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{
			return (lhs.first < rhs.first || (!(lhs.first > rhs.first) && lhs.second < rhs.second));
		}

	template<class T1, class T2>
		bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{
			return (lhs > rhs);
		}

	template<class T1, class T2>
		bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{
			return !(lhs > rhs);
		}

	template<class T1, class T2>
		bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{
			return !(lhs < rhs);
		}

	// make_pair
	template<class T1, class T2>
		ft::pair<T1, T2> make_pair(T1 a, T2 b)
		{
			return (ft::pair<T1, T2>(a, b));
		}

	// enable _if
	template<bool condition, class T = void>
		struct enable_if
		{};

	template<class T>
		struct enable_if<true, T>
		{
			typedef T type;
		};

	// is_integral for all the integral types, only used to differentiate between constructors
	template <class T, T v>
		struct integral_constant
		{
			static const T	value = v;
			typedef T		value_type;
		};

	typedef struct integral_constant<bool, true>	true_type;
	typedef struct integral_constant<bool, false>	false_type;

	// bool false
	template <class T>
		struct is_integral: public false_type
		{};
	// bool true
	template <>
		struct is_integral<bool>: public true_type
		{};
	// char
	template <>
		struct is_integral<char>: public true_type
		{};
	// wchar_t
	template <>
		struct is_integral<wchar_t>: public true_type
		{};
	// signed char
	template <>
		struct is_integral<signed char>: public true_type
		{};
	// short int
	template <>
		struct is_integral<short int>: public true_type
		{};
	// int
	template <>
		struct is_integral<int>: public true_type
		{};
	// long int
	template <>
		struct is_integral<long int>: public true_type
		{};
	// log long int
	template <>
		struct is_integral<long long int>: public true_type
		{};
	// unsigned char
	template <>
		struct is_integral<unsigned char>: public true_type
		{};
	// unsigned short int
	template <>
		struct is_integral<unsigned short int>: public true_type
		{};
	// unsigned int
	template <>
		struct is_integral<unsigned int>: public true_type
		{};
	// unsigned long int
	template <>
		struct is_integral<unsigned long int>: public true_type
		{};
	// unsigned long long int
	template <>
		struct is_integral<unsigned long long int>: public true_type
		{};
}
