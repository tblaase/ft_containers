/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_bidirectional_iterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:19:59 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/23 17:38:44 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"
// # include <iterator>

namespace ft
{
	template <class Iter>
	class reverse_iterator: public iterator <typename iterator_traits<Iter>::iterator_category,
											typename iterator_traits<Iter>::value_type,
											typename iterator_traits<Iter>::difference_type,
											typename iterator_traits<Iter>::pointer,
											typename iterator_traits<Iter>::reference>
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
					this->_it = src.base();
					return (*this);
				}

		// member functions
			iterator_type	base() const
			{
				return (this->_it);
			}

		// operator overloads
			pointer	operator->() const
			{
				return (&(this->operator*()));
			}

			reference	operator*() const
			{
				iterator_type	tmp = this->_it;
				return (*--tmp);
			}

			reverse_iterator&	operator++()
			{
				--this->_it;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(*this);
				--this->_it;
				return (tmp);
			}

			reverse_iterator&	operator--()
			{
				++this->_it;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);
				++this->_it;
				return (tmp);
			}
	};
// non member operator overloads
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
}
