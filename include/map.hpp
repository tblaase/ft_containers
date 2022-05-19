/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:20:09 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/19 17:31:21 by tblaase          ###   ########.fr       */
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
#include "utils/avl_tree.hpp"

// namespace ft
// {
// 	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
// 	class map
// 	{
// 		public:
// 			typedef Key														key_type;
// 			typedef T														mapped_type;
// 			typedef ft::pair<const key_type, mapped_type>					value_type;
// 			typedef Compare													key_compare;
// 			typedef Allocator												allocator_type;
// 			// typedef allocator_type											value_type;
// 			typedef typename allocator_type::reference						reference;
// 			typedef typename allocator_type::const_reference				const_reference;
// 			typedef typename allocator_type::pointer						pointer;
// 			typedef typename allocator_type::const_pointer					const_pointer;
// 			typedef typename allocator_type::size_type						size_type;
// 			typedef typename allocator_type::difference_type				difference_type;

// 			typedef typename Allocator::template rebind<Node<value_type> >::other	node_allocator;
// 			private:
// 				typedef ft::avl_tree<value_type, key_compare, allocator_type>	tree_type;
// 			public:
// 				// typedef typename tree_type::iterator							iterator;
// 				// typedef typename tree_type::const_iterator						const_iterator;
// 				// typedef typename tree_type::reverse_iterator					reverse_iterator;
// 				// typedef typename tree_type::const_reverse_iterator				const_reverse_iterator;


// 			// class value_compare/*: public std::binary_function <value_type, value_type, bool>*/
// 			// {
// 			// 	// private:
// 			// 		friend class map;
// 			// 	protected:
// 			// 		Compare comp;
// 			// 		value_compare (Compare c) : comp(c)
// 			// 		{}
// 			// 	public:
// 			// 		typedef bool		result_type;
// 			// 		typedef value_type	first_argument_type;
// 			// 		typedef value_type	second_argument_type;
// 			// 		bool operator() (const value_type& x, const value_type& y) const
// 			// 		{
// 			// 			return comp(x.first, y.first);
// 			// 		}
// 			// };
// 			class value_compare: public std::binary_function <value_type, value_type, bool>
// 			{
// 				private:
// 					friend class map;
// 				protected:
// 					key_compare comp;
// 					value_compare (key_compare c) : comp(c) {}
// 				public:
// 					bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
// 			};


// 			typedef avl_tree<Key, value_type, value_compare>		tree;
// 			typedef Node<value_type>*								node_ptr;
// 			typedef Node<value_type>								node;

// 			typedef ft::bidirectional_iterator<pointer, node_ptr>				iterator;
// 			typedef ft::bidirectional_iterator<const_pointer, node_ptr>			const_iterator;
// 			typedef ft::rev_bidirectional_iterator<pointer, node_ptr>			reverse_iterator;
// 			typedef ft::rev_bidirectional_iterator<const_pointer, node_ptr>		const_reverse_iterator;

// 		private:
// 			tree			_tree;
// 			key_compare		_comp;
// 			allocator_type	_alloc;
// 			node_allocator	_max_size_alloc;

// 			public:
// 				// empty constructor
// 				explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc), _comp(comp)
// 				{};

// 				// range constructor
// 				template <class InputIterator>
// 					map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(comp, alloc), _comp(comp)
// 					{
// 						this->insert(first, last);
// 					}

// 				// copy conmstructor
// 				map (const map& src): _tree(tree(value_compare(key_compare())))
// 				{
// 					*this = src;
// 				}

// 				// destructor
// 				~map()
// 				{
// 					this->clear();
// 				}

// 				// assignment operator overload
// 				map& operator= (const map& src)
// 				{
// 					if (this == &src)
// 						return (*this);
// 					this->clear();
// 					this->insert(src.begin(), src.end());
// 					return (*this);
// 				}

// 			// ##### Iterators #####
// 				iterator begin()
// 				{
// 					return (iterator(this->_tree.begin()));
// 				}

// 				const_iterator begin() const
// 				{
// 					return (const_iterator(this->_tree.begin()));
// 				}

// 				iterator end()
// 				{
// 					return (iterator(this->_tree.end()));
// 				}

// 				const_iterator end() const
// 				{
// 					return (const_iterator(this->_tree.end()));
// 				}

// 				reverse_iterator rbegin()
// 				{
// 					return (reverse_iterator(this->_tree.rbegin()));
// 				}

// 				const_reverse_iterator rbegin() const
// 				{
// 					return (const_reverse_iterator(this->_tree.rbegin()));
// 				}

