#ifndef TREE
#define TREE
#include <queue>
#include <vector>

template <typename T>
struct AVLBalancedTreeNode
{
    AVLBalancedTreeNode() : data(0), left(nullptr), right(nullptr) {}
    AVLBalancedTreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
    T data;
    AVLBalancedTreeNode *left, *right;
};

template <typename T_>
class AVLBalancedTree
{
public:
    AVLBalancedTree() : root(nullptr) {}
    ~AVLBalancedTree()
    {
        destoryTreeOperation(root);
        root = nullptr;
    }

    void insert(T_ value) { insertNodeOperation(&root, value); }

    void del(T_ value) { deleteNodeOperation(&root, value); }

    bool empty() { return root == nullptr; }

    int get_height(AVLBalancedTreeNode<T_> *object)
    {
        int leftTreeHeight, rightTreeHeight;
        if (object != nullptr)
        {
            leftTreeHeight = get_height(object->left);
            rightTreeHeight = get_height(object->right);
            return (leftTreeHeight > rightTreeHeight) ? (leftTreeHeight + 1) : (rightTreeHeight + 1);
        }
        return 0;
    }

    AVLBalancedTreeNode<T_> *get_node(T_ value) { return getNodeOperation(root, value); }

    std::vector<T_> debug_traverse()
    {
        std::vector<T_> ans;
        if (root != nullptr)
        {
            std::queue<AVLBalancedTreeNode<T_> *> Q;
            Q.push(root);
            AVLBalancedTreeNode<T_> *tempPointer;
            while (!Q.empty())
            {
                tempPointer = Q.front();
                Q.pop();
                ans.push_back(tempPointer->data);
                if (tempPointer->left != nullptr)
                    Q.push(tempPointer->left);
                if (tempPointer->right != nullptr)
                    Q.push(tempPointer->right);
            }
        }
        return ans;
    }

private:
    void LeftLeftRotate(AVLBalancedTreeNode<T_> **object)
    {
        if (object != nullptr)
        {
            AVLBalancedTreeNode<T_> *tempPointer = (*object)->left;
            (*object)->left = tempPointer->right;
            tempPointer->right = *object;
            *object = tempPointer;
        }
    }

    void RightRightRotate(AVLBalancedTreeNode<T_> **object)
    {
        if (object != nullptr)
        {
            AVLBalancedTreeNode<T_> *tempPointer_ = (*object)->right;
            (*object)->right = tempPointer_->left;
            tempPointer_->left = *object;
            *object = tempPointer_;
        }
    }

    void LeftRightRotate(AVLBalancedTreeNode<T_> **object)
    {
        RightRightRotate(&(*object)->left);
        LeftLeftRotate(object);
    }

    void RightLeftRotate(AVLBalancedTreeNode<T_> **object)
    {
        LeftLeftRotate(&(*object)->right);
        RightRightRotate(object);
    }

    void insertNodeOperation(AVLBalancedTreeNode<T_> **object, T_ value)
    {
        if (*object == nullptr)
        {
            *object = new AVLBalancedTreeNode(value);
            return;
        }
        if (value == (*object)->data)
            return;
        if (value < (*object)->data)
        {
            insertNodeOperation(&((*object)->left), value);
            if (get_height((*object)->right) - get_height((*object)->left) > 1)
            {
                if (value < (*object)->left->data)
                    LeftLeftRotate(object);
                else
                    LeftRightRotate(object);
            }
            return;
        }
        if (value > (*object)->data)
        {
            insertNodeOperation(&((*object)->right), value);
            if (get_height((*object)->right) - get_height((*object)->left) > 1)
            {
                if (value > (*object)->right->data)
                    RightRightRotate(object);
                else
                    RightLeftRotate(object);
            }
            return;
        }
    }

