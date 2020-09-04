#include "BST.h"

int main()
{
	BinarySearchTree<int> bst = BinarySearchTree<int>();

	bst.insertNode(10);
	bst.insertNode(16);
	bst.insertNode(5);

	std::cout << "Minimum value in the list: " << bst.min()->data << endl;

	return 0;
}