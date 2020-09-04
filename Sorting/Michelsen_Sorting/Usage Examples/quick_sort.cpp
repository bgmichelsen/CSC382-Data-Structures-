#include <iostream>
#include "linked-list.h"
#include "node.h"

template<typename T>
void quickSort(LinkedList<T>& list, Node<T>* low, Node<T>* high);
Node<T>* quickSortPartition(LinkedList<T>& list, Node<T>* low, Node<T>* high);

int main()
{
	LinkedList<int> list;

	list.insertNode(10);
	list.insertNode(1);
	list.insertNode(5);

	quickSort(list, list.getHeadPtr(), list.getTailPtr());
	auto partitionNode = quickSortPartition(list, list.getHeadPtr(), list.getTailPtr());

	return 0;
}

// Definition of the functions go here (copy/paste from my example project)