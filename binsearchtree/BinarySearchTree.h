#ifndef BINARYSEARCHTREE_H

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree();
	BinarySearchTree(const BinarySearchTree &rhs);
	~BinarySearchTree();
	const BinarySearchTree &operator=(const BinarySearchTree &rhs);

	const Comparable &findMin() const;
	const Comparable &findMax() const;
	bool contains(const Comparable &x) const;
	bool isEmpty() const;
	void printTree() const;

	void makeEmpty();
	void insert(const Comparable &x);
	void remove(const Comparable &x);
	int height() const;
	int leafnum() const;
	void printPath() const;
    void levelprint() const;
	void qianprint() const;
	void zhongprint() const;
	void houprint() const;
	void mirror();

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(const Comparable &theElement, BinaryNode *lt, 
				BinaryNode *rt) : element(theElement), left(lt), right(rt)
		{}
	};

	BinaryNode *root;

	BinaryNode *findMin(BinaryNode *t) const;
	BinaryNode *findMax(BinaryNode *t) const;
	bool contains(const Comparable &x, BinaryNode *t) const;
	void printTree(BinaryNode *t) const;

	void makeEmpty(BinaryNode *&t);
	void insert(const Comparable &x, BinaryNode *&t);
	void remove(const Comparable &x, BinaryNode *&t);
	BinaryNode *clone(BinaryNode *t) const;

	int height(const BinaryNode *t) const;
	int leafnum(const BinaryNode *t) const;
	void printPath(BinaryNode *t, int *arr, int len) const;
	void mirror(BinaryNode * &t);
	BinaryNode *find_both_parent(BinaryNode *x, BinaryNode *y);
};

#endif
