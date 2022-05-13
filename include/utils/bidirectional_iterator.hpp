/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:18:14 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/13 11:24:57 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"
namespace ft
{
	template <class T, class NodePtr>
		class bidirectional_iterator
		{
			public:
				typedef T												iterator_type;
				typedef typename ft::bidirectional_iterator_tag			iterator_category;
				typedef typename iterator_traits<T>::difference_type	difference_type;
				typedef typename iterator_traits<T>::value_type			value_type;
				typedef typename iterator_traits<T>::reference			reference;
				typedef typename iterator_traits<T>::pointer			pointer;
				typedef NodePtr											node_pointer;
			private:
				node_pointer	_it;

			public:
				bidirectional_iterator() : _it()
				{};

				explicit	bidirectional_iterator(node_pointer _p) : _it(_p)
				{};

				template <class Iter>
					bidirectional_iterator(const bidirectional_iterator<Iter, node_pointer>& _i) : _it(_i.base())
					{};

				node_pointer	base() const
				{
					return this->_it;
				};

				reference	operator*() const
				{
					return this->_it->data;
				};

				bidirectional_iterator&	operator++()
				{
					this->_it = _getSuccessor(this->_it);
					return (*this);
				};

				bidirectional_iterator	operator++(int)
				{
					bidirectional_iterator temp(*this);
					++(*this);
					return (temp);
				};

				bidirectional_iterator&	operator--()
				{
					this->_it = _getPredecessor(this->_it);
					return (*this);
				};

				bidirectional_iterator	operator--(int)
				{
					bidirectional_iterator temp(*this);
					--(*this);
					return (temp);
				};

				pointer	operator->() const
				{
					return (&(operator*()));
				};
		};

	template <class Iterator, class NodePtr>
		bool	operator==(const bidirectional_iterator<Iterator, NodePtr>& x, const bidirectional_iterator<Iterator, NodePtr>& y)
		{
			return (x.base() == y.base());
		};

	template <class Iterator, class NodePtr>
		bool	operator!=(const bidirectional_iterator<Iterator, NodePtr>& x, const bidirectional_iterator<Iterator, NodePtr>& y)
		{
			return (x.base() != y.base());
		};
}