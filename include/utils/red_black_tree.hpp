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

# define RED 1
# define BLACK 0

namespace ft {
// a single node used by map to create a tree from
	template <class T>
	class Node
	{
		public:
			typedef T		value_type;
			typedef Node*	node_ptr;

			bool			is_left;
			bool			color;
			value_type		value;
			node_ptr		parent;
			node_ptr		left;
			node_ptr		right;

			Node(void): is_left(0), color(BLACK), parent(NULL), left(NULL), right(NULL) { }
			Node(const value_type &value): is_left(0), color(RED), value(value), parent(NULL), left(NULL), right(NULL) { }
			Node(const Node& src): is_left(src.is_left), color(src.color), value(src.value), parent(src.parent), left(src.left), right(src.right) { }
			~Node() { }

			Node&	operator=(const Node& src)
			{
				value = src.value;
				parent = src.parent;
				right = src.right;
				left = src.left;
				color = src.color;
				is_left = src.is_left;

				return (*this);
			}

			node_ptr	get_uncle()
			{
				if (parent == NULL)
					return (NULL);
				else if (this->parent->is_left)
					return (this->parent->parent->right);
				else
					return (this->parent->parent->left);
			}
	};
// the red-black-tree itself

// RED BLACK TREE RULES

// 	1. Every node is red or black
// 	2. Root is always black
// 	3. New insertions are always red
// 	4. Every path from root - leaf(NULL) has the same number of BLACK nodes
// 	5. No path can have two consecutice RED nodes
// 	6. NULLs are black
// 	7. Every node has two children

// Example tree to understand the child - parent - uncle relationship
//
// 				_root
// 			/			\.
// 		left			right
// 		/	\			/	\.
//	l1		r1		l2		r2
//
// root has two children: left and right
// the parent of l1 and r1 is left
// the uncle of l1 and r1 is right


// 		Rules for fixing an invalid red-black-tree

// 1. If we have BLACK uncle - rotate
// 	- if imbalance is in right child and right subtree - left rotation
// 	- if imbalance is in right child and left subtree - right/left rotation
// 	- if imbalance is in left child and right subtree - left/right rotation
// 	- if imbalance is in left child and left subtree - right rotation
// 2. If we have RED uncle - color flip
// 3. After rotation working nodes should look like: parent - black, childrens - red
// 4. After color flip working nodes should look like: parent - red, childrens - black

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<Node<T> > >
	class red_black_tree
	{
		public:
			typedef	Node<T>													node;
			typedef node*													node_ptr;
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef Compare													key_compare;
			typedef key_compare												value_compare;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename allocator_type::difference_type				difference_type;

		private:
			node_ptr		_end;
			node_ptr		_root;
			size_type		_size;
			key_compare		_cmp;
			allocator_type	_alloc;

		// private helper functions
			node_ptr	_create_node(value_type value)
			{
				node_ptr	new_node = this->_alloc.allocate(1);
				this->_alloc.construct(new_node, value);

				return (new_node);
			}

			void	_clear(node_ptr node_to_delete)
			{
				if (!node_to_delete)
					return ;
				if (node_to_delete->left)
					this->_clear(node_to_delete->left);
				if (node_to_delete->right)
					this->_clear(node_to_delete->right);
				this->_alloc.destroy(node_to_delete);
				this->_alloc.deallocate(node_to_delete, 1);
				node_to_delete = NULL;
			}

			void	_copy(node_ptr copy, node_ptr copy_end)
			{
				if (!copy || copy == copy_end)
					return ;
				if (copy->left)
					this->_copy(copy->left, copy_end);
				if (copy->right)
					this->_copy(copy->right, copy_end);
				this->insert(copy->value);
			}

