#include "linked-list.h"

int main()
{
	// Create a new linked list object
	LinkedList<int> linkedList = LinkedList<int>();

	// Insert some data
	linkedList.insertNode(1);
	linkedList.insertNode(2);
	linkedList.insertNode(3);

	// Delete the tail node
	linkedList.deleteNode(linkedList.getTailPtr());

	return 0;
}