    AVLBalancedTreeNode<T_> *deleteNodeOperation(AVLBalancedTreeNode<T_> **Node, T_ value)
    {
        if (Node == nullptr)
            return nullptr;
        if (value == (*Node)->data)
        {
            if ((*Node)->left == nullptr && (*Node)->right == nullptr)
            {
                delete *Node;
                *Node = nullptr;
                return *Node;
            }
            else if ((*Node)->left != nullptr)
            {
                AVLBalancedTreeNode<T_> *temp = (*Node)->left;
                delete *Node;
                return temp;
            }
            else if ((*Node)->left != nullptr)
            {
                AVLBalancedTreeNode<T_> *temp = (*Node)->right;
                delete (*Node);
                return temp;
            }
            else
            {
                (*Node)->data = getMaxLeftTreeValue((*Node)->left);
                (*Node)->left = deleteNodeOperation(&(*Node)->left, (*Node)->data);
                return *Node;
            }
        }
        if (value < (*Node)->data)
        {
            (*Node)->left = deleteNodeOperation(&(*Node)->left, value);
            if (get_height((*Node)->right) - get_height((*Node)->left) > 1)
                RightLeftRotate(Node);
            else
                RightRightRotate(Node);
            return (*Node);
        }
        if (value > (*Node)->data)
        {
            (*Node)->right = deleteNodeOperation(&(*Node)->right, value);
            if (get_height((*Node)->left) - get_height((*Node)->right) > 1)
                LeftLeftRotate(Node);
            else
                LeftRightRotate(Node);
            return (*Node);
        }
    }

    AVLBalancedTreeNode<T_> *getNodeOperation(AVLBalancedTreeNode<T_> *Node, int value)
    {
        if (Node == nullptr)
            return nullptr;
        if (value < Node->data)
            return getNodeOperation(Node->left, value);
        else if (value > Node->data)
            return getNodeOperation(Node->right, value);
        else
            return Node;
    }

    int getMaxLeftTreeValue(AVLBalancedTreeNode<T_> Node)
    {
        if (Node == nullptr)
            return 0;
        if (Node->right == nullptr)
            return Node->data;
        return getMaxLeftTreeValue(Node->right);
    }

    void destoryTreeOperation(AVLBalancedTreeNode<T_> *Node)
    {
        if (Node == nullptr)
            return;
        destoryTreeOperation(Node->left);
        destoryTreeOperation(Node->right);
        delete Node;
    };

    AVLBalancedTreeNode<T_> *root;
};

typedef enum
{
	RED = 0,
	BLACK = 1
} Color;

template <typename T>
struct RBTNode
{
	Color color;
	T key;
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
};

template <typename Type>
class RBTree
{
public:
	RBTree()
	{
		Nil = BuyNode();
		root = Nil;
		Nil->color = BLACK;
	}

	~RBTree()
	{
		destroy(root);
		delete Nil;
		Nil = NULL;
	}

	bool insert(const Type &value)
	{
		RBTNode<Type> *pr = Nil;
		RBTNode<Type> *s = root;
		while (s != Nil)
		{
			if (value == s->key)
				return false;
			pr = s;
			if (value < s->key)
				s = s->left;
			else
				s = s->right;
		}
		s = BuyNode(value);
		if (pr == Nil)
		{
			root = s;
			root->parent = pr;
		}
		else
		{
			if (value < pr->key)
				pr->left = s;
			else
				pr->right = s;
			s->parent = pr;
		}
		Insert_Fixup(s);
		return true;
	}

	bool Remove(Type key)
	{
		RBTNode<Type> *t;
		if ((t = Search(root, key)) != Nil)
		{
			Remove(t);
			return true;
		}
		return false;
	}

protected:
	RBTNode<Type> *BuyNode(const Type &x = Type())
	{
		RBTNode<Type> *s = new RBTNode<Type>();
		assert(s != NULL);
		s->color = RED;
		s->left = s->right = s->parent = Nil;
		s->key = x;
		return s;
	}

	void LeftRotate(RBTNode<Type> *z)
	{
		RBTNode<Type> *y = z->right;
		z->right = y->left;
		if (y->left != Nil)
			y->left->parent = z;
		y->parent = z->parent;
		if (root == z)
			root = y;
		else if (z == z->parent->left)
			z->parent->left = y;
		else
			z->parent->right = y;
		y->left = z;
		z->parent = y;
	}

