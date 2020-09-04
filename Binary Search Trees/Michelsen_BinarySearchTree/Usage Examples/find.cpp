#include "BST.h"

int main()
{
	BinarySearchTree<int> bst = BinarySearchTree<int>();

	bst.insertNode(10);
	bst.insertNode(16);
	bst.insertNode(5);
	bst.insertNode(7);

	std::cout << "Node containing value 7: " << bst.find(7) << endl;

	return 0;
}