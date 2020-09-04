#include <iostream>
#include "linked-list.h"

int main()
{
	// Create a new linked list object
	LinkedList<int> linkedList = LinkedList<int>();

	// Insert some data
	linkedList.insertNode(1);
	linkedList.insertNode(2);
	linkedList.insertNode(3);

	// Get a pointer to the node that contains the minimum data value
	auto minNode = linkedList.min();

	// Ensure the node is not a null pointer before using it
	if (minNode == nullptr)
	{
		std::cout << "The node is a null pointer. The list may be empty." << std::endl;
	}
	else
	{
		std::cout << "The maximum value in the list is: " << minNode->getData() << std::endl;
	}

	return 0;
}