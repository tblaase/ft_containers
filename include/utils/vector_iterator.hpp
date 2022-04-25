/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:24:38 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/24 13:29:43 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
	template<class Iter>
	class vector_iterator
	{
		public:
				typedef Iter												it_type;
				typedef typename ft::iterator_traits<it_type>::value_type	value_type;
				typedef typename ft::iterator_traits<it_type>::pointer		pointer;
				typedef typename ft::iterator_traits<it_type>::reference	reference;
				typedef typename ft::iterator_traits<it_type>::diff_type	diff_type;
				typedef typename ft::iterator_traits<it_type>::it_category	it_category;

		private:
				it_type _ptr;

		public:
				vector_iterator(): _ptr(NULL)
				{}
				vector_iterator(pointer ptr): _ptr(ptr)
				{}
				template<class It>
					vector_iterator(const vector_iterator<It> &src)
					{
						*this = src;
					}

				~vector_iterator()
				{};

				template<class It>
					vector_iterator&operator=(const vector_iterator<It> &src)
					{
						this->_ptr = src.base();

						return (*this);
					}

				pointer	base()const
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

				reference	operator[](diff_type diff) const
				{
					return (this->_ptr + diff);
				}

				vector_iterator	&operator++()
				{
					this->_ptr++;

					return (*this);
				}

				vector_iterator	&operator++(int)
				{
					vector_iterator tmp = *this;

					++(*this);

					return (tmp);
				}

				vector_iterator	&operator--()
				{
					this->_ptr--;

					return (*this);
				}

				vector_iterator	&operator--(int)
				{
					vector_iterator tmp = *this;

					--(*this);

					return (tmp);
				}

				vector_iterator	operator+(diff_type diff)// maybe const is needed here
				{
					return (vector_iterator(_ptr + diff));
				}

				vector_iterator	&operato+-=(diff_type diff)
				{
					this->_ptr += diff;

					return (*this);
				}

				vector_iterator	operator-(diff_type diff)// maybe const is needed here
				{
					return (vector_iterator(_ptr - diff));
				}

				vector_iterator	&operator-=(diff_type diff)
				{
					this->_ptr -= diff;

					return (*this);
				}
	};

	// non-member functions
	template<class iter1, class iter2>
		typename ft::vector_iterator<iter1>::diff_type	operator+(const ft::vector_iterator<iter1> &left, const ft::vector_iterator<iter2> &right)
		{
			return (left.base() + right.base());
		}

	template<class iter1, class iter2>
		typename ft::vector_iterator<iter1>::diff_type	operator-(const ft::vector_iterator<iter1> &left, const ft::vector_iterator<iter2> &right)
		{
			return (left.base() - right.base());
		}

	template<class iter>
		typename ft::vector_iterator<iter>::diff_type	operator+(ft::vector_iterator<iter> &iter1, typename ft::vector_iterator<iter>::diff_type diff) // maybe -= is needed as well
		{
			iter1 += diff;
			return (iter1);
		}

	template<class iter1, class iter2>
		bool	operator==(const ft::vector_iterator<iter1> &left, const ft::vector_iterator<iter2> &right)
		{
			return (left.base() == right.base());
		}

	template<class iter1, class iter2>
		bool	operator!=(const ft::vector_iterator<iter1> &left, const ft::vector_iterator<iter2> &right)
		{
			return (left.base() != right.base());
		}
	template<class iter1, class iter2>
		bool	operator<(const ft::vector_iterator<iter1> &left, const ft::vector_iterator<iter2> &right)
		{
			return (left.base() < right.base());
		}
	template<class iter1, class iter2>
		bool	operator>(const ft::vector_iterator<iter1> &left, const ft::vector_iterator<iter2> &right)
		{
			return (left.base() > right.base());
		}
	template<class iter1, class iter2>
		bool	operator<=(const ft::vector_iterator<iter1> &left, const ft::vector_iterator<iter2> &right)
		{
			return (left.base() <= right.base());
		}
	template<class iter1, class iter2>
		bool	operator>=(const ft::vector_iterator<iter1> &left, const ft::vector_iterator<iter2> &right)
		{
			return (left.base() >= right.base());
		}
}