	void RightRotate(RBTNode<Type> *z)
	{
		RBTNode<Type> *y = z->left;
		z->left = y->right;
		if (y->right != Nil)
			y->right->parent = z;
		y->parent = z->parent;
		if (root == z)
			root = y;
		else if (z == z->parent->left)
			z->parent->left = y;
		else
			z->parent->right = y;
		y->right = z;
		z->parent = y;
	}

	void Insert_Fixup(RBTNode<Type> *s)
	{
		RBTNode<Type> *uncle;
		while (s->parent->color == RED)
		{
			if (s->parent == s->parent->parent->left)
			{
				uncle = s->parent->parent->right;
				if (uncle->color == RED)
				{
					s->parent->color = BLACK;
					uncle->color = BLACK;
					s->parent->parent->color = RED;
					s = s->parent->parent;
				}
				else
				{
					if (s == s->parent->right)
					{
						s = s->parent;
						LeftRotate(s);
					}
					s->parent->color = BLACK;
					s->parent->parent->color = RED;
					RightRotate(s->parent->parent);
				}
			}
			else
			{
				if (s->parent == s->parent->parent->right)
				{
					uncle = s->parent->parent->left;
					if (uncle->color == RED)
					{
						s->parent->color = BLACK;
						uncle->color = BLACK;
						s->parent->parent->color = RED;
						s = s->parent->parent;
					}
					else
					{
						if (s == s->parent->left)
							s = s->parent;
						RightRotate(s);
					}

					s->parent->color = BLACK;
					s->parent->parent->color = RED;
					LeftRotate(s->parent->parent);
				}
			}
		}
	}
	root->color = BLACK;
}

RBTNode<Type> *Search(RBTNode<Type> *root_, Type key) const
{
	if (root_ == Nil)
		return Nil;
	if (root_->key == key)
		return root;
	if (key < root_->key)
		return Search(root_->left, key);
	else
		return Search(root_->right, key);
}

void Transplant(RBTNode<Type> *u, RBTNode<Type> *v)
{
	if (u->parent == Nil)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	v->parent = u->parent;
}

RBTNode<Type> *Minimum(RBTNode<Type> *x)
{
	if (x->left == Nil)
		return x;
	return Minimum(x->left);
}

void Remove(RBTNode<Type> *z)
{
	RBTNode<Type> *x = Nil;
	RBTNode<Type> *y = z;
	Color ycolor = y->color;
	if (z->left == Nil)
	{
		x = z->right;
		Transplant(z, z->right);
	}
	else if (z->right == Nil)
	{
		x = z->left;
		Transplant(z, z->left);
	}
	else
	{
		y = Minimum(z->right);
		ycolor = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else
		{
			Transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		Transplant(z, y);
		y->left = z->left;
		z->left->parent = y;
		y->color = z->color;
	}
	if (ycolor == BLACK)
		Remove_Fixup(x);
}

void Remove_Fixup(RBTNode<Type> *x)
{
	while (x != root && x->color == BLACK)
	{
		if (x == x->parent->left)
		{
			RBTNode<Type> *w = x->parent->right;

			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->color = RED;
					w->left->color = BLACK;
					RightRotate(w);
					w = x->parent->right;
				}
				w->color = w->parent->color;
				w->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(x->parent);
				x = root;
			}
		}
		else
		{
			RBTNode<Type> *w = x->parent->left;
			if (w->color == RED)
			{
				w->parent->color = RED;
				w->color = BLACK;
				RightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

void destroy(RBTNode<Type> *&root)
{
	if (root == Nil)
		return;
	if (root->left != Nil)
		destroy(root->left);
	if (root->right != Nil)
		destroy(root->right);
	delete root;
	root = NULL;
}

private:
RBTNode<Type> *root;
RBTNode<Type> *Nil;
};

#endif
