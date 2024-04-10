#ifndef BALANCEDTREES
#define BALANCEDTREES

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
    ~AVLBalancedTree() { destoryTreeOperation(root); root = nullptr; }

    void insert(T_ value) { insertNodeOperation(&root, value); }

    void del(T_ value) { deleteNodeOperation(&root, value); }

    bool empty() {return root == nullptr;}

    void get_height(AVLBalancedTreeNode<T_> *object)
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

    void get_node(T_ value) { getNodeOperation(root, value) }

private:
    void LeftLeftRotate(AVLBalancedTreeNode<T_> **object)
    {
        if (object != nullptr)
        {
            AVLBalancedTreeNode *tempPointer = (*object)->left;
            (*object)->left = tempPointer->right;
            tempPointer->right = *object;
            *object = tempPointer;
        }
    }

    void RightRightRotate(AVLBalancedTreeNode<T_> **object)
    {
        if (object != nullptr)
        {
            AVLBalancedTreeNode *tempPointer = (*object)->right;
            (*object)->right = tempPointer->left;
            tempPointer->left = *object;
            *object = tempPointer;
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
            return get_node(Node->left, value);
        else if (value > Node->data)
            return get_node(Node->right, value);
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

#endif
