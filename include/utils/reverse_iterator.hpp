/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:19:59 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/23 15:15:08 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"
// # include <iterator>

namespace ft
{
	template <class Iter>
	class reverse_iterator
		: public iterator < typename iterator_traits<Iter>::iterator_category,
							typename iterator_traits<Iter>::value_type,
							typename iterator_traits<Iter>::difference_type,
							typename iterator_traits<Iter>::pointer,
							typename iterator_traits<Iter>::reference >
	{
	// member types
		public:
			typedef Iter															iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;
			typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		protected:
			iterator_type	_it;
	// member functions
		public:
		// default constructor
			reverse_iterator(): _it() {}
		// constructor
			explicit reverse_iterator(iterator_type it): _it(it) {}
		// copy constructor
			template <class It>
				reverse_iterator(const reverse_iterator<It>& src)
				{
					*this = src;
				}

		// destructor
			~reverse_iterator() {}

		// assignations operator overload
			template <class It>
				reverse_iterator&	operator=(const reverse_iterator<It>& src)
				{
					_it = src.base();
					return (*this);
				}

		// member functions
			iterator_type	base() const
			{
				return (_it);
			}
		// operator overloads
			pointer	operator->() const
			{
				return (&(this->operator*()));
			}
			reference	operator*() const
			{
				iterator_type	tmp = _it;
				return (*--tmp);
			}
			reference	operator[](difference_type n) const
			{
				return *(*this + n);
			}
			reverse_iterator&	operator++()
			{
				--_it;
				return (*this);
			}
			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(*this);

				--_it;
				return (tmp);
			}
			reverse_iterator&	operator--()
			{
				++_it;
				return (*this);
			}
			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);
				++_it;
				return (tmp);
			}
			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(_it - n));
			}
			reverse_iterator	operator-(difference_type n) const
			{
				return (reverse_iterator(_it + n));
			}
			reverse_iterator&	operator+=(difference_type n)
			{
				_it -= n;
				return (*this);
			}
			reverse_iterator&	operator-=(difference_type n)
			{
				_it += n;
				return (*this);
			}
	};
// non member operator overloads
	template <class iter1, class iter2>
		typename ft::reverse_iterator<iter1>::difference_type
		operator-(const ft::reverse_iterator<iter1>& x, const ft::reverse_iterator<iter2>& y)
		{
			return (y.base() - x.base());
		}
	template <class iter>
		ft::reverse_iterator<iter> operator+(typename ft::reverse_iterator<iter>::difference_type n, const ft::reverse_iterator<iter>& x)
		{
			return (ft::reverse_iterator<iter>(x.base() - n));
		}
	template <class iter1, class iter2>
		bool operator==(const ft::reverse_iterator<iter1>& x, const ft::reverse_iterator<iter2>& y)
		{
			return (x.base() == y.base());
		}
	template <class iter1, class iter2>
		bool operator!=(const ft::reverse_iterator<iter1>& x, const ft::reverse_iterator<iter2>& y)
		{
			return (x.base() != y.base());
		}
	template <class iter1, class iter2>
		bool operator<(const ft::reverse_iterator<iter1>& x, const ft::reverse_iterator<iter2>& y)
		{
			return (x.base() > y.base());
		}
	template <class iter1, class iter2>
		bool operator>(const ft::reverse_iterator<iter1>& x, const ft::reverse_iterator<iter2>& y)
		{
			return (x.base() < y.base());
		}
	template <class iter1, class iter2>
		bool operator>=(const ft::reverse_iterator<iter1>& x, const ft::reverse_iterator<iter2>& y)
		{
			return (x.base() <= y.base());
		}
	template <class iter1, class iter2>
		bool operator<=(const ft::reverse_iterator<iter1>& x, const ft::reverse_iterator<iter2>& y)
		{
			return (x.base() >= y.base());
		}
}
