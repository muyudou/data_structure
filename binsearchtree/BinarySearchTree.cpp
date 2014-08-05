#include "BinarySearchTree.h"
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree()
	: root(NULL)
{

}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs)
	: root(NULL)
{
    *this = rhs;
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    makeEmpty(root);
}

template <typename Comparable>
const BinarySearchTree<Comparable> &BinarySearchTree<Comparable>
    ::operator=(const BinarySearchTree &rhs)
{
    if (&rhs == this)
		return *this;
	else
	{
		makeEmpty();
		root = clone(rhs.root);
        return *this;
	}
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
    BinarySearchTree<Comparable>::clone(BinaryNode *t) const
{
    if (t == NULL)
		return NULL;
	return new BinaryNode(t->element, clone(t->left),
			clone(t->right));
}

template <typename Comparable>
const Comparable &BinarySearchTree<Comparable>::findMin() const
{
    return findMin(root)->element;
}

//基础情况：如果左子树为空，则返回该节点
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
    BinarySearchTree<Comparable>::
	findMin(BinaryNode *t) const
{
    if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

template <typename Comparable>
const Comparable &BinarySearchTree<Comparable>::findMax() const
{
    return findMax(root)->element;
}

//基础情况：如果右子树为空，则返回该节点
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
    BinarySearchTree<Comparable>::
	findMax(BinaryNode *t) const
{
    if (t == NULL)
		return NULL;
	while (t->right != NULL)
		t = t->right;
	return t;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x) const
{
	return contains(x, root);
}
    
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x, 
		BinaryNode *t) const
{
	if (t == NULL)
		return false;
    if (t->element == x)
		return true;
	else if (t->element < x)
		return contains(x, t->right);
	else
		return contains(x, t->left);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree() const
{
	cout << "中序遍历打印树" << endl;
	printTree(root);
	cout << endl;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode *t) const
{
	if (t == NULL)
		return;
	printTree(t->left);
	cout << t->element << " ";
    printTree(t->right);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
	makeEmpty(root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode * &t)
{
	if (t == NULL)
		return;
	else
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = NULL;
	}
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x)
{
	insert(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, 
		BinaryNode * &t)
{
    if (t == NULL)
		t = new BinaryNode(x, NULL, NULL);
	else if (x < t->element)
		insert(x, t->left);
	else if (x > t->element)
	    insert(x, t->right);
	else
		;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x)
{
	remove(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, 
		BinaryNode * & t)
{
	if (t == NULL)
		return;
	if (x < t->element)
		remove(x, t->left);
	else if (x > t->element)
		remove(x, t->right);
	else
	{
        if (t->left != NULL && t->right != NULL)
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else if (t->left == NULL && t->right == NULL)
		{
			delete t;
			t = NULL;
		}
		else
		{
			BinaryNode *oldnode = t;
			t = t->left != NULL ? t->left : t->right;
			delete oldnode;
			oldnode = NULL;
		}
	}
}

template <typename Comparable>
int BinarySearchTree<Comparable>::height() const
{
	return height(root);
}

template <typename Comparable>
int BinarySearchTree<Comparable>::
    height(const BinaryNode *t) const
{
	if (t == NULL)
		return 0;
	else
		return 1+max(height(t->left), height(t->right));
}

template <typename Comparable>
int BinarySearchTree<Comparable>::leafnum() const
{
	return leafnum(root);
}

template <typename Comparable>
int BinarySearchTree<Comparable>::
    leafnum(const BinaryNode *t) const
{
	if (t == NULL)
		return 0;
	else if (t->left == NULL && t->right == NULL)
		return 1;
	else
		return leafnum(t->left)+leafnum(t->right);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printPath() const
{
	int arr[100] = {};
	int pathlen = 0;
	printPath(root, arr, pathlen);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::
    printPath(BinaryNode *t, int *arr, int pathlen) const
{
	if (t == NULL)
		return;
	arr[pathlen] = t->element;
	pathlen++;
	if (t->left == NULL && t->right == NULL)
	{
		cout << " len: " << pathlen << endl;
		int i;
		for (i = 0; i < pathlen; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
	else
	{
		if (t->left != NULL)
		    printPath(t->left, arr, pathlen);
		if (t->right != NULL)
			printPath(t->right, arr, pathlen);
	}
}

template <typename Comparable>
void BinarySearchTree<Comparable>::levelprint() const
{
    if (root == NULL)
		return;
    else
	{
		/*首先将根节点入队，之后判断如果队列不空，则出对，出对后
		 判断该节点是否有左右两个孩子，有则进队，循环直到空*/
	    queue<BinaryNode *> que;
		que.push(root);
		while (!que.empty())
		{
			root = que.front();
			que.pop();
			cout << root->element << " ";
			if (root->left != NULL)
				que.push(root->left);
			if (root->right != NULL)
				que.push(root->right);
		}
	}
}

template <typename Comparable>
void BinarySearchTree<Comparable>::qianprint() const
{
	cout << "非递归前序遍历: ";
    if (root == NULL)
		return;
    else
	{
		stack<BinaryNode *> stk;
        BinaryNode *node = root;
		//依次对每个节点做如下操作
		while (node != NULL || !stk.empty())
		{
			/*如果左孩子不为空，则入栈，输出路径上的结点
			  root指向左孩子*/
		    while (node != NULL)
			{
		        cout << node->element << " ";
				stk.push(node);
			    node = node->left;
			}

			/*如果栈非空，元素出栈,如果这个节点有右孩子就进栈，
			 node指向这个点*/
		    if (!stk.empty())
			{
				node = stk.top();
                stk.pop();
				node = node->right;
			}
		}
	} 
	cout << endl;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::zhongprint() const
{
	cout << "非递归中序遍历： " ;
    if (root == NULL)
		return;
    else
	{
		/*思路：首先将向左走，将节点入栈，之后循环判断栈是否为空，
		 如果不为空，弹出一个元素，判断元素是否有右节点，有则入栈，
		 循环直到栈空*/
		stack<BinaryNode *> stk;
		BinaryNode *node = root;
		while (node != NULL || !stk.empty())
		{
		while (node != NULL)
		{
			stk.push(node);
			node = node->left;
		}

		if (!stk.empty())
		{
			node = stk.top();
			stk.pop();
			cout << node->element << " ";
			node = node->right;
		}
		}
	}
	cout << endl;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::houprint() const
{
	cout << "非递归后续遍历： "; 
    if (root == NULL)
		return;
    else
	{
		stack<BinaryNode *> stk;
		vector<BinaryNode *> vec;

		BinaryNode *node = root;
		while (node != NULL || !stk.empty())
		{
			while (node != NULL)
			{
				//如果是非
				if (find(vec.begin(), vec.end(), node) != vec.end())
				{
					cout << endl;
					return;
				}
				stk.push(node);
				node = node->left;
			}

			if (!stk.empty())
			{
				node = stk.top();
				//如果是叶子节点，就弹出并输出，结点指向右节点，因为要退栈
				if (node->left == NULL && node->right == NULL) 
				{
					cout << node->element << " ";
					stk.pop();
					//若是第一次访问，则将node置为node->right,访问右节点
					node = node->right;
				}
				else
				{
					//如果是非叶子结点，若数组中没有则进入数组，表示
					//第一次从栈中弹出，先不从栈弹出，不输出，
					//若有则表示已经弹出一次，可以直接输出，并从栈中弹出。
					if (find(vec.begin(), vec.end(), node) == vec.end())
					{
						vec.push_back(node);
						node = node->right;
					}
					else
					{
						//这里不需要再指向右节点
						cout << node->element << " ";
						stk.pop();
					}
				}
			}
		}
	}
}

template <typename Comparable>
void BinarySearchTree<Comparable>::mirror()
{
	mirror(root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::mirror(BinaryNode *&t)
{
	if (t == NULL)
		return;
    if (t->left != NULL || t->right != NULL)
	{
		swap(t->left, t->right);
	}
	mirror(t->left);
	mirror(t->right);
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* 
    BinarySearchTree<Comparable>::find_both_parent
	(BinaryNode *x, BinaryNode *y)
{
    return NULL;	
}



