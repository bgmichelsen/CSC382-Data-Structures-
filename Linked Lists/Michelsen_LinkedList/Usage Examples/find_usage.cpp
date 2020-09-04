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

	// Find the data element 3 and store it in a variable
	auto foundNode = linkedList.find(3);

	// Ensure the returned value is not a null pointer before using it
	if (foundNode == nullptr)
	{
		std::cout << "The value of 3 was not found in this list." << std::endl;
	}
	else
	{
		std::cout << "The value found was " << foundVal->getData() << std::endl;
	}

	return 0;
}