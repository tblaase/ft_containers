/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_bidirectional_iterator.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 09:47:26 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/19 15:30:47 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{
	// template <class Node>
	// 	class rev_bidirectional_iterator
	// 	{
	// 		public:
	// 			typedef T												iterator_type;
	// 			typedef typename ft::bidirectional_iterator_tag			iterator_category;
	// 			typedef typename iterator_traits<T>::difference_type	difference_type;
	// 			typedef typename iterator_traits<T>::value_type			value_type;
	// 			typedef typename iterator_traits<T>::reference			reference;
	// 			typedef typename iterator_traits<T>::pointer			pointer;
	// 			typedef NodePtr											node_pointer;
	template <class Node>
		class rev_bidirectional_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
		{
			public:
			typedef Node*									iterator_type;
			typedef Node									iterator_value;
			typedef typename iterator_value::value_type		value_type;
			typedef value_type&								reference;
			typedef value_type*								pointer;
			private:
				iterator_type	_it;

				iterator_type	_getSuccessor(iterator_type node)
				{
					iterator_type	res;

					if (!node)
						return (NULL);
					if (node->right)
					{
						res = node->right;
						while (res->left)
							res = res->left;
					}
					else
					{
						res = node->parent;
						while (res)
						{
							node = res;
							res = res->parent;
						}
					}
					return(res);
				}

				iterator_type	_getPredecessor(iterator_type node)
				{
					iterator_type	res;

					if (!node)
						return (NULL);
					if (node->left)
					{
						res = node->left;
						while (res->right)
							res = res->right;
					}
					else
					{
						res = node->parent;
						while (res)
						{
							node = res;
							res = res->parent;
						}
					}
					return(res);
				}

			public:
				rev_bidirectional_iterator() : _it()
				{};

				explicit	rev_bidirectional_iterator(iterator_type _p) : _it(_p)
				{};

				rev_bidirectional_iterator(const rev_bidirectional_iterator& src)
				{
					*this = src;
				}

				template <class Iter>
					rev_bidirectional_iterator& operator=(const Iter& src)
					{
						if (this != src)
							this->_it = src.base();
						return (*this);
					}

				// template <class Iter>
				// 	rev_bidirectional_iterator(const rev_bidirectional_iterator<Iter, node_pointer>& _i) : _it(_i.base())
				// 	{};

				iterator_type	base() const
				{
					return this->_it;
				};

				reference	operator*() const
				{
					return _getPredecessor(this->_it)->data;
				};

				rev_bidirectional_iterator&	operator++()
				{
					this->_it = _getPredecessor(this->_it);
					return (*this);
				};

				rev_bidirectional_iterator	operator++(int)
				{
					rev_bidirectional_iterator temp(*this); ++(*this);
					return (temp);
				};

				rev_bidirectional_iterator&	operator--()
				{
					this->_it = _getSuccessor(this->_it);
					return (*this);
				};

				rev_bidirectional_iterator	operator--(int)
				{
					rev_bidirectional_iterator temp(*this);
					--(*this);
					return (temp);
				};

				pointer			operator->() const
				{
					return (&(operator*()));
				};
		};

	template <class Node>
		bool	operator==(const rev_bidirectional_iterator<Node>& x, const rev_bidirectional_iterator<Node>& y)
		{
			return (x.base() == y.base());
		};

	template <class Node>
		bool	operator!=(const rev_bidirectional_iterator<Node>& x, const rev_bidirectional_iterator<Node>& y)
		{
			return (x.base() != y.base());
		};
}