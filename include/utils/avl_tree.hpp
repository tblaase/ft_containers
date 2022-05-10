
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))

namespace ft
{
	struct Node
	{
		int d;
		struct Node *l;
		struct Node *r;
	}*r;

	class avl_tree
	{
		public:
			avl_tree()
			{
				r = NULL;
			}

		int avl_tree::height(Node *t)
		{
			int h = 0;
			if (t != NULL)
			{
				int l_height = height(t->l);
				int r_height = height(t->r);
				int max_height = std::max(l_height, r_height);
				h = max_height + 1;
			}
			return h;
		}

		int avl_tree::difference(Node *t)
		{
			int l_height = height(t->l);
			int r_height = height(t->r);
			int b_factor = l_height - r_height;
			return b_factor;
		}

		Node *avl_tree::rr_rotat(Node *parent)
		{
			Node *t;
			t = parent->r;
			parent->r = t->l;
			t->l = parent;
			std::cout<<"Right-Right Rotation";
			return t;
		}

		Node *avl_tree::ll_rotat(Node *parent)
		{
			Node *t;
			t = parent->l;
			parent->l = t->r;
			t->r = parent;
			std::cout<<"Left-Left Rotation";
			return t;
		}

		Node *avl_tree::lr_rotat(Node *parent)
		{
			Node *t;
			t = parent->l;
			parent->l = rr_rotat(t);
			std::cout<<"Left-Right Rotation";
			return ll_rotat(parent);
		}

		Node *avl_tree::rl_rotat(Node *parent)
		{
			Node *t;
			t = parent->r;
			parent->r = ll_rotat(t);
			std::cout<<"Right-Left Rotation";
			return rr_rotat(parent);
		}

		Node *avl_tree::balance(Node *t)
		{
			int bal_factor = difference(t);
			if (bal_factor > 1)
			{
				if (difference(t->l) > 0)
					t = ll_rotat(t);
				else
					t = lr_rotat(t);
			}
			else if (bal_factor < -1)
			{
				if (difference(t->r) > 0)
					t = rl_rotat(t);
				else
					t = rr_rotat(t);
			}
			return t;
		}

		Node *avl_tree::insert(Node *r, int v)
		{
			if (r == NULL)
			{
				r = new Node;
				r->d = v;
				r->l = NULL;
				r->r = NULL;
				return r;
			}
			else if (v< r->d)
			{
				r->l = insert(r->l, v);
				r = balance(r);
			}
			else if (v >= r->d)
			{
				r->r = insert(r->r, v);
				r = balance(r);
			}
			return r;
		}

		void avl_tree::show(Node *p, int l)
		{
			int i;
			if (p != NULL)
			{
				show(p->r, l+ 1);
				std::cout<<" ";
				if (p == r)
					std::cout << "Root -> ";
				for (i = 0; i < l&& p != r; i++)
				{
					std::cout << " ";
					std::cout << p->d;
					show(p->l, l + 1);
				}
			}
		}

		void avl_tree::inorder(Node *t)
		{
			if (t == NULL)
				return;
			inorder(t->l);
			std::cout << t->d << " ";
			inorder(t->r);
		}

		void avl_tree::preorder(Node *t)
		{
			if (t == NULL)
				return;
			std::cout << t->d << " ";
			preorder(t->l);
			preorder(t->r);
		}

		void avl_tree::postorder(Node *t)
		{
			if (t == NULL)
				return;
			postorder(t ->l);
			postorder(t ->r);
			std::cout << t->d << " ";
		}
	};
}
