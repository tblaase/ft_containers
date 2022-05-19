/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:18:14 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/19 15:30:49 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"
namespace ft
{
	template <class Node>
		class bidirectional_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
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
				explicit	bidirectional_iterator(iterator_type _p = NULL) : _it(_p)
				{};

				bidirectional_iterator(const bidirectional_iterator& src)
				{
					*this = src;
				}

				template <class Iter>
					bidirectional_iterator& operator=(const Iter& src)
					{
						if (this != src)
							this->_it = src.base();
						return (*this);
					}

				iterator_type	base() const
				{
					return (this->_it);
				}

				reference	operator*() const
				{
					return (this->_it->data);
				}

				bidirectional_iterator&	operator++()
				{
					this->_it = _getSuccessor(this->_it);
					return (*this);
				}

				bidirectional_iterator	operator++(int)
				{
					bidirectional_iterator temp(*this);
					++(*this);
					return (temp);
				}

				bidirectional_iterator&	operator--()
				{
					this->_it = _getPredecessor(this->_it);
					return (*this);
				}

				bidirectional_iterator	operator--(int)
				{
					bidirectional_iterator temp(*this);
					--(*this);
					return (temp);
				}

				pointer	operator->() const
				{
					return (&(operator*()));
				}
		};

	template <class Node>
		bool	operator==(const bidirectional_iterator<Node>& x, const bidirectional_iterator<Node>& y)
		{
			return (x.base() == y.base());
		};

	template <class Node>
		bool	operator!=(const bidirectional_iterator<Node>& x, const bidirectional_iterator<Node>& y)
		{
			return (x.base() != y.base());
		};
}