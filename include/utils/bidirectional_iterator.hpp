/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:18:14 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/23 15:02:09 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"
namespace ft
{
// bidirectional iterator
	template < class Node>
	class bidirectional_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
	{
		public:
			typedef Node*								iterator_type;
			typedef Node								iterator_value;
			typedef typename iterator_value::value_type	value_type;
			typedef value_type&							reference;
			typedef value_type*							pointer;

		private:
			iterator_type	_ptr;

			iterator_type	_get_successor(iterator_type node)
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
					while (res && !node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}
			iterator_type	_get_predecessor(iterator_type node)
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
					while (res && node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}
		public:
			explicit bidirectional_iterator(iterator_type ptr = NULL): _ptr(ptr) { }
			bidirectional_iterator(const bidirectional_iterator& src)
			{
				*this = src;
			}
			~bidirectional_iterator() { }

			template<class Iter>
				bidirectional_iterator&	operator=(const Iter& src)
				{
					if (this != src)
						_ptr = src.base();
					return (*this);
				}

			iterator_type	base()
			{
				return (_ptr);
			}

			iterator_type	base() const
			{
				return (_ptr);
			}


			reference	operator*() const
			{
				return (_ptr->value);
			}

			pointer		operator->() const
			{
				return (&(_ptr->value));
			}


			bidirectional_iterator&	operator++()
			{
				_ptr = _get_successor(_ptr);
				return (*this);
			}

			bidirectional_iterator		operator++(int)
			{
				bidirectional_iterator	tmp(*this);
				++*this;
				return (tmp);
			}


			bidirectional_iterator&	operator--()
			{
				_ptr = _get_predecessor(_ptr);
				return (*this);
			}

			bidirectional_iterator		operator--(int)
			{
				bidirectional_iterator	tmp(*this);
				--*this;
				return (tmp);
			}


			bool	operator==(const bidirectional_iterator &x)
			{
				return (_ptr == x._ptr);
			}

			bool	operator!=(const bidirectional_iterator &x)
			{
				return (_ptr != x._ptr);
			}
	};

// const bidirectional iterator
	template < class Node>
	class const_bidirectional_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
	{
		public:
			typedef Node*										iterator_type;
			typedef Node										iterator_value;
			typedef const typename iterator_value::value_type	value_type;
			typedef value_type&									reference;
			typedef value_type*									pointer;

		private:
			iterator_type	_ptr;

			iterator_type	_get_successor(iterator_type node)
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
					while (res && !node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}

			iterator_type	_get_predecessor(iterator_type node)
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
					while (res && node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}

		public:
			explicit const_bidirectional_iterator(iterator_type ptr = NULL): _ptr(ptr) { }
			~const_bidirectional_iterator() { }

			template<class Iter>
				const_bidirectional_iterator(const Iter& src)
				{
					*this = src;
				}

			template<class Iter>
				const_bidirectional_iterator&	operator=(const Iter& src)
				{
					_ptr = src.base();
					return (*this);
				}

			iterator_type	base()
			{
				return (_ptr);
			}

			iterator_type	base() const
			{
				return (_ptr);
			}


			reference	operator*() const
			{
				return (_ptr->value);
			}

			pointer		operator->() const
			{
				return (&(_ptr->value));
			}


			const_bidirectional_iterator&	operator++()
			{
				_ptr = _get_predecessor(_ptr);
				return (*this);
			}

			const_bidirectional_iterator	operator++(int)
			{
				const_bidirectional_iterator	tmp(*this);
				--*this;
				return (tmp);
			}


			const_bidirectional_iterator&	operator--()
			{
				_ptr = _get_successor(_ptr);
				return (*this);
			}

			const_bidirectional_iterator	operator--(int)
			{
				const_bidirectional_iterator	tmp(*this);
				++*this;
				return (tmp);
			}


			bool	operator==(const const_bidirectional_iterator &x)
			{
				return (_ptr == x._ptr);
			}

			bool	operator!=(const const_bidirectional_iterator &x)
			{
				return (_ptr != x._ptr);
			}
	};
}
