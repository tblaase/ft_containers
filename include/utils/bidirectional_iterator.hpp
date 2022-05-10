/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:18:14 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/10 18:11:11 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
// #include "utils/avl_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare, typename Node, bool B>
		class bidirectional_iterator
		{
			public:
				typedef Key										key_type;
				typedef Compare									key_compare;
				typedef T										mapped_type;

				typedef ft::pair<const key_type, mapped_type>	value_type;
				typedef long int								difference_type;
				typedef size_t									size_type;

				typedef std::bidirectional_iterator_tag			iterator_category;
				typedef value_type&								reference; // check if const is needed
				typedef value_type*								pointer; // check if const needed
				typedef Node*									nodePtr;

			private:
				nodePtr			_node; // Pointer to a binary tree's node
				nodePtr			_lastElem; // Pointer to the dummy node of binary tree
				key_compare		_comp; // Comparison object used to sort the binary tree

			public:
					// default constructor
					bidirectional_iterator(): _node(NULL), _lastElem(NULL), _comp(comp)
					{}

					// constructor
					bidirectional_iterator(pointer ptr): _ptr(ptr)
					{}

					// copy constructor
					bidirectional_iterator(const bidirectional_iterator<Key, T, Compare, Node, false> &src): _node(NULL), _lastElem(NULL), _comp(comp)
					{
						*this = src;
					}

					// destructor
					~bidirectional_iterator()
					{};

					// assigation operator overload
					template<class It>
						bidirectional_iterator&operator=(const bidirectional_iterator<It> &src)
						{
							if (*this != src)
							{
								this->_node = src._node;
								this->_lastElem = src._lastElem;
								this->_comp = src._comp;
							}
							return (*this);
						}

				// ##### Member functions #####
					pointer	base() const
					{
						return (this->_node);
					}

					pointer	operator->()
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

					// reference	operator[](difference_type diff) const
					// {
					// 	return (*(this->_ptr + diff));
					// }

					bidirectional_iterator	&operator++()
					{
						++this->_ptr;
						return (*this);
					}

					bidirectional_iterator	operator++(int)
					{
						bidirectional_iterator tmp = *this;

						++(*this);
						return (tmp);
					}

					bidirectional_iterator	&operator--()
					{
						--this->_ptr;
						return (*this);
					}

					bidirectional_iterator	operator--(int)
					{
						bidirectional_iterator tmp = *this;

						--(*this);
						return (tmp);
					}

					bidirectional_iterator	operator+(const int &diff) const
					{
						bidirectional_iterator it = *this;
						for (size_t i = 0; i < diff; ++i)
							++it;
						return (it);
					}

					// bidirectional_iterator	&operator+=(difference_type diff)
					// {
					// 	this->_ptr += diff;
					// 	return (*this);
					// }

					bidirectional_iterator	operator-(const int &diff) const
					{
						bidirectional_iterator it = *this;
						for (size_t i = 0; i < diff; ++i)
							--it;
						return (it);
					}

					// bidirectional_iterator	&operator-=(difference_type diff)
					// {
					// 	this->_ptr -= diff;
					// 	return (*this);
					// }
		};

	// non-member functions
	// template<class iter1, class iter2>
	// 	typename ft::bidirectional_iterator<iter1>::difference_type	operator+(const ft::bidirectional_iterator<iter1> &x, const ft::bidirectional_iterator<iter2> &y)
	// 	{
	// 		return (x.base() + y.base());
	// 	}

	// template<class iter1, class iter2>
	// 	typename ft::bidirectional_iterator<iter1>::difference_type	operator-(const ft::bidirectional_iterator<iter1> &x, const ft::bidirectional_iterator<iter2> &y)
	// 	{
	// 		return (x.base() - y.base());
	// 	}

	// template<class iter>
	// 	ft::bidirectional_iterator<iter> operator+(typename ft::bidirectional_iterator<iter>::difference_type diff, ft::bidirectional_iterator<iter> x)
	// 	{
	// 		x += diff;
	// 		return (x);
	// 	}

	template<class iter1, class iter2>
		bool	operator==(const ft::bidirectional_iterator<iter1> &x, const ft::bidirectional_iterator<iter2> &y)
		{
			return (x.base() == y.base());
		}

	template<class iter1, class iter2>
		bool	operator!=(const ft::bidirectional_iterator<iter1> &x, const ft::bidirectional_iterator<iter2> &y)
		{
			return (x.base() != y.base());
		}

	// template<class iter1, class iter2>
	// 	bool	operator<(const ft::bidirectional_iterator<iter1> &x, const ft::bidirectional_iterator<iter2> &y)
	// 	{
	// 		return (x.base() < y.base());
	// 	}

	// template<class iter1, class iter2>
	// 	bool	operator>(const ft::bidirectional_iterator<iter1> &x, const ft::bidirectional_iterator<iter2> &y)
	// 	{
	// 		return (x.base() > y.base());
	// 	}

	// template<class iter1, class iter2>
	// 	bool	operator<=(const ft::bidirectional_iterator<iter1> &x, const ft::bidirectional_iterator<iter2> &y)
	// 	{
	// 		return (x.base() <= y.base());
	// 	}

	// template<class iter1, class iter2>
	// 	bool	operator>=(const ft::bidirectional_iterator<iter1> &x, const ft::bidirectional_iterator<iter2> &y)
	// 	{
	// 		return (x.base() >= y.base());
	// 	}
}
