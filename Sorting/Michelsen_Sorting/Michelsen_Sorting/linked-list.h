// This file contains the class definition, along with data members and methods, 
// for the linked list. The functionality is described in comments throughout the 
// code. The class uses templates to make the implementation more generic.
//
// Author: Brandon Michelsen
// Date: 9/23/2018

// Only include the header file once
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Include necessary files
#include "node.h"

/* Class definition */
template<class T>
class LinkedList
{
public:
	// Constructors
	LinkedList(); // Default constructor
	~LinkedList(); // Deconstructor

	// Getters and setters
	void setHeadPtr(Node<T>* headPtr); // Function to set the head of the linked list
	Node<T>* getHeadPtr(); // Function to get the head of the linekd list
	void setTailPtr(Node<T>* tailPtr); // Function to set the tail of the linked list
	Node<T>* getTailPtr(); // Function to get the tail of the linked list
	int getSize(); // Function to get the size of the linked list

	// Other methods
	Node<T>* find(T dataToFind); // Function to find a node with dataToFind
	void insertNode(T newData); // Function to insert new node at the tail of the list
	void deleteNode(Node<T>* delNode); // Function to delate the node at delNode
	void clear(); // Function to clear the linked list
	Node<T>* min(); // Function to find the minimum data value in the list
	Node<T>* max(); // Function to find the maximum data value in the list

private:
	// Declare data members
	Node<T>* head;
	Node<T>* tail;
	int size;
};

/* Method definitions */

// Default constructor
// No parameters, no return value
template<class T>
LinkedList<T>::LinkedList()
{
	// Initialize the head and tail pointers and the size
	head = nullptr;
	tail = nullptr;
	size = 0;
}

// DEconstructor
// No parameters, no return value
template<class T>
LinkedList<T>::~LinkedList()
{
	// Clear the linked list
	clear();
}

// Set head ptr function
// Takes a parameter for the new head ptr, returns void
template<class T>
void LinkedList<T>::setHeadPtr(Node<T>* headPtr)
{
	head = headPtr;
}

// Get head ptr function
// Takes no paramters, returns the head of the linked list
template<class T>
Node<T>* LinkedList<T>::getHeadPtr()
{
	return head;
}

// Set tail ptr function
// Takes parameter for the new tail ptr, returns void
template<class T>
void LinkedList<T>::setTailPtr(Node<T>* tailPtr)
{
	tail = tailPtr;
}

// Get tail ptr function
// Takes no paramters, returns the tail of the linked list
template<class T>
Node<T>* LinkedList<T>::getTailPtr()
{
	return tail;
}

// Get size function
// Takes no parameters, returns the current size of the list
template<class T>
int LinkedList<T>::getSize()
{
	return size;
}

// Find function
// Takes a paramter for the data to find, returns a pointer to the node where the data was found
template<class T>
Node<T>* LinkedList<T>::find(T dataToFind)
{
	// Create a node for searching, set it to the head
	Node<T>* currentNode = head;

	// Loop until the data is found or until the tail is reached
	while (currentNode != nullptr && currentNode->getData() != dataToFind)
	{
		// Get the next node
		currentNode = currentNode->getNextNode();
	}

	return currentNode;
}

// Insert function
// Takes a parameter for the data to insert with the new node, returns void
template<class T>
void LinkedList<T>::insertNode(T newData)
{
	Node<T>* newNode = new Node<T>(newData);

	if (head == nullptr)
	{
		// If this is the first node...
		head = newNode; // Set the head to be the new node
		tail = newNode; // Set the tail to be the new node
	}
	else
	{
		// Otherwise...
		tail->setNextNode(newNode); // Set the next node from the tail to point to the new node
		newNode->setPrevNode(tail); // Set the previous node from the new node to be the tail
		tail = newNode; // Reset the tail to be the new node
	}

	// Increment the size of the list
	size++;
}

// Delete function
// Takes a parameter for a pointer to the node to delete, returns void
template<class T>
void LinkedList<T>::deleteNode(Node<T>* delNode)
{
	if (delNode == nullptr)
		// If the node to delete is a nullptr, return without doing anything
		return;

	if (delNode->getPrevNode() != nullptr)
	{
		// If a previous node exists, set its next node to be the node after delNode
		delNode->getPrevNode()->setNextNode(delNode->getNextNode());
	}
	else
	{
		// Otherwise, set the head node to be the node after delNode
		head = delNode->getNextNode();
	}

	if (delNode->getNextNode() != nullptr)
	{
		// If a next node exists, set its previous node to the node before delNode
		delNode->getNextNode()->setPrevNode(delNode->getPrevNode());
	}
	else
	{
		// If delNode is the tail node, reset the tail node to be the node before delNode
		tail = delNode->getPrevNode();
	}

	// Delete delNode
	delete delNode;

	// Decrement the size of the list
	size--;
}

// Function to return the minimum data value in the list
// Takes no parameters, returns a pointer to the node with the minimum value in the list
template<class T>
Node<T>* LinkedList<T>::min()
{
	// Create local variables
	Node<T>* smallest = head;
	Node<T>* current = head;

	if (head == tail)
		// If there is only one element in the list, return it
		return tail;

	// Otherwise loop through all the elements in the list
	while (current != nullptr)
	{
		if (current->getData() < smallest->getData())
			// If the current element is smaller than the last known smallest, reset the smallest to current
			smallest = current;
		// Get the next node in the list
		current = current->getNextNode();
	}
	return smallest;
}

// Function to return the maximum data value in the list
// Takes no parameters, returns a pointer to the node with the maximum value in the list
template<class T>
Node<T>* LinkedList<T>::max()
{
	// Create local variables
	Node<T>* largest = head;
	Node<T>* current = head;

	if (head == tail)
		// If there is only one element in the list, return it
		return tail;

	// Otherwise, loop through all the elements in the list
	while (current != nullptr)
	{
		if (current->getData() > largest->getData())
			// If the current element is greater than the last known largest, reset the largest to current
			largest = current;
		// Get the next node in the list
		current = current->getNextNode();
	}
	return largest;
}

// Function to clear the linked list
// Takes no parameters, returns void
template<class T>
void LinkedList<T>::clear()
{
	// Declare local variables
	Node<T>* current = tail;
	Node<T>* delNode = nullptr;

	// Make sure the linked list has elements in it
	if (head == nullptr)
		return;
	else
	{
		// Run through the list from the tail and delete the elements
		while (current != head)
		{
			delNode = current;
			current = current->getPrevNode();
			deleteNode(delNode);
		}

		// Finally, delete the head pointer
		deleteNode(current);
	}
}

#endif // LINKED_LIST_H
