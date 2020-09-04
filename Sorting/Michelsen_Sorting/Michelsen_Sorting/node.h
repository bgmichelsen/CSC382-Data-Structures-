// This file contains the class definition, as well as the data members and methods,
// for the node class. The node can be implemented in many different data structures,
// such as a linked list. The functionality is described in comments throughout the 
// code. The node uses a template to allow use of generic data types.
//
// Author: Brandon Michelsen
// Date: 9/23/2018

// Only include the header file once
#ifndef NODE_H
#define NODE_H

/* Class Definition */
template<class T>
class Node
{
public:
	// Constructors
	Node(); // Default constructor
	Node(T newData); // Custom constructor

					 // Getters and setters
	void setNextNode(Node<T>* next); // Function to set the next node pointer
	Node<T>* getNextNode(); // Function to get the next node pointer
	void setPrevNode(Node<T>* previous); // Function to set the previous node pointer
	Node<T>* getPrevNode(); // Function to get the previous node pointer
	void setData(T newData); // Function to set the node's data
	T getData(); // Function to get the node's data

private:
	// Create data members
	Node<T>* nextPointer;
	Node<T>* prevPointer;
	T data;
};

/* Method defintions */

// Default constructor
// No parameters, no return value
template<class T>
Node<T>::Node()
{
	// Initialize the previous and next pointers
	data = NULL;
	nextPointer = nullptr;
	prevPointer = nullptr;
};

// Custom constructor
// Parameter for the data to be entered, no return value
template<class T>
Node<T>::Node(T newData)
{
	// Initialize data and the previous and next pointers
	data = newData;
	nextPointer = nullptr;
	prevPointer = nullptr;
}

// Set next ptr function
// Takes parameter for next ptr value, returns void
template<class T>
void Node<T>::setNextNode(Node<T>* next)
{
	nextPointer = next;
}

// Get next ptr function
// Takes no parameters, returns the value of nextPointer
template<class T>
Node<T>* Node<T>::getNextNode()
{
	return nextPointer;
}

// Set previous ptr function
// Takes a parameter for prev pointer value, returns void
template<class T>
void Node<T>::setPrevNode(Node<T>* previous)
{
	prevPointer = previous;
}

// Get previous ptr function
// Takes no parameters, returns the value of prevPointer
template<class T>
Node<T>* Node<T>::getPrevNode()
{
	return prevPointer;
}

// Set data function
// Takes a parameter for the new data, returns void
template<class T>
void Node<T>::setData(T newData)
{
	data = newData;
}

// Get data function
// Takes no parameters, returns the value of data
template<class T>
T Node<T>::getData()
{
	return data;
}

#endif // NODE_H
