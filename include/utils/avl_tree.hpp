/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:08:05 by tblaase           #+#    #+#             */
/*   Updated: 2022/05/12 10:07:57 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>

#include "bidirectional_iterator.hpp"
#include "rev_bidirectional_iterator.hpp"

namespace ft
{
	template <class T>
		class Node
		{
			public:
				typedef T		value_type;
				typedef Node*	node_ptr;

				value_type		data;
				node_ptr		parent;
				node_ptr		left;
				node_ptr		right;
				int				height;

				Node(void): parent(NULL), left(NULL), right(NULL), height(0) { }
				Node(const value_type &value): data(value), parent(NULL), left(NULL), right(NULL), height(0) { }
				Node(const Node& other): data(other.data), parent(other.parent), left(other.left), right(other.right), height(other.height) { }
				~Node() { }

				Node&	operator=(const Node& other)
				{
					this->data = other.data;
					this->parent = other.parent;
					this->right = other.right;
					this->left = other.left;
					this->height = other.height;

					return (*this);
				}
	};

	// template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<Node<T> > >
	// 	class avl_tree
	// {
	// 	public:
	// 		typedef	Node<T>													node;
	// 		typedef node*													node_ptr;
	// 		typedef T														value_type;
	// 		typedef Allocator												allocator_type;
	// 		typedef Compare													key_compare;
	// 		typedef key_compare												value_compare;
	// 		typedef Key														key_type;
	// 		typedef typename allocator_type::reference						reference;
	// 		typedef typename allocator_type::const_reference				const_reference;
	// 		typedef typename allocator_type::pointer						pointer;
	// 		typedef typename allocator_type::const_pointer					const_pointer;
	// 		typedef typename allocator_type::size_type						size_type;
	// 		typedef typename allocator_type::difference_type				difference_type;

	// 		typedef ft::bidirectional_iterator<Node<value_type> >			iterator;
	// 		typedef ft::bidirectional_iterator<Node<value_type> >			const_iterator;
	// 		typedef ft::rev_bidirectional_iterator<iterator>				reverse_iterator;
	// 		typedef ft::rev_bidirectional_iterator<const_iterator>			const_reverse_iterator;

	// 	private:
	// 		node_ptr		_end;
	// 		node_ptr		_root;
	// 		size_type		_size;
	// 		key_compare		_comp;
	// 		allocator_type	_alloc;

	// 	public:
	// 		explicit avl_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _size(0), _comp(comp), _alloc(alloc)
	// 			{
	// 			this->_end = this->_create_node(value_type());
	// 			this->_end->left = NULL;
	// 			this->_end->right = NULL;
	// 			this->_end->parent = NULL;
	// 		};

	// 		avl_tree(const avl_tree &src): _end(NULL), _root(NULL), _size(0), _comp(src._comp), _alloc(src._alloc)
	// 		{
	// 			const_iterator it = const_iterator(src.begin());
	// 			while (it != const_iterator(src.end()))
	// 			{
	// 				insert(*it);
	// 				++it;
	// 			}
	// 		}

	// 		~avl_tree()
	// 		{
	// 			if (this->size())
	// 				this->clear();
	// 			this->_alloc.deallocate(this->_end, 1);
	// 		}

	// 		avl_tree& operator=(const avl_tree &src)
	// 		{
	// 			if (this != &src) {
	// 				this->clear();
	// 				this->_size = 0;
	// 				this->_comp = src._comp;
	// 				this->_alloc = src._alloc;
	// 				this->_root = NULL;
	// 				const_iterator it = const_iterator(src.begin());
	// 				while (it != const_iterator(src.end()))
	// 				{
	// 					insert(*it);
	// 					++it;
	// 				}
	// 			}
	// 			return (*this);
	// 		}

	// 		node_ptr	begin()
	// 		{
	// 			return (this->_getMin(this->_root));
	// 		};

	// 		node_ptr	begin() const
	// 		{
	// 			return (this->_getMin(this->_root));
	// 		};

	// 		node_ptr	end()
	// 		{
	// 			return (this->_end);
	// 		}

	// 		node_ptr	end() const
	// 		{
	// 			return (this->_end);
	// 		}

	// 		node_ptr	rbegin()
	// 		{
	// 			return (this->_end);
	// 		};

	// 		node_ptr	rbegin() const
	// 		{
	// 			return (this->_end);
	// 		};

	// 		node_ptr	rend()
	// 		{
	// 			return (this->_getMin(this->_root));
	// 		};

	// 		node_ptr	rend() const
	// 		{
	// 			return (this->_getMin(this->_root));
	// 		};

	// 		bool	empty() const
	// 		{
	// 			return (this->_size == 0);
	// 		};

	// 		size_type	size() const
	// 		{
	// 			return (this->_size);
	// 		};

	// 		size_type	max_size() const
	// 		{
	// 			return (this->_alloc.max_size());
	// 		};

	// 		node_ptr	_initNode(value_type data)
	// 		{
	// 			node_ptr	node = this->_alloc.allocate(1);
	// 			this->_alloc.construct(node, data);
	// 			node->parent = NULL;
	// 			node->left = NULL;
	// 			node->right = NULL;
	// 			node->height = 1;
	// 			return (node);
	// 		};

	// 		node_ptr	getEnd() const
	// 		{
	// 			return (this->_end);
	// 		}

	// 		bool	equals(value_type const &first, value_type const &second) const
	// 		{
	// 			return (!_comp(first, second) && !_comp(second, first));
	// 		}

	// 		node	*search(node *root, const value_type &v) const
	// 		{
	// 			if (!root) {
	// 				return nullptr;
	// 			}
	// 			if (equals(root->data, v)) {
	// 				return root;
	// 			}
	// 			if (_comp(v, root->data) && root->left == nullptr) {
	// 				return root;
	// 			}
	// 			if (!_comp(v, root->data) && root->right == nullptr) {
	// 				return root;
	// 			}
	// 			if (!_comp(v, root->data)) {
	// 				return search(root->right, v);
	// 			}
	// 			return search(root->left, v);
	// 		}

	// 		ft::pair<iterator, bool>	insert(value_type val)
	// 		{
	// 			// this->_root = _addNode(this->_root, this->_root, val, val.first);
	// 			node	*z;

	// 			z = search(this->_root, val);
	// 			if (z && equals(val, z->data))
	// 				return ft::make_pair(iterator(z), false);
	// 				// return ;
	// 			z = _create_node(val);
	// 			this->_getMax(this->_root)->right = this->_end;
	// 			this->_end->parent = this->_getMax(this->_root);
	// 			this->_checkBalance(this->_root, val);

	// 			return ft::make_pair(iterator(z), true);
	// 		};

	// 		// node_ptr	insertWithHint(node_ptr position, value_type val)
	// 		// {
	// 		// 	node_ptr	ret = _addNode(position, position, val, val.first);
	// 		// 	if (this->_root->parent)
	// 		// 		this->_root = this->_root->parent;
	// 		// 	_addNode(this->_root, this->_root, val, val.first);
	// 		// 	this->_getMax(this->_root)->right = this->_end;
	// 		// 	this->_end->parent = this->_getMax(this->_root);
	// 		// 	return (_getSuccessor(ret));
	// 		// };

	// 		// bool	search(value_type key) const
	// 		// {
	// 		// 	return (this->_search(this->_root, key));
	// 		// };

	// 		node_ptr	find(value_type key) const
	// 		{
	// 			node_ptr	node;

	// 			node = _find(_root, key);
	// 			if (!node)
	// 				return (_end);
	// 			return (node);
	// 		};

	// 		node_ptr	exist(value_type key) const
	// 		{
	// 			node_ptr	node;

	// 			node = _find(_root, key);
	// 			return(node);
	// 		}

	// 		void	deleteNode(value_type key)
	// 		{
	// 			this->_root = this->_deleteNode(this->_root, key);
	// 		};

	// 		void	clear()
	// 		{
	// 			this->_deleteavl_tree(this->_root);
	// 			this->_end->parent = NULL;
	// 			this->_root = this->_end;
	// 			this->_size = 0;
	// 		};

	// 		node_ptr	lower_bound(key_type key) const
	// 		{
	// 			node_ptr	temp = this->_getMin(this->_root);
	// 			if (temp == NULL || temp == this->_end)
	// 				return (this->_end);
	// 			while (temp->data.first <= key)
	// 			{
	// 				if (key == temp->data.first)
	// 					break;
	// 				temp = this->_getSuccessor(temp);
	// 				if (temp == NULL || temp == this->_end)
	// 					return (this->_end);
	// 			}
	// 			return (temp);
	// 		}

	// 		node_ptr	upper_bound(key_type key) const
	// 		{
	// 			node_ptr	temp = this->_getMin(this->_root);
	// 			if (temp == NULL || temp == this->_end)
	// 				return (this->_end);
	// 			while (temp->data.first <= key)
	// 			{
	// 				temp = this->_getSuccessor(temp);
	// 				if (temp == NULL || temp == this->_end)
	// 					return (this->_end);
	// 			}
	// 			return (temp);
	// 		}

	// 		void	swap(avl_tree& x)
	// 		{
	// 			size_t			temp_size = x._size;
	// 			node_ptr		temp_root = x._root;
	// 			node_ptr		temp_end = x._end;
	// 			node_ptr		temp_alloc = x._alloc;
	// 			key_compare		temp_comp = x._comp;

	// 			x._size = this->_size;
	// 			x._root = this->_root;
	// 			x._end = this->_end;
	// 			x._alloc = this->_alloc;
	// 			x._comp = this->_comp;

	// 			this->_size = temp_size;
	// 			this->_root = temp_root;
	// 			this->_end = temp_end;
	// 			this->_alloc = temp_alloc;
	// 			this->_comp = temp_comp;
	// 		}

	// 	private:
	// 		node_ptr	_create_node(value_type value)
	// 		{
	// 			node_ptr	new_node;

	// 			new_node = _alloc.allocate(1);
	// 			_alloc.construct(new_node, value);
	// 			return (new_node);
	// 		}

	// 		void 		_copy(node_ptr copy, node_ptr copy_end)
	// 		{
	// 			if (!copy || copy == copy_end)
	// 				return ;
	// 			if (copy->left)
	// 				_copy(copy->left, copy_end);
	// 			if (copy->right)
	// 				_copy(copy->right, copy_end);
	// 			insert(copy->data);
	// 		}

	// 		void 		_cut_end_connections()
	// 		{
	// 			node_ptr	biggest;

	// 			biggest = _getMax(this->_root);
	// 			if (biggest)
	// 				biggest->right = NULL;
	// 			if (_end)
	// 				_end->parent = NULL;
	// 		}

	// 		int	_getHeight(node_ptr node) const
	// 		{
	// 			if (node == NULL || node == this->_end)
	// 				return (0);
	// 			return (node->height);
	// 		};

	// 		int	_getBalanceFactor(node_ptr node) const
	// 		{
	// 			if (node == NULL || node == this->_end)
	// 				return (0);
	// 			return (this->_getHeight(node->left) - this->_getHeight(node->right));
	// 		};

	// 		node_ptr	_getMax(node_ptr node) const
	// 		{
	// 			while (node->right != NULL && node->right != this->_end)
	// 				node = node->right;
	// 			return (node);
	// 		};

	// 		node_ptr	_getMin(node_ptr node) const
	// 		{
	// 			if (!node)
	// 				return (this->_end);
	// 			while (node->left != NULL && node != this->_end)
	// 				node = node->left;
	// 			return (node);
	// 		};

	// 		node_ptr	_rightRotate(node_ptr node)
	// 		{
	// 			node_ptr	temp = node->left;
	// 			node_ptr	temp2 = temp->right;

	// 			node->left = temp2;
	// 			if (node->left)
	// 				node->left->parent = node;
	// 			temp->right = node;
	// 			temp->parent = node->parent;
	// 			if (node->parent && node->parent != this->_end)
	// 			{
	// 				if (node == node->parent->right)
	// 					node->parent->right = temp;
	// 				else
	// 					node->parent->left = temp;
	// 			}
	// 			node->parent = temp;

	// 			node->height = std::max(this->_getHeight(node->left),
	// 				this->_getHeight(node->right)) + 1;
	// 			temp->height = std::max(this->_getHeight(temp->left),
	// 				this->_getHeight(temp->right)) + 1;
	// 			return (temp);
	// 		};

	// 		node_ptr	_leftRotate(node_ptr node)
	// 		{
	// 			node_ptr	temp = node->right;
	// 			node_ptr	temp2 = temp->left;

	// 			node->right = temp2;
	// 			if (node->right)
	// 				node->right->parent = node;
	// 			temp->left = node;
	// 			temp->parent = node->parent;
	// 			if (node->parent && node->parent != this->_end)
	// 			{
	// 				if (node == node->parent->right)
	// 					node->parent->right = temp;
	// 				else
	// 					node->parent->left = temp;
	// 			}
	// 			node->parent = temp;

	// 			node->height = std::max(this->_getHeight(node->left),
	// 				this->_getHeight(node->right)) + 1;
	// 			temp->height = std::max(this->_getHeight(temp->left),
	// 				this->_getHeight(temp->right)) + 1;
	// 			return (temp);
	// 		};

	// 		node_ptr	_checkBalance(node_ptr node, value_type key)
	// 		{
	// 			int	balanceFactor = this->_getBalanceFactor(node);
	// 			if (balanceFactor > 1)
	// 			{
	// 				if (this->_comp(key, node->left->data))
	// 					return (this->_rightRotate(node));
	// 				else
	// 				{
	// 					node->left = this->_leftRotate(node->left);
	// 					return (this->_rightRotate(node));
	// 				}
	// 			}
	// 			else if (balanceFactor < -1)
	// 			{
	// 				if (this->_comp(key, node->right->data))
	// 				{
	// 					node->right = this->_rightRotate(node->right);
	// 					return (this->_leftRotate(node));
	// 				}
	// 				else
	// 					return (this->_leftRotate(node));
	// 			}
	// 			return (node);
	// 		};

	// 		node_ptr	_reBalance(node_ptr node)
	// 		{
	// 			int balanceFactor = this->_getBalanceFactor(node);
	// 			if (balanceFactor > 1)
	// 			{
	// 				if (this->_getBalanceFactor(node->left) >= 0)
	// 					return (this->_rightRotate(node));
	// 				else
	// 				{
	// 					node->left = this->_leftRotate(node->left);
	// 					return (this->_rightRotate(node));
	// 				}
	// 			}
	// 			else if (balanceFactor < -1)
	// 			{
	// 				if (this->_getBalanceFactor(node->right) <= 0)
	// 					return (this->_leftRotate(node));
	// 				else
	// 				{
	// 					node->right = this->_rightRotate(node->right);
	// 					return (this->_leftRotate(node));
	// 				}
	// 			}
	// 			return (node);
	// 		};

	// 		void	_deleteavl_tree(node_ptr node)
	// 		{
	// 			if (node == NULL || node == this->_end)
	// 				return;
	// 			this->_deleteavl_tree(node->left);
	// 			this->_deleteavl_tree(node->right);
	// 			this->_alloc.destroy(node);
	// 			this->_alloc.deallocate(node, 1);
	// 			node = NULL;
	// 		}

	// 		node_ptr	_deleteNode(node_ptr node, value_type key)
	// 		{
	// 			if (node == NULL || node == this->_end)
	// 				return (node);
	// 			if (this->_comp(key, node->data))
	// 				node->left = this->_deleteNode(node->left, key);
	// 			else if (this->_comp(node->data, key))
	// 				node->right = this->_deleteNode(node->right, key);
	// 			else
	// 			{
	// 				if (node->left == NULL && node->right == NULL)
	// 				{
	// 					this->_alloc.destroy(node);
	// 					this->_alloc.deallocate(node, 1);
	// 					this->_size--;
	// 					node = NULL;
	// 				}
	// 				else if (node->left == NULL)
	// 				{
	// 					node_ptr	temp = node;
	// 					node = node->right;
	// 					if (node)
	// 						node->parent = temp->parent;
	// 					this->_alloc.destroy(temp);
	// 					this->_alloc.deallocate(temp, 1);
	// 					this->_size--;
	// 					temp = NULL;
	// 				}
	// 				else if (node->right == NULL)
	// 				{
	// 					node_ptr	temp = node;
	// 					node = node->left;
	// 					if (node)
	// 						node->parent = temp->parent;
	// 					this->_alloc.destroy(temp);
	// 					this->_alloc.deallocate(temp, 1);
	// 					this->_size--;
	// 					temp = NULL;
	// 				}
	// 				else
	// 				{
	// 					node_ptr	temp = this->_getMin(node->right);
	// 					node_ptr	newNode = _initNode(temp->data);
	// 					newNode->parent = node->parent;
	// 					if (node->parent)
	// 					{
	// 						if (node == node->parent->right)
	// 							node->parent->right = newNode;
	// 						else
	// 							node->parent->left = newNode;
	// 					}
	// 					newNode->left = node->left;
	// 					node->left->parent = newNode;
	// 					newNode->right = this->_deleteNode(node->right, temp->data);
	// 					if (newNode->right)
	// 						newNode->right->parent = newNode;
	// 					node = newNode;
	// 				}
	// 			}
	// 			if (node == NULL)
	// 				return (node);
	// 			node->height = 1 + std::max(this->_getHeight(node->left), this->_getHeight(node->right));
	// 			return (this->_reBalance(node));
	// 		};

	// 		node_ptr	_find(node_ptr node, value_type key) const
	// 		{
	// 			if (!node)
	// 				return (NULL);
	// 			else if (_comp(key, node->data) && !_comp(node->data, key))
	// 				return (_find(node->left, key));
	// 			else if (!_comp(key, node->data) && _comp(node->data, key))
	// 				return (_find(node->right, key));
	// 			return (node);
	// 		}

	// 		// bool	_search(node_ptr node, key_type key) const
	// 		// {
	// 		// 	if (node == NULL || node == this->_end)
	// 		// 		return (false);
	// 		// 	else if (this->_comp(key, node->data) && !this->_comp(node->data, key))
	// 		// 		return (this->_search(node->left, key));
	// 		// 	if (this->_comp(key, node->data) && !this->_comp(node->data, key))
	// 		// 		return (this->_search(node->right, key));
	// 		// 	else
	// 		// 		return (true);
	// 		// };
	// 		// bool	_search(node_ptr node, value_type key) const
	// 		// {
	// 		// 	if (!node)
	// 		// 		return (false);
	// 		// 	else if (this->_find(node, key))
	// 		// 		return (true);
	// 		// 	return (false);
	// 		// }

	// 		node_ptr	_addNode(node_ptr node, node_ptr parent, value_type val, key_type key)
	// 		{
	// 			if (node == NULL || node == this->_end)
	// 			{
	// 				node_ptr	ret = this->_initNode(val);
	// 				if (parent != this->_end)
	// 					ret->parent = parent;
	// 				this->_size++;
	// 				return (ret);
	// 			}
	// 			if (this->_comp(val, node->data) && !this->_comp(node->data, val))
	// 				node->left = this->_addNode(node->left, node, val, key);
	// 			else if (this->_comp(node->data, val) && !this->_comp(val, node->data))
	// 				node->right = this->_addNode(node->right, node, val, key);
	// 			else
	// 				return (node);
	// 			node->height = 1 + std::max(this->_getHeight(node->left), this->_getHeight(node->right));
	// 			return (this->_checkBalance(node, val));
	// 		};
	// };

	// template <class node_ptr>
	// 	node_ptr	_getMin(node_ptr node)
	// 	{
	// 		while (node->left != NULL)
	// 			node = node->left;
	// 		return (node);
	// 	};

	// template <class node_ptr>
	// 	node_ptr	_getMax(node_ptr node)
	// 	{
	// 		while (node->right != NULL)
	// 			node = node->right;
	// 		return (node);
	// 	};

	// template <class node_ptr>
	// 	node_ptr	_getSuccessor(node_ptr node)
	// 	{
	// 		if (node->right)
	// 			return (_getMin(node->right));
	// 		node_ptr	temp = node->parent;
	// 		while (temp && node == temp->right)
	// 		{
	// 			node = temp;
	// 			temp = temp->parent;
	// 		}
	// 		return (temp);
	// 	};

	// template <class node_ptr>
	// 	node_ptr	_getPredecessor(node_ptr node)
	// 	{
	// 		if (node->left)
	// 			return (_getMax(node->left));
	// 		node_ptr	temp = node->parent;
	// 		while (temp && node == temp->left)
	// 		{
	// 			node = temp;
	// 			temp = temp->parent;
	// 		}
	// 		return (temp);
	// 	};
	// }

	// this will be the new implementation of the avl_tree

	// the actual avl-tree
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<Node<T> > >
		class avl_tree
	{
		public:
			typedef	Node<T>													node;
			typedef node*													node_ptr;
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef Compare													key_compare;
			typedef key_compare												value_compare;
			typedef Key														key_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename allocator_type::difference_type				difference_type;

			typedef ft::bidirectional_iterator<Node<value_type> >			iterator;
			typedef ft::bidirectional_iterator<Node<value_type> >			const_iterator;
			typedef ft::rev_bidirectional_iterator<iterator>				reverse_iterator;
			typedef ft::rev_bidirectional_iterator<const_iterator>			const_reverse_iterator;

		private:
			node_ptr		_end;
			node_ptr		_root;
			size_type		_size;
			key_compare		_comp;
			allocator_type	_alloc;
		public:
			explicit avl_tree(const key_compare& comp, const allocator_type& alloc = allocator_type()): _root(NULL), _size(0), _comp(comp), _alloc(alloc)
				{
				this->_end = this->_create_node(value_type());
				this->_end->left = NULL;
				this->_end->right = NULL;
				this->_end->parent = NULL;
			};

			avl_tree(const avl_tree &src): _end(NULL), _root(NULL), _size(0), _comp(src._comp), _alloc(src._alloc)
			{
				*this = src;
			}

			~avl_tree()
			{
				if (this->size())
					this->clear();
				this->_alloc.destroy(this->_end);
				this->_alloc.deallocate(this->_end, 1);
				this->_end = NULL;
			}

			avl_tree& operator=(const avl_tree &src)
			{
				if (this != &src) {
					this->clear();
					this->_size = 0;
					this->_comp = src._comp;
					this->_alloc = src._alloc;
					this->_root = NULL;
					const_iterator it = const_iterator(src.get_lowest());
					while (it != const_iterator(src.get_biggest()))
					{
						insert((*it));
						++it;
					}
				}
				return (*this);
			}

			void	swap(avl_tree& x)
			{
				size_t			temp_size = x._size;
				node_ptr		temp_root = x._root;
				node_ptr		temp_end = x._end;
				node_ptr		temp_alloc = x._alloc;
				key_compare		temp_comp = x._comp;

				x._size = this->_size;
				x._root = this->_root;
				x._end = this->_end;
				x._alloc = this->_alloc;
				x._comp = this->_comp;

				this->_size = temp_size;
				this->_root = temp_root;
				this->_end = temp_end;
				this->_alloc = temp_alloc;
				this->_comp = temp_comp;
			}

			size_type size() const
			{
				return (this->_size);
			}

			node_ptr	get_end() const
			{
				return(this->_end);
			}

			node_ptr	get_lowest() const
			{
				node_ptr	res = this->_root;

				if (!res)
					return (this->_end);
				while (res->left)
					res = res->left;
				return (res);
			}

			node_ptr	get_biggest() const
			{
				node_ptr	res = this->_root;

				if (!res)
					return (NULL);
				while (res->right && res->right != this->_end)
					res = res->right;
				return (res);
			}

			void	clear()
			{
				this->_deleteavl_tree(this->_root);
				this->_end->parent = NULL;
				this->_root = this->_end;
				this->_size = 0;
			};

			void		erase(value_type key)
			{
				node_ptr	node_to_delete;

				node_to_delete = this->exist(key);
				if (!node_to_delete)
					return ;
				else if (_size == 1)
					this->_root = NULL;
				else
				{
					this->_deleteNode(this->_root, key);
				}
				this->_alloc.destroy(node_to_delete);
				this->_alloc.deallocate(node_to_delete, 1);
				this->_size--;
				this->_connect_end();
			}

			node_ptr	_get_successor(node_ptr node)
			{
				node_ptr	res;

				res = node->right;
				while (res->left)
					res = res->left;
				return(res);
			}

			void	_deleteavl_tree(node_ptr node)
			{
				if (node == NULL || node == this->_end)
					return;
				this->_deleteavl_tree(node->left);
				this->_deleteavl_tree(node->right);
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
				node = NULL;
			}

			void 		_cut_end_connections()
			{
				node_ptr	biggest;

				biggest = this->get_biggest();
				if (biggest)
					biggest->right = NULL;
				if (this->_end)
					this->_end->parent = NULL;
			}
			void 		_connect_end()
			{
				node_ptr	biggest;

				biggest = get_biggest();
				if (biggest)
					biggest->right = this->_end;
				if (!this->_end)
					this->_end = this->newNode(value_type());
				this->_end->parent = biggest;
			}


			// A utility function to get maximum
			// of two integers
			int max(int a, int b)
			{
				return (a > b)? a : b;
			}

			node_ptr	exist(value_type key) const
			{
				node_ptr	node;

				node = _find(this->_root, key);
				return(node);
			}

			node_ptr	find(value_type key) const
			{
				node_ptr	node;

				node = _find(this->_root, key);
				if (!node)
					return (this->_end);
				return (node);
			};

			node_ptr	_find(node_ptr node, value_type key) const
			{
				if (!node)
					return (NULL);
				else if (this->_comp(key, node->data) && !this->_comp(node->data, key))
					return (this->_find(node->left, key));
				else if (!this->_comp(key, node->data) && this->_comp(node->data, key))
					return (this->_find(node->right, key));
				return (node);
			}

			// A utility function to get the
			// height of the tree
			int height(node_ptr N)
			{
				if (N == NULL)
					return 0;
				return N->height;
			}

			/* Helper function that allocates a
			new node with the given val and
			NULL left and right pointers. */
			node_ptr newNode(value_type val)
			{
				node_ptr node = this->_create_node(val);
				// node->val = val;
				node->left = NULL;
				node->right = NULL;
				node->height = 1; // new node is initially
								// added at leaf
				return(node);
			}

			node_ptr	_create_node(value_type value)
			{
				node_ptr	new_node;

				new_node = this->_alloc.allocate(1);
				this->_alloc.construct(new_node, value);
				return (new_node);
			}

			// A utility function to right
			// rotate subtree rooted with y
			// See the diagram given above.
			node_ptr rightRotate(node_ptr y)
			{
				node_ptr x = y->left;
				node_ptr T2 = x->right;

				// Perform rotation
				x->right = y;
				y->left = T2;

				// Update heights
				y->height = this->max(this->height(y->left), this->height(y->right)) + 1;
				x->height = this->max(this->height(x->left), this->height(x->right)) + 1;

				// Return new root
				return x;
			}

			// A utility function to left
			// rotate subtree rooted with x
			// See the diagram given above.
			node_ptr leftRotate(node_ptr x)
			{
				node_ptr y = x->right;
				node_ptr T2 = y->left;

				// Perform rotation
				y->left = x;
				x->right = T2;

				// Update heights
				x->height = this->max(this->height(x->left), this->height(x->right)) + 1;
				y->height = this->max(this->height(y->left), this->height(y->right)) + 1;

				// Return new root
				return y;
			}

			// Get Balance factor of node N
			int getBalance(node_ptr N)
			{
				if (N == NULL)
					return 0;
				return this->height(N->left) - this->height(N->right);
			}


			ft::pair<node_ptr, bool>	insert(value_type val)
			{
				node_ptr					exists;
				node_ptr					new_node;
				ft::pair<node_ptr, bool>	res;

				exists = this->exist(val);
				if (exists)
				 	return (ft::make_pair(exists, false));
				new_node = this->_create_node(val);
				if (!this->_root)
				{
					this->_root = new_node;
					++this->_size;
					this->_connect_end();
					return (ft::make_pair(new_node, true));
				}
				this->_cut_end_connections();
				res = _insert(this->_root, new_node);
				++this->_size;
				this->_connect_end();
				return (res);
			}

			ft::pair<node_ptr, bool>	_insert(node_ptr parent, node_ptr new_node)
			{
				if (this->_comp(parent->data, new_node->data))
				{
					if (!parent->right)
					{
						parent->right = new_node;
						new_node->parent = parent;
						// new_node->is_left = 0;
					}
					else
						this->_insert(parent->right, new_node);
				}
				else
				{
					if (!parent->left)
					{
						parent->left = new_node;
						new_node->parent = parent;
						// new_node->is_left = 1;
					}
					else
						this->_insert(parent->left, new_node);
				}
				// _check_color(new_node);
				this->_root = this->_balance(new_node, new_node->data);

				return (ft::make_pair(new_node, true));
			}

			node_ptr _balance(node_ptr node, value_type val)
			{
				int balance = this->getBalance(node);

				// If this node becomes unbalanced, then
				// there are 4 cases

				// Left Left Case
				// if (balance > 1 && val < node->left->data)
				if (balance > 1 && this->_comp(val, node->left->data))
					return this->rightRotate(node);

				// Right Right Case
				// if (balance < -1 && val > node->right->data)
				if (balance < -1 && !this->_comp(val, node->right->data))
					return this->leftRotate(node);

				// Left Right Case
				// if (balance > 1 && val > node->left->data)
				if (balance > 1 && !this->_comp(val, node->left->data))
				{
					node->left = this->leftRotate(node->left);
					return this->rightRotate(node);
				}

				// Right Left Case
				// if (balance < -1 && val < node->right->data)
				if (balance < -1 && this->_comp(val, node->right->data))
				{
					node->right = this->rightRotate(node->right);
					return this->leftRotate(node);
				}
				/* return the (unchanged) node pointer */
				return node;
			}
			// Recursive function to insert a val
			// in the subtree rooted with node and
			// returns the new root of the subtree.
			node_ptr _insert(node_ptr node, value_type val)
			{
				/* 1. Perform the normal BST insertion */
				if (node == NULL)
					return(this->newNode(val));

				// if (val < node->data.first)
				// 	node->left = _insert(node->left, val);
				// else if (val > node->data.first)
				// 	node->right = _insert(node->right, val);
				// else // Equal keys are not allowed in BST
				// 	return node;

				/* 2. Update height of this ancestor node */
				node->height = 1 + this->max(this->height(node->left), this->height(node->right));

				/* 3. Get the balance factor of this ancestor
					node to check whether this node became
					unbalanced */
				// int balance = getBalance(node);

				// // If this node becomes unbalanced, then
				// // there are 4 cases

				// // Left Left Case
				// if (balance > 1 && val < node->left->data)
				// 	return rightRotate(node);

				// // Right Right Case
				// if (balance < -1 && val > node->right->data)
				// 	return leftRotate(node);

				// // Left Right Case
				// if (balance > 1 && val > node->left->data)
				// {
				// 	node->left = leftRotate(node->left);
				// 	return rightRotate(node);
				// }

				// // Right Left Case
				// if (balance < -1 && val < node->right->data)
				// {
				// 	node->right = rightRotate(node->right);
				// 	return leftRotate(node);
				// }
				return (this->_balance(node, val));
			}

			/* Given a non-empty binary search tree,
			return the node with minimum key value
			found in that tree. Note that the entire
			tree does not need to be searched. */
			node_ptr  minValueNode(node_ptr node)
			{
				node_ptr current = node;

				/* loop down to find the leftmost leaf */
				while (current->left != NULL)
					current = current->left;

				return current;
			}

			// Recursive function to delete a node
			// with given key from subtree with
			// given root. It returns root of the
			// modified subtree.
			node_ptr _deleteNode(node_ptr root, value_type val)
			{

				// STEP 1: PERFORM STANDARD BST DELETE
				if (root == NULL)
					return (root);

				// If the key to be deleted is smaller
				// than the root's key, then it lies
				// in left subtree
				if (val < root->data)
					root->left = this->_deleteNode(root->left, val);

				// If the key to be deleted is greater
				// than the root's key, then it lies
				// in right subtree
				else if(val > root->data)
					root->right = this->_deleteNode(root->right, val);

				// if key is same as root's key, then
				// This is the node to be deleted
				else
				{
					// node with only one child or no child
					if( (root->left == NULL) ||
						(root->right == NULL) )
					{
						node_ptr temp = root->left ?root->left : root->right;

						// No child case
						if (temp == NULL)
						{
							temp = root;
							root = NULL;
						}
						else // One child case
						root = temp; // Copy the contents of
									// the non-empty child
						// free(temp);
						this->_alloc.destroy(temp);
						this->_alloc.deallocate(temp, 1);
					}
					else
					{
						// node with two children: Get the inorder
						// successor (smallest in the right subtree)
						// node_ptr temp = minValueNode(root->right);
						node_ptr temp = this->minValueNode(root->right);

						// Copy the inorder successor's
						// data to this node
						root->data = temp->data;

						// Delete the inorder successor
						root->right = this->_deleteNode(root->right, temp->data);
					}
				}

				// If the tree had only one node
				// then return
				if (root == NULL)
					return (root);

				// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
				root->height = 1 + this->max(this->height(root->left), this->height(root->right));

				// STEP 3: GET THE BALANCE FACTOR OF
				// THIS NODE (to check whether this
				// node became unbalanced)
				int balance = this->getBalance(root);

				// If this node becomes unbalanced,
				// then there are 4 cases

				// Left Left Case
				if (balance > 1 && this->getBalance(root->left) >= 0)
					return (this->rightRotate(root));

				// Left Right Case
				if (balance > 1 && this->getBalance(root->left) < 0)
				{
					root->left = this->leftRotate(root->left);
					return (this->rightRotate(root));
				}

				// Right Right Case
				if (balance < -1 && this->getBalance(root->right) <= 0)
					return (this->leftRotate(root));

				// Right Left Case
				if (balance < -1 && this->getBalance(root->right) > 0)
				{
					root->right = this->rightRotate(root->right);
					return (this->leftRotate(root));
				}

				return (root);
			}

			// A utility function to print preorder
			// traversal of the tree.
			// The function also prints height
			// of every node
			// void preOrder(node_ptr root)
			// {
			// 	if(root != NULL)
			// 	{
			// 		std::cout << root->val << " ";
			// 		preOrder(root->left);
			// 		preOrder(root->right);
			// 	}
			// }
	};
}