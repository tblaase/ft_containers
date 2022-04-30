/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:50:45 by tblaase           #+#    #+#             */
/*   Updated: 2022/04/30 12:21:57 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <iostream>
#include <memory>
#include <vector>

#include "utils/random_access_iterator.hpp"
#include "utils/utils.hpp"

namespace ft
{
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
				typedef T											value_type;
				typedef Allocator									allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::size_type			size_type;
				typedef typename allocator_type::difference_type	difference_type;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef random_access_iterator<pointer>				iterator;
				typedef random_access_iterator<const_pointer>		const_iterator;
				// typedef std::reverse_iterator<iterator>				reverse_iterator;
				// typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
		private:
				pointer			_array;
				size_type		_size;
				size_type		_capacity;
				allocator_type	_alloc;

				template <class InputIterator>
				size_type		_distance(InputIterator first, InputIterator last)
				{
					size_type	res = 0;

					while (first < last)
					{
						res++;
						first++;
					}

					return (res);
				}

		public:
				// default constructor
					// creates vector with size of 0
				explicit vector(const allocator_type& alloc = allocator_type()):
								_size(0), _capacity(0), _alloc(alloc)
				{
					if (this->_capacity > this->max_size())
						throw (std::length_error("cannot create ft::vector larger than max_size()"));
					try
					{
						this->_array = _alloc.allocate(this->_capacity);
					}
					catch (std::exception &e)
					{
						std::cerr << "\033[31mAn error occured in the default constructor while allocating your vector: " << e.what() << "\033[0m" << std::endl; // maybe remove those when finnishing up the project
						throw (std::bad_alloc());
					}
				}

				// fill constructor
					// create vector of size count and initialize it with value
				explicit vector(size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type()):
								_size(n), _capacity(n), _alloc(alloc)
				{
					if (this->_capacity > this->max_size())
						throw (std::length_error("cannot create ft::vector larger than max_size()"));
					// try
					// {
					this->_array = _alloc.allocate(this->_capacity);
					// }
					// catch (std::exception &e)
					// {
					// 	std::cerr << "\033[31mAn error occured in the fill constructor while allocating your vector: " << e.what() << "\033[0m" << std::endl; // maybe remove those when finnishing up the project
					// 	throw (std::bad_alloc());
					// }
					for (size_type i = 0; i < n; ++i)
						this->_alloc.construct(this->_array + i, val);
				}

				// range constructor
					// creates vector with the range between it_start and it_end
					// and copies the corresponding values
				template<class InputIterator>
					explicit vector(InputIterator it_start, InputIterator it_end, const allocator_type &alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL): _alloc(alloc)
					{
						if (this->_distance(it_start, it_end) > this->max_size())
							throw (std::length_error("cannot create ft::vector larger than max_size()"));
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
					// try
					// {
						this->_array = _alloc.allocate(this->_capacity);
					// }
					// catch (std::exception &e)
					// {
					// 	std::cerr << "\033[31mAn error occured in the copy constructor while allocating your vector: " << e.what() << "\033[0m" << std::endl; // maybe remove those when finnishing up the project
					// 	throw (std::bad_alloc());
					// }
					for (size_type i = 0; i < this->_size; ++i)
						this->_alloc.construct(this->_array + i, src._array[i]);

					return (*this);
				}

		// ##### Member functions for Iterators #####

				iterator	begin()
				{
					return(iterator(_array));
				}

				const_iterator	begin() const
				{
					return (const_iterator(_array));
				}

				iterator	end()
				{
					return (iterator(this->_array + this->_size));
				}

				const_iterator	end() const
				{
					return (const_iterator(this->_array + this->_size));
				}

				// reverse_iterator rbegin()
				// {
				// 	return (reverse_iterator(this->_array + this->_size));
				// }

				// const_reverse_iterator rbegin()
				// {
				// 	return (const_reverse_iterator(this->_array + this->_size));
				// }

				// reverse_iterator rend()
				// {
				// 	return (reverse_iterator(this->_array));
				// }

				// const_reverse_iterator rend()
				// {
				// 	return (const_reverse_iterator(this->_array));
				// }
		// ##### Member functions for Capacity #####

				size_type size() const
				{
					return (this->_size);
				}

				size_type max_size() const
				{
					return (_alloc.max_size());
				}

				void	resize(size_type n, value_type val = value_type())
				{
					if (n > this->max_size())
						throw (std::length_error("cannot create ft::vector larger than max_size()"));
					if (n < this->_size)
						this->_size = n;
					else if (n < (this->_capacity + this->_capacity))
					{
						this->reserve((size_type)(this->_capacity + this->_capacity));
						if (this->_array[this->_size] != val)
						{
							for (size_type i = this->_size; i < this->_capacity; ++i)
								this->_alloc.construct(this->_array + i, val);
						}
					}
					else
					{
							this->reserve(n);
							if (this->_array[this->_size] != val)
							{
								for (size_type i = this->_size; i < this->_capacity; ++i)
									this->_alloc.construct(this->_array + i, val);
							}
					}
					this->_size = n;
				}

				size_type	capacity() const
				{
					return (this->_capacity);
				}

				bool	empty()const
				{
					return (this->_size == 0);
				}

				void	reserve(size_type n)
				{
					if (n > this->max_size())
						throw (std::length_error("cannot create ft::vector larger than max_size()"));
					else if (n <= this->_capacity)
						return ;
					pointer tmp = this->_array;
					size_type tmp_cap = this->_capacity;
					this->_capacity = n;
					try
					{
						this->_array = this->_alloc.allocate(this->_capacity);
					}
					catch (std::exception &e)
					{
						this->_array = tmp;
						this->_capacity = tmp_cap;
						throw (std::bad_alloc());
					}
					for (size_type i = 0; i < this->_size; ++i)
						this->_alloc.construct(this->_array + i, tmp[i]);

					for (size_type i = this->_size; i < this->_capacity; ++i)
						this->_alloc.construct(this->_array + i, value_type());

					for (size_type i = 0; i < tmp_cap; ++i)
						this->_alloc.destroy(tmp + i);
					this->_alloc.deallocate(tmp, tmp_cap);
				}

		// ##### Member functions for element access #####

				reference		operator[](size_type pos)
				{
					return (this->_array[pos]);
				}

				const_reference	operator[](size_type pos) const
				{
					return (this->_array[pos]);
				}

				reference at (size_type n)
				{
					if (n >= this->size() || n < 0)
						throw (std::out_of_range("ft::vector"));
					return (this->_array[n]);
				}

				const_reference at (size_type n) const
				{
					if (n >= this->size() || n < 0)
						throw std::out_of_range("ft::vector");
					return (this->_array[n]);
				}

				reference front()
				{
					return (this->_array[0]);
				}

				const_reference front() const
				{
					return (this->array[0]);
				}

				reference back()
				{
					return (this->_array[this->_size - 1]);
				}

				const_reference back() const
				{
					return (this->_array[this->_size - 1]);
				}

		// ##### Member functions for Modifiers #####

				template <class InputIterator>
					void assign (InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
					{
						size_type diff = _distance(first, last);
						if (diff > this->_capacity)
						{
							pointer tmp = this->_array;
							size_type tmp_cap = this->_capacity;
							this->_array = this->_alloc.allocate(diff); // if throws any exception, due to bad_alloc, or bad size, thats fine
							for (size_type i = 0; i < this->_capacity; ++i)
								this->_alloc.construct(this->_array + i, tmp[i]);

							// for (size_type i = this->_size; i < this->_capacity; ++i) //maybe cut this out for optimization
							// 	this->_alloc.construct(this->_array + i, value_type());

							for (size_type i = 0; i < tmp_cap; ++i)
								this->_alloc.destroy(tmp + i);
							this->_alloc.deallocate(tmp, tmp_cap);

							this->_capacity = diff;
							this->_size = diff;

						}
						else
						{
							this->_size = diff;
						}
					}

				void assign (size_type n, const value_type& val)
				{
					if (n > this->max_size())
						throw (std::length_error("cannot create ft::vector larger than max_size()"));
					if (n > this->_capacity)
					{
						pointer tmp = this->_array;
						size_type tmp_cap = this->_capacity;
						this->_array = this->_alloc.allocate(n);
						for (size_type i = 0; i < n; ++i)
							this->_alloc.construct(this->_array + i, val);

						for (size_type i = 0; i < tmp_cap; ++i)
							this->_alloc.destroy(tmp + i);
						this->_alloc.deallocate(tmp, tmp_cap);

						this->_capacity = n;
						this->_size = n;
					}
					else
					{
						this->_size = n;
						for (size_type i = 0; i < this->_size; ++i)
						{
							this->_alloc.destroy(this->_array + i);
							this->_alloc.construct(this->_array + i, val);
						}
					}
				}

				void push_back (const value_type& val)
				{
					if (this->_size == this->_capacity)
					{
						this->resize(this->_size + 1);
						this->_alloc.construct(this->_array + this->_size - 1, val);
					}
					else
					{
						this->_alloc.construct(this->_array + this->_size, val);
						++this->_size;
					}
				}

				void pop_back()
				{
					if (this->_size < this->_capacity)
						this->_alloc.destroy(this->_array + this->_size);
					--this->_size;
				}

				iterator insert (iterator position, const value_type& val)
				{
					size_type diff = _distance(this->begin(), position);
					if (this->_size + 1 > this->_capacity)
						this->resize(this->_size + 1);
					else
						++this->_size;
					for (size_type i = this->_size; i > diff; --i)
						this->_array[i] = this->_array[i - 1];
					this->_array[diff] = val;
					return (position);
				}

				void insert (iterator position, size_type n, const value_type& val)
				{
					size_type diff = _distance(this->begin(), position);
					if (this->_size + n > this->_capacity)
						this->resize(this->_size + n);
					else
						this->_size += n;
					for (size_type i = this->_size - 1; i - n > diff; --i)
						this->_array[i] = this->_array[i - n];
					for (size_type i = 0; i < n; ++i)
						this->_array[i + diff] = val;
				}

				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
					{
						size_type diff = _distance(this->begin(), position);
						pointer tmp = this->_alloc.allocate(this->_capacity);
						for (size_type i = 0; i < this->_capacity; ++i)
							this->_alloc.construct(tmp + i, this->_array[i]);
						size_type n = _distance(first, last);
						if (this->_size + n > this->_capacity)
							this->resize(this->_size + n);
						else
							this->_size += n;
						for (size_type i = this->_size - 1; i - n > diff; --i)
							this->_array[i] = this->_array[i - n];
						for (size_type i = 0; i < n; ++i)
							this->_alloc.construct(this->_array + (i + diff), tmp[i + diff]);
							// this->_array[i + diff] = tmp[i + diff];

					}

				void	clear()
				{
					for (size_type i = 0; i < this->_capacity; ++i)
						this->_alloc.destroy(this->_array + i);
					this->_size = 0;
				}

	};
}
