#include <iostream>
#include "linked-list.h"

template<typename T>
void insertionSort(LinkedList<T>& list);

int main()
{
	LinkedList<int> list;

	list.insertNode(10);
	list.insertNode(1);
	list.insertNode(5);

	insertionSort(list);

	return 0;
}

// Definition of the function goes here (copy/paste from my example project)