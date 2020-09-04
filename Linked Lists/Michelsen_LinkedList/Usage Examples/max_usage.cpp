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

	// Get the node with the maximum data value
	auto maxNode = linkedList.max();

	// Ensure the returned node is not a null pointer before using it
	if (maxNode == nullptr)
	{
		std::cout << "The returned value was a null pointer. The list may be empty." << std::endl;
	}
	else
	{
		std::cout << "The maximum data value is: " << maxNode->getData() << std::endl;
	}

	return 0;
}