/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:20:09 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/24 14:29:45 by tblaase          ###   ########.fr       */
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
// #include "utils/reverse_iterator.hpp"
#include "utils/red_black_tree.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef Compare											key_compare;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::value_type				value_type;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::difference_type		difference_type;

			typedef typename Allocator::template rebind<Node<value_type> >::other	node_allocator;
		// value compare

			class value_compare: public std::binary_function <value_type, value_type, bool>
			{
				private:
					friend class map; // only use of friend keyword is here
				protected:
					key_compare comp;
					value_compare	(key_compare c) : comp(c) {}
				public:
					bool operator()	(const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			typedef red_black_tree<Key, value_type, value_compare>			tree;
			typedef Node<value_type>*										node_ptr;
			typedef Node<value_type>										node;

			typedef ft::bidirectional_iterator<Node<value_type> >			iterator;
			typedef ft::const_bidirectional_iterator<Node<value_type> >		const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

		private:
			tree			_tree;
			key_compare		_cmp;
			allocator_type	_alloc;
			node_allocator	_max_size_alloc;
		public:
		// empty constuctor
			explicit map(const Compare& cmp = Compare(), const Allocator& alloc = Allocator()): _tree(tree(value_compare(key_compare()))), _cmp(cmp), _alloc(alloc) {}
		// range constructor
			template <class Iter>
				map(Iter first, Iter last, const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(tree(value_compare(key_compare()))), _cmp(cmp), _alloc(alloc)
				{
					while (first != last)
					{
						_tree.insert(*first);
						++first;
					}
				}
		// copy constructor
			map(const map& src): _tree(tree(value_compare(key_compare())))
			{
				*this = src;
			}
		// destructor
			~map() { }
		// assignation operator overload
			map&	operator=(const map& src)
			{
				if (*this != src)
				{
					this->_cmp = src._cmp;
					this->_alloc = src._alloc;
					this->_tree = src._tree;
				}

				return (*this);
			}

		// ##### Member functions for Iterators #####

			iterator	begin()
			{
				return (iterator(this->_tree.get_lowest()));
			}

			const_iterator	begin() const
			{
				return (const_iterator(this->_tree.get_lowest()));
			}

			iterator	end() {
				return (iterator(this->_tree.get_end()));
			}

			const_iterator	end() const
			{
				return (const_iterator(this->_tree.get_end()));
			}

			reverse_iterator	rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator	rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(this->begin()));
			}

		// ##### Member functions for Capacity #####

			bool	empty() const
			{
				return (this->_tree.size() == 0);
			}

			size_type	size() const
			{
				return (this->_tree.size());
			}

			size_type	max_size() const
			{
				return (this->_max_size_alloc.max_size());
			}

		// ##### Member functions for Element access #####

			mapped_type&	operator[](const key_type& key)
			{
				node_ptr	node = this->_tree.exist(ft::make_pair(key, mapped_type()));
				if (!node)
					return (this->insert(ft::make_pair(key, mapped_type())).first->second);
				return (node->value.second);
			}

			mapped_type&	at(const key_type& key)
			{
				node_ptr	node = this->_tree.exist(ft::make_pair(key, mapped_type()));
				if (!node)
					throw (std::out_of_range("map"));
				return (node->value.second);
			}

			const mapped_type&	at(const key_type& key) const
			{
				node_ptr	node = this->_tree.exist(ft::make_pair(key, mapped_type()));
				if (!node)
					throw (std::out_of_range("map"));
				return (node->value.second);
			}

		// ##### Member functions for Modifiers #####

			ft::pair<iterator, bool>	insert(const value_type& value)
			{
				ft::pair<node_ptr, bool> new_elem = this->_tree.insert(value);
				return (ft::make_pair(iterator(new_elem.first), new_elem.second));
			}

			iterator	insert(iterator pos, const value_type& value)
			{
				(void)pos;
				ft::pair<node_ptr, bool> new_elem = this->_tree.insert(value);
				return (iterator(new_elem.first));
			}

			template <class Iter>
				void	insert(Iter first, Iter last)
				{
					while (first != last)
					{
						this->_tree.insert(*first);
						++first;
					}
				}

			void	erase(iterator pos)
			{
				this->_tree.erase(*pos);
			}

			void	erase(iterator first, iterator last)
			{
				while (first != last)
				{
					iterator	to_delete = first++;
					this->erase(to_delete);
				}
			}

			size_type	erase(const key_type& key)
			{
				size_type	old_size = this->_tree.size();
				this->_tree.erase(ft::make_pair(key, mapped_type()));
				return (old_size - this->_tree.size());
			}

			void	swap(map& src)
			{
				this->_tree.swap(src._tree);
			}

			void	clear()
			{
				this->_tree.clear();
			}

		// ##### Member functions for Observers #####

			key_compare	key_comp() const
			{
				return (Compare());
			}

			value_compare	value_comp() const
			{
				return (value_compare(key_comp()));
			}

		// ##### Member functions for Operations #####

			iterator	find(const key_type& key)
			{
				return (iterator(this->_tree.find(ft::make_pair(key, mapped_type()))));
			}

			const_iterator	find(const key_type& key) const
			{
				return (iterator(this->_tree.find(ft::make_pair(key, mapped_type()))));
			}

			size_type	count(const key_type& key) const
			{
				if (this->_tree.exist(ft::make_pair(key, mapped_type())))
					return (1);
				return (0);
			}

			iterator	lower_bound(const key_type& key)
			{
				iterator it;

				it = this->begin();
				while (it != this->end() && it->first < key)
					it++;
				return (it);
			}

			const_iterator	lower_bound(const key_type& key) const
			{
				const_iterator	it;

				it = this->begin();
				while (it != this->end() && it->first < key)
					++it;
				return (it);
			}

			iterator	upper_bound(const key_type& key)
			{
				iterator it;

				it = this->begin();
				while (it != this->end() && it->first <= key)
					++it;
				return (it);
			}

			const_iterator	upper_bound(const key_type& key) const
			{
				const_iterator	it;

				it = this->begin();
				while (it != this->end() && it->first <= key)
					++it;
				return (it);
			}

			ft::pair<iterator, iterator>	equal_range(const key_type& key)
			{
				return (ft::make_pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const
			{
				return (ft::make_pair<const_iterator, const_iterator>(this->lower_bound(key), this->upper_bound(key)));
			}

		// ##### Getter for the Allocator #####
			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			}
	};

// ##### Non member functions of the map #####

	// ##### functional template of the swap function #####
	template <typename Key, typename T, typename Compare>
		void swap(map<Key, T, Compare>& x, map<Key, T, Compare>& y)
		{
			x.swap(y);
		}

	// ##### Relational opperator overloads #####
	template <class Key, class T, class Compare, class Alloc>
		bool operator== (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
		{
			if (x.size() != y.size())
				return (false);
			return (ft::equal(x.begin(), x.end(), y.begin()));
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator!= (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
		{
			return (!(x == y));
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<  (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
		{
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<= (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
		{
			return !(y < x);
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator>  (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
		{
			return (y < x);
		}

	template <class Key, class T, class Compare, class Alloc>
		bool operator>= (const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
		{
			return (!(x < y));
		}
}
