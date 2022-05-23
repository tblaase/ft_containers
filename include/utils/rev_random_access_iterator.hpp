/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_random_access_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:26:30 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/09 15:59:42 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
// #include <iterator>

namespace ft
{
	template <class Iter>
	class rev_random_access_iterator: public iterator <typename iterator_traits<Iter>::iterator_category,
														typename iterator_traits<Iter>::value_type,
														typename iterator_traits<Iter>::difference_type,
														typename iterator_traits<Iter>::pointer,
														typename iterator_traits<Iter>::reference>
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
			rev_random_access_iterator(): _current()
			{}

			// constructor
			explicit rev_random_access_iterator(iterator_type x): _current(x)
			{}

			// copy costructor
			template <class It>
				rev_random_access_iterator(const rev_random_access_iterator<It> &src)
				{
					*this = src;
				}

			// destructor
			~rev_random_access_iterator()
			{}

			// assigation operator overload
			template <class It>
				rev_random_access_iterator	&operator=(const rev_random_access_iterator<It>& src)
				{
					this->_current = src.base();
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

			rev_random_access_iterator	&operator++()
			{
				--this->_current;
				return (*this);
			}

			rev_random_access_iterator	operator++(int)
			{
				rev_random_access_iterator	tmp(*this);

				--this->_current;
				return (tmp);
			}

			rev_random_access_iterator	&operator--()
			{
				++this->_current;
				return (*this);
			}

			rev_random_access_iterator	operator--(int)
			{
				rev_random_access_iterator	tmp(*this);

				++this->_current;
				return (tmp);
			}

			rev_random_access_iterator	operator+(difference_type n)
			{
				return (rev_random_access_iterator(this->_current - n));
			}

			rev_random_access_iterator	&operator+=(difference_type n)
			{
				this->_current -= n;
				return (*this);
			}

			rev_random_access_iterator	operator-(difference_type n)
			{
				return (rev_random_access_iterator(this->_current + n));
			}

			rev_random_access_iterator	&operator-=(difference_type n)
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
		bool operator==(const ft::rev_random_access_iterator<Iter1> &x, const ft::rev_random_access_iterator<Iter2> &y)
		{
			return (x.base() == y.base());
		}

	template <class Iter1, class Iter2>
		bool operator<(const ft::rev_random_access_iterator<Iter1> &x, const ft::rev_random_access_iterator<Iter2> &y)
		{
			return (x.base() > y.base());
		}

	template <class Iter1, class Iter2>
		bool operator!=(const ft::rev_random_access_iterator<Iter1> &x, const ft::rev_random_access_iterator<Iter2> &y)
		{
			return (x.base() != y.base());
		}

	template <class Iter1, class Iter2>
		bool operator>(const ft::rev_random_access_iterator<Iter1> &x, const ft::rev_random_access_iterator<Iter2> &y)
		{
			return (x.base() < y.base());
		}

	template <class Iter1, class Iter2>
		bool operator>=(const ft::rev_random_access_iterator<Iter1> &x, const ft::rev_random_access_iterator<Iter2> &y)
		{
			return (x.base() <= y.base());
		}

	template <class Iter1, class Iter2>
		bool operator<=(const ft::rev_random_access_iterator<Iter1> &x, const ft::rev_random_access_iterator<Iter2> &y)
		{
			return (x.base() >= y.base());
		}

	template <class Iter1, class Iter2>
		typename ft::rev_random_access_iterator<Iter1>::difference_type operator-(const ft::rev_random_access_iterator<Iter1> &x, const ft::rev_random_access_iterator<Iter2> &y)
		{
			return (y.base() - x.base());
		}

	template <class Iter1>
		ft::rev_random_access_iterator<Iter1> operator+(typename ft::rev_random_access_iterator<Iter1>::difference_type n, const ft::rev_random_access_iterator<Iter1> &x)
		{
			return (ft::rev_random_access_iterator<Iter1>(x.base() - n));
		}
}
