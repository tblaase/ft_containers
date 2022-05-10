/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:24:38 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/10 09:22:09 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
	template<class Iter>
	class random_access_iterator
	{
		public:
				typedef Iter															iterator_type;
				typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
				typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
				typedef typename ft::iterator_traits<iterator_type>::reference			reference;
				typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
				typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;

		private:
				iterator_type _ptr;

		public:
				// default constructor
				random_access_iterator(): _ptr(NULL)
				{}

				// constructor
				random_access_iterator(pointer ptr): _ptr(ptr)
				{}

				// copy constructor
				template<class It>
					random_access_iterator(const random_access_iterator<It> &src): _ptr(NULL)
					{
						*this = src;
					}

				// destructor
				~random_access_iterator()
				{};

				// assigation operator overload
				template<class It>
					random_access_iterator&operator=(const random_access_iterator<It> &src)
					{
						this->_ptr = src.base();
						return (*this);
					}

			// ##### Member functions for RandomAccessIterators #####
				pointer	base() const
				{
					return (this->_ptr);
				}

				pointer	operator->() const
				{
					return (this->_ptr);
				}

				reference	operator*() const
				{
					return (*this->_ptr);
				}

				reference	operator[](difference_type diff) const
				{
					return (*(this->_ptr + diff));
				}

				random_access_iterator	&operator++()
				{
					++this->_ptr;
					return (*this);
				}

				random_access_iterator	operator++(int)
				{
					random_access_iterator tmp = *this;

					++(*this);
					return (tmp);
				}

				random_access_iterator	&operator--()
				{
					--this->_ptr;
					return (*this);
				}

				random_access_iterator	operator--(int)
				{
					random_access_iterator tmp = *this;

					--(*this);
					return (tmp);
				}

				random_access_iterator	operator+(difference_type diff)
				{
					return (random_access_iterator(_ptr + diff));
				}

				random_access_iterator	&operator+=(difference_type diff)
				{
					this->_ptr += diff;
					return (*this);
				}

				random_access_iterator	operator-(difference_type diff)
				{
					return (random_access_iterator(_ptr - diff));
				}

				random_access_iterator	&operator-=(difference_type diff)
				{
					this->_ptr -= diff;
					return (*this);
				}
	};

	// non-member functions
	template<class iter1, class iter2>
		typename ft::random_access_iterator<iter1>::difference_type	operator+(const ft::random_access_iterator<iter1> &x, const ft::random_access_iterator<iter2> &y)
		{
			return (x.base() + y.base());
		}

	template<class iter1, class iter2>
		typename ft::random_access_iterator<iter1>::difference_type	operator-(const ft::random_access_iterator<iter1> &x, const ft::random_access_iterator<iter2> &y)
		{
			return (x.base() - y.base());
		}

	template<class iter>
		ft::random_access_iterator<iter> operator+(typename ft::random_access_iterator<iter>::difference_type diff, ft::random_access_iterator<iter> x)
		{
			x += diff;
			return (x);
		}

	template<class iter1, class iter2>
		bool	operator==(const ft::random_access_iterator<iter1> &x, const ft::random_access_iterator<iter2> &y)
		{
			return (x.base() == y.base());
		}

	template<class iter1, class iter2>
		bool	operator!=(const ft::random_access_iterator<iter1> &x, const ft::random_access_iterator<iter2> &y)
		{
			return (x.base() != y.base());
		}

	template<class iter1, class iter2>
		bool	operator<(const ft::random_access_iterator<iter1> &x, const ft::random_access_iterator<iter2> &y)
		{
			return (x.base() < y.base());
		}

	template<class iter1, class iter2>
		bool	operator>(const ft::random_access_iterator<iter1> &x, const ft::random_access_iterator<iter2> &y)
		{
			return (x.base() > y.base());
		}

	template<class iter1, class iter2>
		bool	operator<=(const ft::random_access_iterator<iter1> &x, const ft::random_access_iterator<iter2> &y)
		{
			return (x.base() <= y.base());
		}

	template<class iter1, class iter2>
		bool	operator>=(const ft::random_access_iterator<iter1> &x, const ft::random_access_iterator<iter2> &y)
		{
			return (x.base() >= y.base());
		}
}