			node_ptr	_find(node_ptr node, value_type key) const
			{
				if (!node)
					return (NULL);
				else if (this->_cmp(key, node->value) && !this->_cmp(node->value, key))
					return (this->_find(node->left, key));
				else if (!this->_cmp(key, node->value) && this->_cmp(node->value, key))
					return (this->_find(node->right, key));
				return (node);
			}

			void	_remove_end()
			{
				node_ptr	biggest = this->get_biggest();
				if (biggest)
					biggest->right = NULL;
				if (this->_end)
					this->_end->parent = NULL;
			}

			void	_connect_end()
			{
				node_ptr	biggest = get_biggest();
				if (biggest)
					biggest->right = this->_end;
				if (!this->_end)
					this->_end = this->_create_node(value_type());
				this->_end->parent = biggest;
			}

		// all the possible rotations of the tree
			void	_left_right_rotation(node_ptr node_to_fix)
			{
				this->_left_rotation(node_to_fix->left);
				this->_right_rotation(node_to_fix);
			}

			void	_right_left_rotation(node_ptr node_to_fix)
			{
				this->_right_rotation(node_to_fix->right);
				this->_left_rotation(node_to_fix);
			}

			void	_left_rotation(node_ptr node_to_fix)
			{
				node_ptr	tmp = node_to_fix->right;
				node_to_fix->right = tmp->left;
				if (node_to_fix->right)
				{
					node_to_fix->right->parent = node_to_fix;
					node_to_fix->right->is_left = 0;
				}
				if (!node_to_fix->parent)
				{
					this->_root = tmp;
					tmp->parent = NULL;
				}
				else
				{
					tmp->parent = node_to_fix->parent;
					if (node_to_fix->is_left)
					{
						tmp->is_left = 1;
						tmp->parent->left = tmp;
					}
					else
					{
						tmp->is_left = 0;
						tmp->parent->right = tmp;
					}
				}
				tmp->left = node_to_fix;
				node_to_fix->is_left = 1;
				node_to_fix->parent = tmp;
			}

			void	_right_rotation(node_ptr node_to_fix)
			{
				node_ptr	tmp = node_to_fix->left;
				node_to_fix->left = tmp->right;
				if (node_to_fix->left)
				{
					node_to_fix->left->parent = node_to_fix;
					node_to_fix->left->is_left = 1;
				}
				if (!node_to_fix->parent)
				{
					this->_root = tmp;
					tmp->parent = NULL;
				}
				else
				{
					tmp->parent = node_to_fix->parent;
					if (node_to_fix->is_left)
					{
						tmp->is_left = 1;
						tmp->parent->left = tmp;
					}
					else
					{
						tmp->is_left = 0;
						tmp->parent->right = tmp;
					}
				}
				tmp->right = node_to_fix;
				node_to_fix->is_left = 0;
				node_to_fix->parent = tmp;
			}

			void	_rotate(node_ptr node_to_fix)
			{
				if (node_to_fix->is_left && node_to_fix->parent->is_left)
				{
					this->_right_rotation(node_to_fix->parent->parent);
					node_to_fix->color = RED;
					node_to_fix->parent->color = BLACK;
					if (node_to_fix->parent->right)
						node_to_fix->parent->right->color = RED;
				}
				else if (!node_to_fix->is_left && !node_to_fix->parent->is_left)
				{
					this->_left_rotation(node_to_fix->parent->parent);
					node_to_fix->color = RED;
					node_to_fix->parent->color = BLACK;
					if (node_to_fix->parent->left)
						node_to_fix->parent->left->color = RED;
				}
				else if (!node_to_fix->is_left && node_to_fix->parent->is_left)
				{
					this->_left_right_rotation(node_to_fix->parent->parent);
					node_to_fix->color = BLACK;
					node_to_fix->right->color = RED;
					node_to_fix->left->color = RED;
				}
				else
				{
					this->_right_left_rotation(node_to_fix->parent->parent);
					node_to_fix->color = BLACK;
					node_to_fix->right->color = RED;
					node_to_fix->left->color = RED;
				}
			}

