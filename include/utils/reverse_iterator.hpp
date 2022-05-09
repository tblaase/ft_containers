/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:26:30 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/09 15:59:42 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include <iterator>

namespace ft
{
	template <class Iter>
	class reverse_iterator
		: public iterator <	typename iterator_traits<Iter>::iterator_category,
							typename iterator_traits<Iter>::value_type,
							typename iterator_traits<Iter>::difference_type,
							typename iterator_traits<Iter>::pointer,
							typename iterator_traits<Iter>::reference >
	{
		public:
			typedef Iter															iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;
			typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		protected:
			iterator_type	_current;
		public:
			// default constructor
			reverse_iterator(): _current()
			{}

			// constructor
			explicit reverse_iterator(iterator_type x): _current(x)
			{}

			// copy costructor
			template <class It>
				reverse_iterator(const reverse_iterator<It> &src)
				{
					*this = src;
				}

			// destructor
			~reverse_iterator()
			{}

			// assigation operator overload
			template <class It>
				reverse_iterator	&operator=(const reverse_iterator<It>& other)
				{
					this->_current = other.base();
					return (*this);
				}

		// ##### Member functions for Reverse Iterators #####
			iterator_type	base() const
			{
				return (this->_current);
			}

			reference	operator*() const
			{
				iterator_type	tmp = this->_current;
				return (*--tmp);
			}

			pointer	operator->() const
			{
				return (&(this->operator*()));
			}

			reverse_iterator	&operator++()
			{
				--this->_current;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(*this);

				--this->_current;
				return (tmp);
			}

			reverse_iterator	&operator--()
			{
				++this->_current;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);

				++this->_current;
				return (tmp);
			}

			reverse_iterator	operator+(difference_type n)
			{
				return (reverse_iterator(this->_current - n));
			}

			reverse_iterator	&operator+=(difference_type n)
			{
				this->_current -= n;
				return (*this);
			}

			reverse_iterator	operator-(difference_type n)
			{
				return (reverse_iterator(this->_current + n));
			}

			reverse_iterator	&operator-=(difference_type n)
			{
				this->_current += n;
				return (*this);
			}

			reference	operator[](difference_type n)
			{
				return *(*this + n);
			}
	};

	// ##### Non member functions of the reverse iterator #####
	template <class Iter1, class Iter2>
		bool operator==(const ft::reverse_iterator<Iter1> &x, const ft::reverse_iterator<Iter2> &y)
		{
			return (x.base() == y.base());
		}

	template <class Iter1, class Iter2>
		bool operator<(const ft::reverse_iterator<Iter1> &x, const ft::reverse_iterator<Iter2> &y)
		{
			return (x.base() > y.base());
		}

	template <class Iter1, class Iter2>
		bool operator!=(const ft::reverse_iterator<Iter1> &x, const ft::reverse_iterator<Iter2> &y)
		{
			return (x.base() != y.base());
		}

	template <class Iter1, class Iter2>
		bool operator>(const ft::reverse_iterator<Iter1> &x, const ft::reverse_iterator<Iter2> &y)
		{
			return (x.base() < y.base());
		}

	template <class Iter1, class Iter2>
		bool operator>=(const ft::reverse_iterator<Iter1> &x, const ft::reverse_iterator<Iter2> &y)
		{
			return (x.base() <= y.base());
		}

	template <class Iter1, class Iter2>
		bool operator<=(const ft::reverse_iterator<Iter1> &x, const ft::reverse_iterator<Iter2> &y)
		{
			return (x.base() >= y.base());
		}

	template <class Iter1, class Iter2>
		typename ft::reverse_iterator<Iter1>::difference_type operator-(const ft::reverse_iterator<Iter1> &x, const ft::reverse_iterator<Iter2> &y)
		{
			return (y.base() - x.base());
		}

	template <class Iter1>
		ft::reverse_iterator<Iter1> operator+(typename ft::reverse_iterator<Iter1>::difference_type n, const ft::reverse_iterator<Iter1> &x)
		{
			return (ft::reverse_iterator<Iter1>(x.base() - n));
		}
}