// 				reverse_iterator rend()
// 				{
// 					return (reverse_iterator(this->_tree.rend()));
// 				}

// 				const_reverse_iterator rend() const
// 				{
// 					return (const_reverse_iterator(this->_tree.rend()));
// 				}

// 			// ##### Capacity #####
// 				bool empty() const
// 				{
// 					return (this->_tree.empty());
// 				}

// 				size_type size() const
// 				{
// 					return (this->_tree.size());
// 				}

// 				size_type max_size() const
// 				{
// 					return (this->_tree.max_size());
// 				}

// 			// ##### Element access #####
// 				mapped_type& operator[] (const key_type& k)
// 				{
// 					return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
// 				}

// 			// ##### Modifiers #####
// 				pair<iterator,bool> insert (const value_type& val)
// 				{
// 					if (this->count(val.first))
// 						return (ft::make_pair(this->find(val.first), false));
// 					this->_tree.insert(val);
// 					return (ft::make_pair(this->find(val.first), true));
// 				}

// 				iterator insert (iterator position, const value_type& val)
// 				{
// 					node_ptr temp = position.base();
// 					node_ptr	successor = _getSuccessor(temp);
// 					node_ptr	end = this->_tree.getEnd();
// 					if ((temp != end && temp->data.first < val.first) &&
// 						(successor == end || successor->data.first > val.first)) {
// 						position = iterator(this->_tree.insertWithHint(temp, val));
// 					}
// 					else
// 						position = this->insert(val).first;
// 					return position;
// 				}

// 				template <class InputIterator>
// 					void insert (InputIterator first, InputIterator last)
// 					{
// 						for(; first != last; ++first)
// 							this->insert(*first);
// 					}

// 				void erase (iterator position)
// 				{
// 					this->erase((*position).first);
// 				}

// 				size_type erase (const key_type& k)
// 				{
// 					size_type tmp_size = this->size();
// 					this->_tree.deleteNode(k);
// 					return (tmp_size - this->size());
// 				}

// 				void erase (iterator first, iterator last) //needs testing with fsanitize=address
// 				{
// 					iterator	temp;
// 					while (first != last)
// 					{
// 						temp = first;
// 						++first;
// 						this->erase((*temp).first);
// 					}
// 				}

// 				void swap (map& x)
// 				{
// 					this->_tree.swap(x);
// 				}

// 				void clear()
// 				{
// 					this->_tree.clear();
// 				}

// 			// ##### Observers #####
// 				key_compare key_comp() const
// 				{
// 					return (key_compare());
// 				}

// 				value_compare value_comp() const
// 				{
// 					return (value_compare(this->_comp));
// 				}

// 			// ##### Operations #####
// 				iterator find (const key_type& k)
// 				{
// 					return (iterator(this->_tree.find(k)));
// 				}

// 				const_iterator find (const key_type& k) const
// 				{
// 					return (const_iterator(this->_tree.find(k)));
// 				}

// 				size_type count (const key_type& k) const
// 				{
// 					return (this->_tree.search(k));
// 				}

// 				iterator lower_bound (const key_type& k)
// 				{
// 					return (iterator(this->_tree.lower_bound(k)));
// 				}

// 				const_iterator lower_bound (const key_type& k) const
// 				{
// 					return (const_iterator(this->_tree.lower_bound(k)));
// 				}

// 				iterator upper_bound (const key_type& k)
// 				{
// 					return (iterator(this->_tree.upper_bound(k)));
// 				}

// 				const_iterator upper_bound (const key_type& k) const
// 				{
// 					return (const_iterator(this->_tree.upper_bound(k)));
// 				}

// 				pair<const_iterator,const_iterator> equal_range (const key_type& k) const
// 				{
// 					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
// 				}

// 				pair<iterator,iterator> equal_range (const key_type& k)
// 				{
// 					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
// 				}

// 			// ##### Allocator #####
// 				allocator_type get_allocator() const
// 				{
// 					return (this->_alloc);
// 				}
// 		};
// 		// non member functions
// 		template <typename Key, typename T, typename Compare>
// 			void swap(map<Key, T, Compare>& x, map<Key, T, Compare>& y)
// 			{
// 				x.swap(y);
// 			}

// 		template <class Key, class T, class Compare, class Alloc>
// 			bool operator==(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
// 			{
// 				if (x.size() != y.size())
// 					return (false);
// 				return (ft::equal(x.begin(), x.end(), y.begin()));
// 			}