		// insert helpers
			void	_color_flip(node_ptr node_to_fix)
			{
				node_to_fix->parent->color = BLACK;
				node_to_fix->parent->parent->color = RED;
				node_to_fix->get_uncle()->color = BLACK;
			}

			void	_check_color(node_ptr new_node)
			{
				if (!new_node)
					return ;
				if (new_node == _root)
				{
					new_node->color = BLACK;
					return ;
				}
				if (new_node->color == RED && new_node->parent->color == RED)
					this->_insert_balance(new_node);
				this->_check_color(new_node->parent);
			}

			void	_insert_balance(node_ptr node_to_fix)
			{
				if (node_to_fix->get_uncle() && node_to_fix->get_uncle()->color == RED)
					this->_color_flip(node_to_fix);
				else
					this->_rotate(node_to_fix);
			}

			ft::pair<node_ptr, bool>	_insert(node_ptr parent, node_ptr new_node)
			{
				if (this->_cmp(parent->value, new_node->value))
				{
					if (!parent->right)
					{
						parent->right = new_node;
						new_node->parent = parent;
						new_node->is_left = 0;
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
						new_node->is_left = 1;
					}
					else
						this->_insert(parent->left, new_node);
				}
				this->_check_color(new_node);
				return (ft::make_pair(new_node, true));
			}
		// erase helpers
			void	_assign(node_ptr parent, node_ptr to, bool is_left)
			{
				if (is_left)
					parent->left = to;
				else
					parent->right = to;
				if (to)
					to->is_left = is_left;
			}

			node_ptr	_replace(node_ptr node_to_delete, node_ptr replacement)
			{
				if (node_to_delete == _root)
				{
					this->_root = replacement;
					this->_root->parent = NULL;
					this->_root->color = BLACK;
				}
				else
				{
					if (node_to_delete->is_left)
						this->_assign(node_to_delete->parent, replacement, 1);
					else
						this->_assign(node_to_delete->parent, replacement, 0);
					if (replacement && replacement->parent)
						replacement->parent = node_to_delete->parent;
				}
				return (replacement);
			}

			node_ptr	_get_successor(node_ptr node)
			{
				node_ptr	res = node->right;
				while (res->left)
					res = res->left;
				return(res);
			}

			void	_fix_case_1(node_ptr parent, bool is_left)
			{
				parent->color = RED;
				if (is_left)
				{
					parent->right->color = BLACK;
					this->_left_rotation(parent);
				}
				else
				{
					parent->left->color = BLACK;
					this->_right_rotation(parent);
				}
				this->_get_sibling(parent, is_left);
			}

			void	_fix_case_2(node_ptr parent, bool is_left)
			{
				if (is_left)
					parent->right->color = RED;
				else
					parent->left->color = RED;
				if (parent->color == RED)
					parent->color = BLACK;
				else if (parent->color == BLACK && parent == _root)
					return ;
				else
					this->_get_sibling(parent->parent, parent->is_left);
			}

			void	_fix_case_3(node_ptr parent, bool is_left)
			{
				if (is_left)
				{
					if (parent->right->left)
						parent->right->left->color = BLACK;
					parent->right->color = RED;
					this->_right_rotation(parent->right);
				}
				else
				{
					if (parent->left->right)
						parent->left->right->color = BLACK;
					parent->left->color = RED;
					this->_left_rotation(parent->left);
				}
				this->_fix_case_4(parent, is_left);
			}

			void	_fix_case_4(node_ptr parent, bool is_left)
			{
				if (is_left)
				{
					parent->right->color = parent->color;
					parent->color = BLACK;
					if (parent->right->right)
						parent->right->right->color = BLACK;
					this->_left_rotation(parent);
				}
				else
				{
					parent->left->color = parent->color;
					parent->color = BLACK;
					if (parent->left->left)
						parent->left->left->color = BLACK;
					this->_right_rotation(parent);
				}
			}

