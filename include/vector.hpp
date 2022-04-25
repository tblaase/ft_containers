/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:50:45 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/25 18:30:26 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <iostream>
#include <memory>
#include <vector>

#include "utils/vector_iterator.hpp"
#include "utils/utils.hpp"

namespace ft
{
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
				typedef T												value_type;
				typedef Allocator										allocator_type;
				typedef typename allocator_type::reference				reference;
				typedef typename allocator_type::const_reference		const_reference;
				// typedef ft::random_access_iterator<value_type>			iterator;
				// typedef ft::random_access_iterator<const value_type>	const_iterator;
				typedef typename allocator_type::size_type				size_type;
				typedef typename allocator_type::difference_type		difference_type;
				typedef typename allocator_type::pointer				pointer;
				typedef typename allocator_type::const_pointer			const_pointer;
				// typedef std::reverse_iterator<iterator>					reverse_iterator;
				// typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;
		private:
				pointer			_array;
				size_type		_size;
				size_type		_capacity;
				allocator_type	_alloc;

				// template <class InputIterator>
				// size_type		_distance(InputIterator first, InputIterator last)
				// {
				// 	size_type	res;

				// 	res = 0;
				// 	while (first != last)
				// 	{
				// 		res++;
				// 		first++;
				// 	}

				// 	return (res);
				// }

		public:
				// different default constructor
					// creates vector with size of 0
				explicit vector(const allocator_type& alloc = allocator_type()):
								_size(0), _capacity(0), _alloc(alloc)
				{
					this->_array = this->_alloc.allocate(this->_capacity);
				}

				// fill constructor
					// create vector of size count and initialize it with value
				explicit vector(size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type()):
								_size(n), _capacity(n), _alloc(alloc)
				{
					this->_arr = _alloc.allocate(this->_capacity);
					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(this->_array + i, val);
				}

				// range constructor
					// creates vector with the range between it_start and it_end
					// and copies the corresponding values
				template<class InputIterator>
					explicit vector(InputIterator it_start, InputIterator it_end, const alloc &alloc = alloc(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL): _alloc(alloc)
					{
						// still has to be understood, then implemented
						(void)it_start;
						(void)it_end;
					}

				// copy constructor
				vector(const vector &src): _array(NULL), _size(0), _capacity(0)
				{
					*this = src;
				}

				// destructor
				~vector()
				{
					if (this->_array)
					{
						clear();
						this->_alloc.deallocate(this->_array, this->_capacity);
					}
				}

				// assigation operator overload
				vector &operator=(const vector &src)
				{
					if (this->_capacity)
						delete (this->_capacity);
					this->_size = src._size;
					this->_capacity = src._capacity;
					this->_alloc = src._alloc;
					this->_array = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(this->_array + i, src._array[i]);

					return (*this);
				}

				size()const
				{
					return (this->_size);
				}

				max_size()const
				{
					return (_alloc.max_size());
				}

				size_type	resize(size_type n, value_type val = value_type())
				{
					// implement resize :'D
				}

				size_type	capacity()const
				{
					return (this->_capacity);
				}

				bool	empty()const
				{
					return (this->_size == 0);
				}

				void	reserve(size_type n)
				{
					if(n > ft::vector::max_size())
						throw std::length_error(("vector reserve bigger than max: " + ft::vector::max_size())); // check if needed
					else if (n < this->_capacity)
						return ;
					pointer temp = this->_array;
					size_type temp_cap = this->_capacity;
					this->_capacity = n;
					this->_array = this->_alloc.allocate(this->_capacity);
					if (this->_array == NULL)
					{
						this->_array = temp;
						this->_capacity = temp_cap;
						throw std::bad_alloc(("vector allocation failed: " + std::perror(NULL))); //check if needed
					}
					for (size_type i = 0; i < this->size; i++)
						this->_alloc.construct(this->_array + i, temp._array[i]);
					delete (temp);

				}


					void	clear()
				{
					for (size_type i = 0; i < _size; i++)
						this->_alloc.destroy(this->_array + i);
					this->_size = 0;
				}

	};
}
