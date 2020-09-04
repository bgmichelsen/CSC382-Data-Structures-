#include "linked-list.h"

int main()
{
	// Create a new linked list object
	LinkedList<int> linkedList = LinkedList<int>();

	// Insert some data
	linkedList.insertNode(1);
	linkedList.insertNode(2);
	linkedList.insertNode(3);

	// Retrieve data from tail node
	int tailData = linkedList.getTailPtr()->getData();

	return 0;
}