			void	_erase_fix(node_ptr parent, node_ptr sibling, node_ptr x, bool is_left)
			{
				if (x && x->color == RED)
					x->color = BLACK;
				else if (sibling && sibling->color == RED)
					this->_fix_case_1(parent, is_left);
				else if (sibling && sibling->color == BLACK
						&& (!sibling->right || (sibling->right && sibling->right->color == BLACK))
						&& (!sibling->left || (sibling->left && sibling->left->color == BLACK)))
					this->_fix_case_2(parent, is_left);
				else if (sibling && sibling->color == BLACK
						&& ((is_left && sibling->left && sibling->left->color == RED
						&& (!sibling->right || (sibling->right && sibling->right->color == BLACK)))
						|| (!is_left && sibling->right && sibling->right->color == RED
						&& (!sibling->left || (sibling->left && sibling->left->color == BLACK)))))
					this->_fix_case_3(parent, is_left);
				else if (sibling && sibling->color == BLACK
						&& ((is_left && sibling->right && sibling->right->color == RED)
						|| (!is_left && sibling->left && sibling->left->color == RED)))
					this->_fix_case_4(parent, is_left);
			}

			void	_get_sibling(node_ptr parent, bool is_left)
			{
				if (is_left)
					this->_erase_fix(parent, parent->right, parent->left, is_left);
				else
					this->_erase_fix(parent, parent->left, parent->right, is_left);
			}

			void	_erase_balance(node_ptr node_to_delete, node_ptr replacement, node_ptr parent, bool is_left)
			{
				node_ptr	x;

				if (is_left)
					x = parent->left;
				else
					x = parent->right;
				if (node_to_delete->color == RED
					&& (!replacement || (replacement && replacement->color == RED)))
					return ;
				else if (node_to_delete->color == RED && replacement && replacement->color == BLACK)
				{
					replacement->color = RED;
					this->_get_sibling(parent, is_left);
				}
				else if (node_to_delete->color == BLACK && replacement && replacement->color == RED)
					replacement->color = BLACK;
				else if (node_to_delete->color == BLACK
						&& (!replacement || (replacement && replacement->color == BLACK)) && x == _root)
					return ;
				else if (node_to_delete->color == BLACK
						&& (!replacement || (replacement && replacement->color == BLACK)) && x != _root)
					this->_get_sibling(parent, is_left);
			}

			void	_child_is_null(node_ptr node_to_delete)
			{
				bool		is_left;
				node_ptr	parent = NULL;
				node_ptr	replacement;

				if (!node_to_delete->left && !node_to_delete->right)
				{
					replacement = this->_replace(node_to_delete, NULL);
					parent = node_to_delete->parent;
					is_left = node_to_delete->is_left;
				}
				else if (!node_to_delete->right)
				{
					replacement = this->_replace(node_to_delete, node_to_delete->left);
					parent = replacement->parent;
					is_left = 1;
				}
				else if (!node_to_delete->left)
				{
					replacement = this->_replace(node_to_delete, node_to_delete->right);
					parent = replacement->parent;
					is_left = 0;
				}
				if (!parent)
					return ;
				this->_erase_balance(node_to_delete, replacement, parent, is_left);
			}

			void 	_both_child_exist(node_ptr node_to_delete)
			{
				bool		is_left;
				node_ptr	parent;
				node_ptr	replacement = this->_get_successor(node_to_delete);
				if (replacement == node_to_delete->right)
				{
					this->_replace(node_to_delete, replacement);
					replacement->left = node_to_delete->left;
					replacement->left->parent = replacement;
					parent = replacement;
					is_left = 0;
				}
				else
				{
					parent = replacement->parent;
					is_left = replacement->is_left;
					this->_replace(replacement, replacement->right);
					this->_replace(node_to_delete, replacement);
					replacement->left = node_to_delete->left;
					replacement->right = node_to_delete->right;
					replacement->left->parent = replacement;
					replacement->right->parent = replacement;
				}
				this->_erase_balance(node_to_delete, replacement, parent, is_left);
			}

