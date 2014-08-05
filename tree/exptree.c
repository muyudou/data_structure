#include <iostream>
#include <stack>
#include <ctype.h>
#include <stdio.h>
using namespace std;

template <typename Object>
struct BinaryNode
{
	Object element;
	BinaryNode<Object> *left;
	BinaryNode<Object> *right;
};

typedef struct BinaryNode<char> Node;
typedef struct BinaryNode<char>* pNode;

pNode houtoexp(char *exp)
{
	char *p = exp;

	stack<pNode> stk;
	pNode bnode;

	while (*p != '\0')
	{
		 //如果是数字或字母，构造节点，进栈
		 if (isalnum(*p))
		 {
             bnode = new Node;
		     bnode->element = *p;
		     bnode->left = bnode->right = NULL;
			 stk.push(bnode);
		 }
		 else
		 {
			 pNode lnode = stk.top();
			 stk.pop();
			 pNode rnode = stk.top();
			 stk.pop();

			 bnode = new Node;
			 bnode->element = *p;
			 bnode->left = rnode;
			 bnode->right = lnode;
			 stk.push(bnode);
		 }
		 p++;
	}
	return bnode;
}

void zhongxu(pNode root)
{
	if (root == NULL)
		return;
	zhongxu(root->left);
	cout << root->element << " ";
	zhongxu(root->right);
}

int main()
{
	char expbuffer[256];

	gets(expbuffer);
	cout << expbuffer << endl;
    pNode root = houtoexp(expbuffer);
	zhongxu(root);
    cout << endl;

	return 0;
}
