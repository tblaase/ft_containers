/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:20:09 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/10 18:07:05 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "utils/algorithm.hpp"
#include "utils/reverse_iterator.hpp"
#include "utils/utils.hpp"
#include "utils/bidirectional_iterator.hpp"
#include "utils/avl_tree.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:
				// typedefs
				typedef Key																key_type;
				typedef T																mapped_type;
				typedef ft::pair<const key_type, mapped_type>							value_type;
				typedef Compare															key_compare;
				typedef Allocator														allocator_type;
				typedef typename allocator_type::reference								reference;
				typedef typename allocator_type::const_reference						const_reference;
				typedef typename allocator_type::pointer								pointer;
				typedef typename allocator_type::const_pointer							const_pointer;
				typedef typename allocator_type::size_type								size_type;
				typedef typename allocator_type::difference_type						difference_type;
				// typedef ft::bidirectional_iterator<Key, T, Compare, Node, false>		iterator; // maybe rethink the use of the bool and use an overload instead
				// typedef ft::bidirectional_iterator<Key, T, Compare, Node, true>			const_iterator; // maybe rethink the use of the bool and use an overload instead
				// typedef ft::rev_bidirectional_iterator<Key, T, Compare, Node, false>	reverse_iterator; // not implemented yet
				// typedef ft::rev_bidirectional_iterator<Key, T, Compare, Node, true>		const_reverse_iterator; // not implemented yet

				class value_compare: public binary_function<value_type, value_type, bool>
				{
					private:
						friend class map;
					protected:
						key_compare comp;
						value_compare(key_compare c): comp(c)
						{}
					public:
						bool operator()(const value_type &x, const value_type &y) const
						{
							return (comp(x.first, y.first));
						}
				};

			private:
				Node*					_root; // Pointer to the first element of the tree (root)
				Node*					_lastElem; // Pointer to the last elem of the tree
				size_type				_size; // Number of T values inside the map
				allocator_type			_allocPair; // Copy of allocator_type object
				key_compare				_comp; // Copy of comp key_compare predicate
				ft::allocator<Node>		_allocNode; // Node's allocator

			public:
				// empty constructor
				explicit map (const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());

				// range constructor
				template <class InputIterator>
					map (InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());

				// copy conmstructor
				map (const map &src);

				// destructor
				~map();

				// assignment operator overload
				map& operator= (const map &src);

			// ##### Iterators #####
				iterator begin();

				const_iterator begin() const;

				iterator end();

				const_iterator end() const;

				reverse_iterator rbegin();

				const_reverse_iterator rbegin() const;

				reverse_iterator rend();

				const_reverse_iterator rend() const;

			// ##### Capacity #####
				bool empty() const;

				size_type size() const;

				size_type max_size() const;

			// ##### Element access #####
				mapped_type& operator[] (const key_type& k);

			// ##### Modifiers #####
				pair<iterator,bool> insert (const value_type& val);

				iterator insert (iterator position, const value_type& val);

				template <class InputIterator>
					void insert (InputIterator first, InputIterator last);

				void erase (iterator position);

				size_type erase (const key_type& k);

				void erase (iterator first, iterator last);

				void swap (map &x);

				void clear();

			// ##### Observers #####
				key_compare key_comp() const;

				value_compare value_comp() const;

			// ##### Operations #####
				iterator find (const key_type& k);

				const_iterator find (const key_type& k) const;

				size_type count (const key_type& k) const;

				iterator lower_bound (const key_type& k);

				iterator upper_bound (const key_type& k);

				const_iterator upper_bound (const key_type& k) const;

				pair<const_iterator,const_iterator> equal_range (const key_type& k) const;

				pair<iterator,iterator> equal_range (const key_type& k);

			// ##### Allocator #####
				allocator_type get_allocator() const;
		};
		// non member functions
		template <typename Key, typename T, typename Compare>
			void swap(map<Key, T, Compare> &x, map<Key, T, Compare> &y)
			{
				x.swap(y);
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator==(const map<Key,T,Compare,Alloc> &x, const map<Key,T,Compare,Alloc> &y)
			{
				if (x.size() != y.size())
					return (false);
				return (ft::equal(x.begin(), x.end(), y.begin()));
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator!=(const map<Key,T,Compare,Alloc> &x, const map<Key,T,Compare,Alloc> &y)
			{
				return (!(x == y));
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator<(const map<Key,T,Compare,Alloc> &x, const map<Key,T,Compare,Alloc> &y)
			{
				return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator<=(const map<Key,T,Compare,Alloc> &x, const map<Key,T,Compare,Alloc> &y)
			{
				return !(y < x);
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator>(const map<Key,T,Compare,Alloc> &x, const map<Key,T,Compare,Alloc> &y)
			{
				return (x > y);
			}

		template <class Key, class T, class Compare, class Alloc>
			bool operator>=(const map<Key,T,Compare,Alloc> &x, const map<Key,T,Compare,Alloc> &y)
			{
				return (!(x < y));
			}
}
