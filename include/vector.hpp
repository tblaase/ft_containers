/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:50:45 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/24 13:27:16 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <iostream>
#include <memory>

#include "utils/algorithm.hpp"
#include "utils/random_access_iterator.hpp"
#include "utils/rev_random_access_iterator.hpp"
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
				typedef typename allocator_type::size_type				size_type;
				typedef typename allocator_type::difference_type		difference_type;
				typedef typename allocator_type::pointer				pointer;
				typedef typename allocator_type::const_pointer			const_pointer;
				typedef ft::random_access_iterator<pointer>				iterator;
				typedef ft::random_access_iterator<const_pointer>		const_iterator;
				typedef ft::rev_random_access_iterator<const_iterator>	const_reverse_iterator;
				typedef ft::rev_random_access_iterator<iterator>		reverse_iterator;

		private:
				pointer			_array;
				size_type		_size;
				size_type		_capacity;
				allocator_type	_alloc;

				template <class InputIterator>
				size_type	_distance(InputIterator first, InputIterator last)
				{
					size_type	res = 0;

					while (first != last)
					{
						++res;
						++first;
						if (res == this->max_size() && first != last)
							throw(std::length_error("ft::vector::_M_Range_insert"));
					}

					return (res);
				}

				size_type	_get_n(iterator position)
				{
					size_type	n;

					n = 0;
					for (iterator it = begin(); it < position; ++it)
						++n;

					return (n);
				}

				void	_delete(size_type cap)
				{
					for (size_type i = 0; i < cap; ++i)
						this->_alloc.destroy(this->_array + i);
					this->_alloc.deallocate(this->_array, cap);
				}

		public:
				// default constructor
					// creates vector with size of 0
				explicit vector(const allocator_type& alloc = allocator_type()):
					_array(NULL), _size(0), _capacity(0), _alloc(alloc)
				{
					this->_array = this->_alloc.allocate(this->_capacity);
				}

				// fill constructor
					// create vector of size n and initialize it with value
				explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
					_array(NULL), _size(n), _capacity(n), _alloc(alloc)
				{
					if (this->_capacity > this->max_size())
						throw (std::length_error("cannot create ft::vector larger than max_size()"));
					this->_array = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < n; ++i)
						this->_alloc.construct(this->_array + i, val);
				}

				// range constructor
					// creates vector with the range between it_start and it_end
					// and copies the corresponding values
				template <class InputIt>
					explicit vector(InputIt first, InputIt last, const allocator_type& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true):
						_array(NULL), _size(0), _alloc(alloc)
					{
						InputIt	tmp = first;

						while (tmp != last)
						{
							this->_size++;
							++tmp;
						}
						this->_capacity = this->_size;
						this->_array = this->_alloc.allocate(this->_capacity);
						for (size_type i = 0; first != last; ++i)
						{
							this->_alloc.construct(this->_array + i, *(first));
							++first;
						}
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

				// assignation operator overload
				vector	&operator=(const vector &src)
				{
					if (this->_array != NULL)
						this->_delete(this->_capacity);
					this->_size = src._size;
					this->_capacity = src._capacity;
					this->_alloc = src._alloc;
					this->_array = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < this->_size; ++i)
						this->_alloc.construct(this->_array + i, src._array[i]);

					return (*this);
				}

		// ##### Member functions for Iterators #####

				iterator	begin()
				{
					return(iterator(this->_array));
				}

				const_iterator	begin() const
				{
					return (const_iterator(this->_array));
				}

				iterator	end()
				{
					return (iterator(this->_array + this->_size));
				}

				const_iterator	end() const
				{
					return (const_iterator(this->_array + this->_size));
				}

				reverse_iterator	rbegin()
				{
					return (reverse_iterator(this->_array + this->_size));
				}

				const_reverse_iterator	rbegin() const
				{
					return (const_reverse_iterator(this->_array + this->_size));
				}

				reverse_iterator	rend()
				{
					return (reverse_iterator(this->_array));
				}

				const_reverse_iterator	rend() const
				{
					return (const_reverse_iterator(this->_array));
				}

		// ##### Member functions for Capacity #####

				size_type	size() const
				{
					return (this->_size);
				}

				size_type	max_size() const
				{
					return (this->_alloc.max_size());
				}

				void	resize(size_type n, value_type val = value_type())
				{
					if (n > this->max_size())
						throw (std::length_error("cannot create ft::vector larger than max_size()"));
					if (this->_capacity < n)
					{
						if (this->_capacity * 2 > n)
						{
							this->reserve(this->_capacity + this->_capacity);
						}
						else
						{
							this->reserve(n);
						}
						for (size_type i = this->_size; i < n; ++i)
							this->_alloc.construct(this->_array + i, val);
					}
					else if (this->_size > n)
						for (size_type i = this->_size - 1; i >= n; --i)
						{
							this->_alloc.destroy(this->_array + i);
							if (i == 0)
								break ;
						}
					else
						for (size_type i = _size; i < n; ++i)
							this->_alloc.construct(this->_array + i, val);
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
					pointer new_arr = this->_alloc.allocate(n);
					for (size_type i = 0; i < this->_size; ++i)
						this->_alloc.construct(new_arr + i, this->_array[i]);
					this->_delete(this->_capacity);
					this->_capacity = n;
					this->_array = new_arr;
				}

		// ##### Member functions for Element access #####

				reference	operator[](size_type position)
				{
					return (this->_array[position]);
				}

				const_reference	operator[](size_type position) const
				{
					return (this->_array[position]);
				}

				reference	at(size_type n)
				{
					if (n >= this->size())
						throw (std::out_of_range("cannot access ft::vector outside of this->size()"));
					return (this->_array[n]);
				}

				const_reference	at(size_type n) const
				{
					if (n >= this->size())
						throw (std::out_of_range("cannot access ft::vector outside of this->size()"));
					return (this->_array[n]);
				}

				reference	front()
				{
					return (this->_array[0]);
				}

				const_reference	front() const
				{
					return (this->_array[0]);
				}

				reference	back()
				{
					return (this->_array[this->_size - 1]);
				}

				const_reference	back() const
				{
					return (this->_array[this->_size - 1]);
				}

		// ##### Member functions for Modifiers #####

				template <class InputIterator>
					void	assign (InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
					{
						this->resize(this->_distance(first, last));
						for (size_type i = 0; i < this->_size; ++i)
						{
							this->_alloc.destroy(this->_array + i);
							this->_alloc.construct(this->_array + i, *(first));
							++first;
						}
					}

				void	assign (size_type n, const value_type& val)
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

				void	push_back (const value_type& val)
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

				void	pop_back()
				{
					if (this->_size < this->_capacity)
						this->_alloc.destroy(this->_array + this->_size);
					--this->_size;
				}

				iterator insert (iterator position, const_reference val)
				{
						this->insert(position, 1, val);
						return (this->begin() + this->_get_n(position));
				}

				void	insert(iterator position, size_type n, const_reference val)
				{
					size_type	diff = this->_distance(this->begin(), position);
					size_type	old_end = this->_get_n(this->end() - 1);

					resize(_size + n);
					for (iterator it = this->end() - 1; it >= this->begin() + diff + n; --it)
					{
						*it = this->_array[old_end];
						--old_end;
					}
					for (iterator it = this->begin() + diff; it != this->begin() + (diff + n); ++it)
						*it = val;
				}

				template < class InputIt >
					void	insert(iterator position, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
					{
						size_type	diff = this->_distance(this->begin(), position);
						size_type	n = this->_distance(first, last);
						value_type	val[n];

						size_type	old_end = this->_get_n(this->end() - 1);
						this->resize(this->_size + n);

						for (size_type i = 0; first != last; ++i)
						{
							val[i] = *first;
							++first;
						}
						for (iterator it = this->end() - 1; it >= this->begin() + diff + n; --it)
						{
							*it = this->_array[old_end];
							--old_end;
						}
						for (size_type i = 0; i < n; ++i)
						{
							*(this->begin() + diff + i) = val[i];
						}
					}

				// the commented out lines would make it a better function, that makes more sense and would not create double values as the original does
				iterator erase (iterator position)
				{
					size_type diff = this->_distance(this->begin(), position);

					this->_alloc.destroy(this->_array + diff);
					// if (diff + 1 < this->_size)
					// {
						for (size_type i = diff; i < this->_size - 1; ++i) // this would be replaced by the while loop below
						// i = diff;
						// while (i < this->_size)
						{
							// if (i + 1 > this->_capacity)
							// 	this->_alloc.construct(this->_array + i, value_type());
							// else
								this->_alloc.construct(this->_array + i, this->_array[i + 1]);
							// ++i;
						}
					// }
					// else
					// 	this->_alloc.construct(this->_array + i, value_type());
					--this->_size;
					return (position);
				}

				// the commented out lines would make it a better function, that makes more sense and would not create double values as the original does
				iterator erase (iterator first, iterator last)
				{
					size_type diff = this->_distance(this->begin(), first);
					size_type n = this->_distance(first, last);
					value_type	val[this->_size - diff - n];
					iterator	old_first = first;
					for (size_type i = 0; last != this->end(); ++i)
					{
						val[i] = *last;
						this->_alloc.destroy(this->_array + this->_get_n(last)); // might be not needed, possibly remove for faster speed
						// this->_alloc.construct(this->_array + this->_get_n(last), value_type());
						++last;
					}
					this->_size -= n;
					for (size_type i = diff; i < this->_size; ++i)
					{
						this->_alloc.destroy(this->_array + i); // might be not needed, possibly remove for faster speed
						this->_alloc.construct(this->_array + i, val[i - diff]);
					}
					return (old_first);
				}

				void swap (vector& x)
				{
					pointer tmp = this->_array;
					size_type tmp_size = this->_size;
					size_type tmp_cap = this->_capacity;

					this->_array = x._array;
					this->_size = x._size;
					this->_capacity = x._capacity;

					x._array = tmp;
					x._size = tmp_size;
					x._capacity = tmp_cap;
				}

				void	clear()
				{
					for (size_type i = 0; i < this->_capacity; ++i)
						this->_alloc.destroy(this->_array + i);
					this->_size = 0;
				}

			// ##### Getter for the Allocator #####

				allocator_type get_allocator() const
				{
					return (this->_alloc);
				}
	};

	// ##### Non member functions of the vector #####

	// ##### Relational opperator overloads #####

	template< class T, class Alloc >
		bool	operator==(const ft::vector<T, Alloc>& x, const ft::vector<T, Alloc>& y)
		{
			if (x.size() != y.size())
				return (false);
			return (ft::equal(x.begin(), x.end(), y.begin()));
		}

	template< class T, class Alloc >
		bool	operator!=(const ft::vector<T, Alloc>& x, const ft::vector<T, Alloc>& y)
		{
			return (!(x == y));
		}

	template< class T, class Alloc >
		bool	operator<(const ft::vector<T, Alloc>& x, const ft::vector<T, Alloc>& y)
		{
			return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
		}

	template< class T, class Alloc >
		bool	operator<=(const ft::vector<T, Alloc>& x, const ft::vector<T, Alloc>& y)
		{
			return (!(y < x));
		}

	template< class T, class Alloc >
		bool	operator>(const ft::vector<T, Alloc>& x, const ft::vector<T, Alloc>& y)
		{
			return (y < x);
		}

	template< class T, class Alloc >
		bool	operator>=(const ft::vector<T, Alloc>& x, const ft::vector<T, Alloc>& y)
		{
			return (!(y > x));
		}

	// ##### functional template of the swap function #####

	template<class T, class Alloc>
		void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
		{
			x.swap(y);
		}
}
