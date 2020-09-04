#include "linked-list.h"

int main()
{
	// Create a new linked list object
	LinkedList<int> linkedList = LinkedList<int>();

	// Create a new node object with an initial data value of 5
	Node<int> node = Node<int>(5);

	// Setter functions
	linkedList.setHeadPtr(&node);
	linkedList.setTailPtr(&node);

	// Getter functions
	Node<int>* headPtr = linkedList.getHeadPtr();
	Node<int>* tailPtr = linkedList.getTailPtr();

	return 0;
}