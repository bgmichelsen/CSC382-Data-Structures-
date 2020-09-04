#include "BST.h"

int main()
{
	BinarySearchTree<int> bst = BinarySearchTree<int>();
	TreeNode<int> testTree;

	bst.setRoot(&testTree);
	std::cout << "Root: " << bst.getRoot() << endl;

	return 0;
}