// 		template <class Key, class T, class Compare, class Alloc>
// 			bool operator!=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
// 			{
// 				return (!(x == y));
// 			}

// 		template <class Key, class T, class Compare, class Alloc>
// 			bool operator<(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
// 			{
// 				return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
// 			}

// 		template <class Key, class T, class Compare, class Alloc>
// 			bool operator<=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
// 			{
// 				return !(y < x);
// 			}

// 		template <class Key, class T, class Compare, class Alloc>
// 			bool operator>(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
// 			{
// 				return (x > y);
// 			}

// 		template <class Key, class T, class Compare, class Alloc>
// 			bool operator>=(const map<Key,T,Compare,Alloc>& x, const map<Key,T,Compare,Alloc>& y)
// 			{
// 				return (!(x < y));
// 			}
// }

namespace ft {
	template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
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

			class value_compare: public std::binary_function <value_type, value_type, bool>
			{
				private:
					friend class map;
				protected:
					key_compare comp;
					value_compare (key_compare c) : comp(c) {}
				public:
					bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};

			typedef avl_tree<Key, value_type, value_compare>		tree;
			typedef Node<value_type>*								node_ptr;
			typedef Node<value_type>								node;

			typedef ft::bidirectional_iterator<Node<value_type> >	iterator;
			typedef ft::bidirectional_iterator<Node<value_type> >	const_iterator;
			typedef ft::rev_bidirectional_iterator<iterator>		reverse_iterator;
			typedef ft::rev_bidirectional_iterator<const_iterator>	const_reverse_iterator;
			// typedef ft::reverse_iterator<iterator>				reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			tree			_tree;
			key_compare		_comp;
			allocator_type	_alloc;
			node_allocator	_max_size_alloc;
		public:
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(tree(value_compare(key_compare()))), _comp(comp), _alloc(alloc)
			{}

			template <class Iter>
				map(Iter first, Iter last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(tree(value_compare(key_compare()))), _comp(comp), _alloc(alloc)
				{
					this->insert(first, last);
				}

			map(const map& src): _tree(tree(value_compare(key_compare()))), _comp(src._comp), _alloc(src._alloc)
			{
				*this = src;
			}

			~map()
			{}

			map&	operator=(const map& src)
			{
				if (*this != src)
				{
					this->_comp = src._comp;
					this->_alloc = src._alloc;
					this->_tree = src._tree;
				}
				return (*this);
			}

			iterator				begin()
			{
				return (iterator(_tree.get_lowest()));
			}

			const_iterator			begin() const
			{
				return (const_iterator(_tree.get_lowest()));
			}

			iterator				end()
			{
				return (iterator(_tree.get_end()));
			}

			const_iterator			end() const
			{
				return (const_iterator(_tree.get_end()));
			}

			reverse_iterator		rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator		rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			}

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

			mapped_type&	operator[](const key_type& key)
			{
				node_ptr	node;

				node = this->_tree.exist(ft::make_pair(key, mapped_type()));
				if (!node)
					return (insert(ft::make_pair(key, mapped_type())).first->second);
				return (node->data.second);
			}

			mapped_type&	at(const key_type& key)
			{
				node_ptr	node;

				node = _tree.exist(ft::make_pair(key, mapped_type()));
				if (!node)
					throw (std::out_of_range("map"));
				return (node->value.second);
			}

			const mapped_type&	at(const key_type& key) const
			{
				node_ptr	node;

				node = _tree.exist(ft::make_pair(key, mapped_type()));
				if (!node)
					throw (std::out_of_range("map"));
				return (node->value.second);
			}

			ft::pair<iterator, bool>	insert(const value_type& value)
			{
				ft::pair<iterator, bool> new_elem = this->_tree.insert(value);
				return (ft::make_pair(iterator(new_elem.first), new_elem.second));
			}

			iterator	insert(iterator pos, const value_type& value)
			{
				(void)pos; // maybe there is a better way
				ft::pair<iterator, bool> new_elem = this->_tree.insert(value);
				return (iterator(new_elem.first));
			}

			template <class InputIterator>
				void	insert(InputIterator first, InputIterator last)
				{
					while (first != last)
					{
						this->_tree.insert(*first);
						first++;
					}
				}

			// pair<iterator,bool> insert (const value_type& val)
			// 	{
			// 		if (this->count(val.first))
			// 			return (ft::make_pair(this->find(val.first), false));
			// 		this->_tree.insert(this->_tree._root, val);
			// 		return (ft::make_pair(this->find(val.first), true));
			// 	}

