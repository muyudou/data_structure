#include "BinarySearchTree.cpp"

int main()
{
	BinarySearchTree<int> bstree, bstree2;

	int val;
	while (cin >> val)
		bstree.insert(val);
	cout << bstree.contains(5) << endl;
	cout << "Max: " << bstree.findMax() << endl;
	cout << "Min: " << bstree.findMin() << endl;
	cout << "height: " << bstree.height() << endl;
	cout << "leafnum: " << bstree.leafnum() << endl;
	cout << "path: " << endl;
	bstree.printPath();
	bstree.printTree();
	cout << "树的镜像是：" << endl;
	bstree.mirror();
	bstree.printPath();
	bstree.printTree();
	bstree2 = bstree;
	bstree2.printTree();
	
	bstree.qianprint();
	bstree.zhongprint();
	bstree.houprint();

	return 0;
}
