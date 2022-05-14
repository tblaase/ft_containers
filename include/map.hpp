/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:20:09 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/14 13:44:41 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "utils/algorithm.hpp"
#include "utils/utils.hpp"
#include "utils/bidirectional_iterator.hpp"
#include "utils/rev_bidirectional_iterator.hpp"
#include "utils/avl_tree.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:
				typedef Key														key_type;
				typedef T														mapped_type;
				typedef ft::pair<const key_type, mapped_type>					value_type;
				typedef Compare													key_compare;
				typedef Allocator												allocator_type;
				typedef typename allocator_type::reference						reference;
				typedef typename allocator_type::const_reference				const_reference;
				typedef typename allocator_type::pointer						pointer;
				typedef typename allocator_type::const_pointer					const_pointer;
				typedef typename allocator_type::size_type						size_type;
				typedef typename allocator_type::difference_type				difference_type;

			private:
				typedef Node<value_type>										Node_type;
				typedef Node_type*												NodePtr;
				typedef ft::avl_tree<value_type, key_compare, allocator_type>	Tree_type;

			public:
				typedef typename Tree_type::iterator							iterator;
				typedef typename Tree_type::const_iterator						const_iterator;
				typedef typename Tree_type::reverse_iterator					reverse_iterator;
				typedef typename Tree_type::const_reverse_iterator				const_reverse_iterator;

				class value_compare
				{
					friend class map;

				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}

				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool	operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					};
				};

			private:
				Tree_type	_tree;
				key_compare	_comp;

			public:
				// empty constructor
				explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc), _comp(comp)
				{};

				// range constructor
				template <class InputIterator>
					map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc), _comp(comp)
					{
						this->insert(first, last);
					}

				// copy conmstructor
				map (const map& src)
				{
					*this = src;
				}

				// destructor
				~map()
				{
					this->clear();
				}

				// assignment operator overload
				map& operator= (const map& src)
				{
					if (this == &src)
						return (*this);
					this->clear();
					this->insert(src.begin(), src.end());
					return (*this);
				}

			// ##### Iterators #####
				iterator begin()
				{
					return (this->_tree.begin());
				}

				const_iterator begin() const
				{
					return (this->_tree.begin());
				}

				iterator end()
				{
					return (this->_tree.end());
				}

				const_iterator end() const
				{
					return (this->_tree.end());
				}

				reverse_iterator rbegin()
				{
					return (this->_tree.rbegin());
				}

				const_reverse_iterator rbegin() const
				{
					return (this->_tree.rbegin());
				}

				reverse_iterator rend()
				{
					return (this->_tree.rend());
				}

				const_reverse_iterator rend() const
				{
					return (this->_tree.rend());
				}

			// ##### Capacity #####
				bool empty() const
				{
					return (this->_tree.empty());
				}

				size_type size() const
				{
					return (this->_tree.size());
				}

				size_type max_size() const
				{
					return (this->_tree.max_size());
				}

			// ##### Element access #####
				mapped_type& operator[] (const key_type& k)
				{
					return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
				}

			// ##### Modifiers #####
				pair<iterator,bool> insert (const value_type& val)
				{
					if (this->count(val.first))
						return (ft::make_pair(this->find(val.first), false));
					this->_tree.insert(val);
					return (ft::make_pair(this->find(val.first), true));
				}

				iterator insert (iterator position, const value_type& val)
				{
					NodePtr temp = position.base();
					NodePtr	successor = _getSuccessor(temp);
					NodePtr	end = this->_tree.getEnd();
					if ((temp != end && temp->data.first < val.first) &&
						(successor == end || successor->data.first > val.first)) {
						position = iterator(this->_tree.insertWithHint(temp, val));
					}
					else
						position = this->insert(val).first;
					return position;
				}

				template <class InputIterator>
					void insert (InputIterator first, InputIterator last)
					{
						for(; first != last; ++first)
							this->insert(*first);
					}

				void erase (iterator position)
				{
					this->erase((*position).first);
				}

				size_type erase (const key_type& k)
				{
					size_type tmp_size = this->size();
					this->_tree.deleteNode(k);
					return (tmp_size - this->size());
				}

				void erase (iterator first, iterator last) //needs testing with fsanitize=address
				{
					iterator	temp;
					while (first != last)
					{
						temp = first;
						++first;
						this->erase((*temp).first);
					}
				}

				void swap (map& x)
				{
					this->_tree.swap(x);
				}

				void clear()
				{
					this->_tree.clear();
				}

			// ##### Observers #####
				key_compare key_comp() const
				{
					return (key_compare());
				}

				value_compare value_comp() const
				{
					return (value_compare(this->_comp));
				}

			// ##### Operations #####
				iterator find (const key_type& k)
				{
					return (iterator(this->_tree.find(k)));
				}

				const_iterator find (const key_type& k) const
				{
					return (const_iterator(this->_tree.find(k)));
				}

				size_type count (const key_type& k) const
				{
					return (this->_tree.search(k));
				}

				iterator lower_bound (const key_type& k)
				{
					return (iterator(this->_tree.lower_bound(k)));
				}

				const_iterator lower_bound (const key_type& k) const
				{
					return (const_iterator(this->_tree.lower_bound(k)));
				}

				iterator upper_bound (const key_type& k)
				{
					return (iterator(this->_tree.upper_bound(k)));
				}

				const_iterator upper_bound (const key_type& k) const
				{
					return (const_iterator(this->_tree.upper_bound(k)));
				}

				pair<const_iterator,const_iterator> equal_range (const key_type& k) const
				{
					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}

				pair<iterator,iterator> equal_range (const key_type& k)
				{
					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}

			// ##### Allocator #####
				allocator_type get_allocator() const
				{
					return (this->_tree.get_allocator());
				}
		};
		// non member functions
		template <typename Key, typename T, typename Compare>
			void swap(map<Key, T, Compare>& x, map<Key, T, Compare>& y)
			{
				x.swap(y);
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator==(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
			{
				if (x.size() != y.size())
					return (false);
				return (ft::equal(x.begin(), x.end(), y.begin()));
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator!=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
			{
				return (!(x == y));
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator<(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
			{
				return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator<=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
			{
				return !(y < x);
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator>(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
			{
				return (x > y);
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator>=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
			{
				return (!(x < y));
			}
}
