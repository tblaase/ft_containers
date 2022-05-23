/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:46:26 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/23 17:05:33 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
		class stack
		{
			// typedefs
			public:
				typedef Container									container_type;
				typedef typename container_type::value_type			value_type;
				typedef typename container_type::reference			reference;
				typedef typename container_type::const_reference	const_reference;
				typedef typename container_type::size_type			size_type;

			// protected attributes
			protected:
				container_type	_c;

			public:
				// constructor
				explicit stack(const container_type& c = container_type()): _c(c) {}

				// destructor
				~stack()
				{
					this->_c.clear();
				}

				// Member functions
				bool	empty() const
				{
					return (this->_c.empty());
				}

				size_type	size() const
				{
					return (this->_c.size());
				}

				reference	top()
				{
					return (this->_c.back());
				}

				const_reference	top() const
				{
					return (this->_c.back());
				}

				void	push(const value_type& x)
				{
					this->_c.push_back(x);
				}
				void	pop()
				{
					this->_c.pop_back();
				}

				// friend declaration
				template<class FT, class FriendContainer>
					friend bool	operator==(const ft::stack<FT,FriendContainer> &x, const ft::stack<FT,FriendContainer> &y);

				template<class FT, class FriendContainer>
					friend bool	operator!=(const ft::stack<FT,FriendContainer> &x, const ft::stack<FT,FriendContainer> &y);

				template<class FT, class FriendContainer>
					friend bool	operator<(const ft::stack<FT,FriendContainer> &x, const ft::stack<FT,FriendContainer> &y);

				template<class FT, class FriendContainer>
					friend bool	operator<=(const ft::stack<FT,FriendContainer> &x, const ft::stack<FT,FriendContainer> &y);

				template<class FT, class FriendContainer>
					friend bool	operator>(const ft::stack<FT,FriendContainer> &x, const ft::stack<FT,FriendContainer> &y);

				template<class FT, class FriendContainer>
					friend bool	operator>=(const ft::stack<FT,FriendContainer> &x, const ft::stack<FT,FriendContainer> &y);
};

	// non-member functions
	template <class T, class Container>
		bool	operator==(const stack<T, Container>& x, const stack<T, Container>& y)
		{
			return (x._c == y._c);
		}

	template <class T, class Container>
		bool	operator< (const stack<T, Container>& x, const stack<T, Container>& y)
		{
			return (x._c < y._c);
		}

	template <class T, class Container>
		bool	operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
		{
			return (x._c != y._c);
		}

	template <class T, class Container>
		bool	operator> (const stack<T, Container>& x, const stack<T, Container>& y)
		{
			return (x._c > y._c);
		}

	template <class T, class Container>
		bool	operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
		{
			return (x._c >= y._c);
		}

	template <class T, class Container>
		bool	operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
		{
			return (x._c <= y._c);
		}
}
