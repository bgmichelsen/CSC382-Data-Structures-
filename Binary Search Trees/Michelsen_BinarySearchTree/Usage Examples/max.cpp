#include "BST.h"

int main()
{
	BinarySearchTree<int> bst = BinarySearchTree<int>();

	bst.insertNode(10);
	bst.insertNode(16);
	bst.insertNode(5);

	std::cout << "Maximum value in the list: " << bst.max()->data << endl;

	return 0;
}