			void	_erase(node_ptr node_to_delete)
			{
				if (!node_to_delete->right || !node_to_delete->left)
					this->_child_is_null(node_to_delete);
				else
					this->_both_child_exist(node_to_delete);
			}

		public:
		// empty constructor
			explicit red_black_tree(const key_compare& cmp, const allocator_type& alloc = allocator_type()): _root(NULL), _size(0), _cmp(cmp), _alloc(alloc)
			{
				this->_end = this->_create_node(value_type());
				this->_end->left = NULL;
				this->_end->right = NULL;
				this->_end->parent = NULL;
				this->_end->is_left = 0;
				this->_end->color = 0;
			}
		// copy constructor
			red_black_tree(const red_black_tree& src): _end(NULL), _root(NULL), _cmp(src._cmp), _alloc(src._alloc)
			{
				*this = src;
			}

		// assignation operator overload
			red_black_tree&	operator=(const red_black_tree& src)
			{
				this->clear();
				this->_cmp = src._cmp;
				this->_alloc = src._alloc;
				this->_remove_end();
				this->_copy(src._root, src._end);

				return (*this);
			}

		// destructor
			~red_black_tree()
			{
				this->clear();
				this->_alloc.destroy(this->_end);
				this->_alloc.deallocate(this->_end, 1);
				this->_end = NULL;
			}

			size_type	size() const
			{
				return (this->_size);
			}

			node_ptr	get_end() const
			{
				return(this->_end);
			}

			void	clear()
			{
				this->_remove_end();
				this->_clear(this->_root);
				this->_size = 0;
				this->_root = NULL;
			}

			// will search the whole tree for the given key-value pair
			node_ptr	find(value_type key) const
			{
				node_ptr	node = this->_find(this->_root, key);
				if (!node)
					return (this->_end);
				return(node);
			}

			node_ptr	exist(value_type key) const
			{
				node_ptr	node = this->_find(this->_root, key);
				return(node);
			}

			void	swap(red_black_tree& src)
			{
				node_ptr		_end_tmp = this->_end;
				node_ptr		_root_tmp = this->_root;
				size_type		_size_tmp = this->_size;
				key_compare		_cmp_tmp = this->_cmp;
				allocator_type	_alloc_tmp = this->_alloc;

				this->_end = src._end;
				this->_root = src._root;
				this->_size = src._size;
				this->_cmp = src._cmp;
				this->_alloc = src._alloc;
				src._end = _end_tmp;
				src._root = _root_tmp;
				src._size = _size_tmp;
				src._cmp = _cmp_tmp;
				src._alloc = _alloc_tmp;
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

			ft::pair<node_ptr, bool>	insert(value_type value)
			{
				node_ptr	exists = this->exist(value);

				if (exists)
				 	return (ft::make_pair(exists, false));
				node_ptr new_node = this->_create_node(value);
				if (!this->_root)
				{
					this->_root = new_node;
					this->_root->color = BLACK;
					++this->_size;
					this->_connect_end();
					return (ft::make_pair(new_node, true));
				}
				this->_remove_end();
				ft::pair<node_ptr, bool> res = this->_insert(this->_root, new_node);
				++this->_size;
				this->_connect_end();
				return (res);
			}

			void	erase(value_type key)
			{
				node_ptr	node_to_delete = this->exist(key);
				if (!node_to_delete)
					return ;
				else if (this->_size == 1)
					this->_root = NULL;
				else
				{
					this->_remove_end();
					this->_erase(node_to_delete);
				}
				this->_alloc.destroy(node_to_delete);
				this->_alloc.deallocate(node_to_delete, 1);
				--this->_size;
				this->_connect_end();
			}
	};
}
