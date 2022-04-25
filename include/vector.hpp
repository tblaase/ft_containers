/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:50:45 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/24 13:57:01 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <iostream>
#include <memory>
#include <vector>

#include "vector_iterator.hpp"

namespace ft
{
	template<class T, class Allocator = std::allocator<T>>
	class vector
	{
		public:
				typedef T										value_type;
				typedef Allocator								alloc_type;
				typedef typename alloc_type::difference_type	difference_type;
				typedef typename alloc_type::size_type			size_type;

				typedef typename alloc_type::reference			reference;
				typedef typename alloc_type::const_reference	const_reference;
				typedef typename alloc_type::pointer			pointer;
				typedef typename alloc_type::const_pointer		const_pointer;

				typedef typename ft::vector_iterator<T, false>		iterator;
				typedef typename ft::vector_iterator<T, true>		const_iterator;
				typedef typename ft::vector_rev_iterator<T, false>	rev_iterator;
				typedef typename ft::vector_rev_iterator<T, true>	const_rev_iterator;
		private:
				pointer		_vector;
				size_type	_size;
				size_type	_capacity;
				alloc_type	_alloc_type;

		public:
				// default constructor
				// vector(): _vector(NULL), _size(0), _capacity(0)
				// {}

				// different default constructor
					// creates vector with size of 0
				explicit vector(const alloc_type &alloc_type): _alloc_type(alloc), _size(0), _capacity(0)
				{
					this->_vector = this->_alloc_type.allocate(this->_capacity);
				}

				// fill constructor
					// create vector of size count and initialize it with value
				explicit vector(size_type count, const_reference value = value_type(), const alloc_type &alloc = alloc_type()): _size(count), _capacity(count), _alloc_type(alloc)
				{
					this->_arr = _alloc_type.allocate(this->_capacity);
					for (size_type i = 0; i < count; i++)
						this->_alloc_type.construct(this->_vector + i, value);
				}

				// range constructor
					// creates vector with the range between it_start and it_end
					// and copies the corresponding values
				template<class InputIterator>
					explicit vector(InputIterator it_start, InputIterator it_end, const alloc_type &alloc = alloc_type(), typename ft::enable_if<!ft::is)
	};
}