			// iterator insert (iterator position, const value_type& val)
			// {
			// 	node_ptr temp = position.base();
			// 	node_ptr successor = _getSuccessor(temp);
			// 	node_ptr end = this->_tree.getEnd();
			// 	if ((temp != end && temp->data.first < val.first) &&
			// 		(successor == end || successor->data.first > val.first)) {
			// 		position = iterator(this->_tree.insertWithHint(temp, val));
			// 	}
			// 	else
			// 		position = this->insert(this->_tree._root, val).first;
			// 	return position;
			// }

			// template <class InputIterator>
			// 	void insert (InputIterator first, InputIterator last)
			// 	{
			// 		// for(; first != last; ++first)
			// 		// 	this->insert(*first);
			// 		while (first != last)
			// 		{
			// 			this->_tree.insert(*first);
			// 			++first;
			// 		}
			// 	}

			// void	erase(iterator pos)
			// {
			// 	this->_tree.erase(*pos);
			// }

			// void	erase(iterator first, iterator last)
			// {
			// 	while (first != last)
			// 	{
			// 		iterator to_delete = first++;
			// 		this->erase(to_delete);
			// 	}
			// }

			// size_type	erase(const key_type& key)
			// {
			// 	size_type old_size;

			// 	old_size = this->_tree.size();
			// 	this->_tree.erase(ft::make_pair(key, mapped_type()));
			// 	return (old_size - this->_tree.size());
			// }

			void	erase(iterator pos)
			{
				value_type val = *pos;
				this->_tree.erase(val);
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
				size_type	tmp_size;

				tmp_size = this->_tree.size();
				this->_tree.erase(ft::make_pair(key, mapped_type()));
				return (tmp_size - this->_tree.size());
			}

			void	swap(map& src)
			{
				this->_tree.swap(src._tree);
			}

			void	clear()
			{
				this->_tree.clear();
			}

			key_compare		key_comp() const
			{
				return (Compare());
			}

			value_compare	value_comp() const
			{
				return (value_compare(key_comp()));
			}

			iterator	find(const key_type& key)
			{
				return (iterator(this->_tree.find(ft::make_pair(key, mapped_type()))));
			}

			const_iterator	find(const key_type& key) const
			{
				return (const_iterator(this->_tree.find(ft::make_pair(key, mapped_type()))));
			}

			size_type	count(const key_type& key) const
			{
				if (_tree.exist(ft::make_pair(key, mapped_type())))
					return (1);
				return (0);
			}

			iterator	lower_bound(const key_type& key)
			{
				iterator it;

				it = begin();
				while (it != end() && it->first < key)
					it++;
				return (it);
			}

			const_iterator	lower_bound(const key_type& key) const
			{
				const_iterator	it;

				it = begin();
				while (it != end() && it->first < key)
					it++;
				return (it);
			}

			iterator	upper_bound(const key_type& key)
			{
				iterator it;

				it = begin();
				while (it != end() && it->first <= key)
					it++;
				return (it);
			}

			const_iterator	upper_bound(const key_type& key) const
			{
				const_iterator	it;

				it = begin();
				while (it != end() && it->first <= key)
					it++;
				return (it);
			}

			ft::pair<iterator, iterator>	equal_range(const key_type& key)
			{
				return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const
			{
				return (ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}

		// ##### Iterators #####
	// 		iterator	begin()
	// 		{
	// 			return (iterator(this->_tree.begin()));
	// 		}

	// 		const_iterator			begin() const
	// 		{
	// 			return (const_iterator(this->_tree.begin()));
	// 		}

	// 		iterator	end()
	// 		{
	// 			return (iterator(this->_tree.end()));
	// 		}

	// 		const_iterator	end() const
	// 		{
	// 			return (const_iterator(this->_tree.end()));
	// 		}

	// 		reverse_iterator	rbegin()
	// 		{
	// 			return (reverse_iterator(this->_tree.rbegin()));
	// 		}

	// 		const_reverse_iterator	rbegin() const
	// 		{
	// 			return (const_reverse_iterator(this->_tree.rbegin()));
	// 		}

	// 		reverse_iterator	rend()
	// 		{
	// 			return (reverse_iterator(this->_tree.rend()));
	// 		}

	// 		const_reverse_iterator	rend() const
	// 		{
	// 			return (const_reverse_iterator(this->_tree.rend()));
	// 		}
	};

// ##### non member functions #####
	template <typename Key, typename T, typename Compare>
		void swap(map<Key, T, Compare>& x, map<Key, T, Compare>& y)
		{
			x.swap(y);
		}

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
