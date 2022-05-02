/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:24:38 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/01 01:22:40 by tblaase          ###   ########.fr       */
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
				random_access_iterator(): _ptr(NULL)
				{}
				random_access_iterator(pointer ptr): _ptr(ptr)
				{}
				template<class It>
					random_access_iterator(const random_access_iterator<It> &src)
					{
						*this = src;
					}

				~random_access_iterator()
				{};

				template<class It>
					random_access_iterator&operator=(const random_access_iterator<It> &src)
					{
						this->_ptr = src.base();

						return (*this);
					}

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
					this->_ptr++;

					return (*this);
				}

				random_access_iterator	&operator++(int)
				{
					static random_access_iterator tmp = *this;

					++(*this);

					return (tmp);
				}

				random_access_iterator	&operator--()
				{
					this->_ptr--;

					return (*this);
				}

				random_access_iterator	&operator--(int)
				{
					static random_access_iterator tmp = *this;

					--(*this);

					return (tmp);
				}

				random_access_iterator	operator+(difference_type diff)// maybe const is needed here
				{
					return (random_access_iterator(_ptr + diff));
				}

				random_access_iterator	&operator+=(difference_type diff)
				{
					this->_ptr += diff;

					return (*this);
				}

				random_access_iterator	operator-(difference_type diff)// maybe const is needed here
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
		typename ft::random_access_iterator<iter1>::difference_type	operator+(const ft::random_access_iterator<iter1> &lhs, const ft::random_access_iterator<iter2> &rhs)
		{
			return (lhs.base() + rhs.base());
		}

	template<class iter1, class iter2>
		typename ft::random_access_iterator<iter1>::difference_type	operator-(const ft::random_access_iterator<iter1> &lhs, const ft::random_access_iterator<iter2> &rhs)
		{
			return (lhs.base() - rhs.base());
		}

	template<class iter>
		typename ft::random_access_iterator<iter>::difference_type	operator+(ft::random_access_iterator<iter> &iter1, typename ft::random_access_iterator<iter>::difference_type diff) // maybe -= is needed as well
		{
			iter1 += diff;
			return (iter1);
		}

	template<class iter1, class iter2>
		bool	operator==(const ft::random_access_iterator<iter1> &lhs, const ft::random_access_iterator<iter2> &rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template<class iter1, class iter2>
		bool	operator!=(const ft::random_access_iterator<iter1> &lhs, const ft::random_access_iterator<iter2> &rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template<class iter1, class iter2>
		bool	operator<(const ft::random_access_iterator<iter1> &lhs, const ft::random_access_iterator<iter2> &rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template<class iter1, class iter2>
		bool	operator>(const ft::random_access_iterator<iter1> &lhs, const ft::random_access_iterator<iter2> &rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template<class iter1, class iter2>
		bool	operator<=(const ft::random_access_iterator<iter1> &lhs, const ft::random_access_iterator<iter2> &rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template<class iter1, class iter2>
		bool	operator>=(const ft::random_access_iterator<iter1> &lhs, const ft::random_access_iterator<iter2> &rhs)
		{
			return (lhs.base() >= rhs.base());
		}
}
