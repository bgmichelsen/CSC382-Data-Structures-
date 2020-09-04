#include "BST.h"

int main()
{
	BinarySearchTree<int> bst = BinarySearchTree<int>();

	bst.insertNode(10);
	bst.insertNode(5);

	bst.deleteNode(5);
	bst.deleteNode(10);

	return 0;
}