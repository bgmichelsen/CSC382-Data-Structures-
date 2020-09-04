// This file provides the class definition and member function definitions
// for the BinarySearchTree class. The binary search tree has a data member 
// that points to the root of the node, and member functions for inserting
// a node, deleting a node, searching for a node, finding the max, and
// finding the min

// NOTE: There are private functions to aid in insertion and removal of nodes

#ifndef _BST_H
#define _BST_H

#include "TreeNode.h"

template<class T>
class BinarySearchTree
{
public:
	// Constructors
	BinarySearchTree();

	// Getters and setters
	void setRoot(TreeNode<T>* rootPtr); // Method for setting root node
	TreeNode<T>* getRoot(); // Method for getting root node

	// Other methods
	void insertNode(T inData); // Function to insert
	void deleteNode(T delData); // Function to delete a node that contains the given data
	TreeNode<T>* max(); // Function to return the maximum value in the BST
	TreeNode<T>* min(); // Function to find the minimum data member
	TreeNode<T>* find(T dataToFind); // Function for finding data in the BST

private:
	// Declare data members
	TreeNode<T>* root;

	// Declare Private Functions
	void insertNodePrivate(TreeNode<T>*& node, T inData); // Private function for inserting a node
	void deleteNodePrivate(TreeNode<T>*& node, T delData); // Private function for deleting a node
	void removeRoot(); // Function for removing the root node
	void removeMatchingNode(TreeNode<T>*& parent, TreeNode<T>* current); // Private function for removing a node
	TreeNode<T>* findMin(TreeNode<T>* start); // Function for finding a minimum value of a subtree
};

/* Define member functions */

// Constructor
// Takes no paramters, returns nothing
template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
	// Initialize root pointer
	root = nullptr;
}

// Setter for root pointer
// Takes a pointer for resetting the root, returns void
template<class T>
void BinarySearchTree<T>::setRoot(TreeNode<T>* rootPtr)
{
	root = rootPtr;
}

// Getter for root pointer
// Takes no parameters, returns a pointer to the root
template<class T>
TreeNode<T>* BinarySearchTree<T>::getRoot()
{
	return root;
}

// Insert node method (public)
// Takes in data for the new node, returns void
template<class T>
void BinarySearchTree<T>::insertNode(T inData)
{
	// If the root node is nullptr, set it to contain the new node
	if (root == nullptr)
	{
		root = new TreeNode<T>;
		root->data = inData;
	}
	// Else, if the data is lesser, search to the left of the root
	else if (inData < root->data)
		insertNodePrivate(root->left, inData);
	// Else, if the data is greater, search to the right
	else if (inData > root->data)
		insertNodePrivate(root->right, inData);
	// Otherwise, the data matches
	else
		return;
}

// Insertion method (private)
// Takes a parameter for the input data and a node pointer, returns void
template<class T>
void BinarySearchTree<T>::insertNodePrivate(TreeNode<T>*& node, T inData)
{
	// If the current node is a nullptr, set it to contain the proper data
	if (node == nullptr)
	{
		node = new TreeNode<T>;
		node->data = inData;
	}
	// If the data we want is less than the current node's data, search to the left
	else if (inData < node->data)
		insertNodePrivate(node->left, inData);
	// If the data we want is greater, search to the right
	else if (inData > node->data)
		insertNodePrivate(node->right, inData);
	// Otherwise, the data matches our current node
	else
		return;
}

// Delete node method (public)
// Takes in data for the node to be deleted, returns void
template<class T>
void BinarySearchTree<T>::deleteNode(T delData)
{
	if (root == nullptr)
		// If the tree is empty, do nothing
		return;
	else if (root->data == delData)
		// Else, if the the root has the data to delete, remove the root node
		removeRoot();
	else
		// Otherwise, begin finding the data to delete
		deleteNodePrivate(root, delData);
}

// Delete node method (private)
// Takes in the data to be be deleted and a pointer to a node to search through, returns void
template<class T>
void BinarySearchTree<T>::deleteNodePrivate(TreeNode<T>*& node, T delData)
{
	if (delData < node->data && node->left != nullptr)
	{
		// Check if the node's left pointer is equal to the data to delete
		// If it is, remove that node. If not, continue searching to the left
		node->left->data == delData ?
			removeMatchingNode(node, node->left) :
			deleteNodePrivate(node->left, delData);
	}
	else if (delData > node->data && node->right != nullptr)
	{
		// Check if the node's right pointer is equal to the data to delete
		// If it is, remove that node. If not, continue searching to the right
		node->right->data == delData ?
			removeMatchingNode(node, node->right) :
			deleteNodePrivate(node->right, delData);
	}
	else
		// Otherwise, do nothing
		return;
}

// Remove root method (private)
// Takes no parameters, returns void
template<class T>
void BinarySearchTree<T>::removeRoot()
{
	// Declare local variables
	TreeNode<T>* delNode = root;
	TreeNode<T>* foundMin = nullptr;
	T temp = NULL;

	if (root->left == nullptr && root->right == nullptr)
	{
		// The root is the only node. Delete the corresponding data.
		root = nullptr;
		delete delNode;
	}
	else if (root->left == nullptr && root->right != nullptr)
	{
		// The root has one child to the right
		// Delete the current root and reset the new root
		root = root->right;
		delNode->right = nullptr;
		delete delNode;
	}
	else if (root->left != nullptr && root->right == nullptr)
	{
		// The root has one child to the left
		// Delete the current root and reset the new node
		root = root->left;
		delNode->left = nullptr;
		delete delNode;
	}
	else
	{
		// Otherwise, the root has two children
		// Find the smallest value in the right subtree and set it as the new root'
		foundMin = findMin(root->right);
		temp = (foundMin->data + 1);
		root->data = foundMin->data;
		foundMin->data = temp;
		deleteNodePrivate(root, foundMin->data);
	}
}

// Remove node method (private)
// Takes in the node to be deleted and its parent node, returns void
template<class T>
void BinarySearchTree<T>::removeMatchingNode(TreeNode<T>*& parent, TreeNode<T>* current)
{
	// Declare local variables
	TreeNode<T>* foundMin = nullptr;
	T temp = NULL;

	// Check to see if the current node is the parents left node
	bool left = (current->data < parent->data);

	if (current->left == nullptr && current->right == nullptr)
	{
		// If the current node is a leaf, delete it and set the parents pointer to null
		left == true ? parent->left = nullptr : parent->right = nullptr;
		delete current;
	}
	else if (current->left == nullptr && current->right != nullptr)
	{
		// If the node only has one child to the right, re-link the right node to
		// the parent node and delete the current node
		left == true ? parent->left = current->right : parent->right = current->right;
		current->right = nullptr;
		delete current;
	}
	else if (current->left != nullptr && current->right == nullptr)
	{
		// If the node only has one child to the left, re-link the left node to
		// the parent node and delete the current node
		left == true ? parent->left = current->left : parent->right = current->left;
		current->left = nullptr;
		delete current;
	}
	else
	{
		// Otherwise, find the minimum value in the right subtree and reset that to be the current node
		foundMin = findMin(current->right);
		temp = (foundMin->data) + 1; // Set temp data to be 1 greater than the node we wish to delete (due to runtime errors, data would copy again after deletion)
		current->data = foundMin->data;
		foundMin->data = temp;
		deleteNodePrivate(current, foundMin->data); // Delete the found minimum node
	}
}

// Find min in subtree method (private)
// Takes in a starting node, returns a pointer to the node containing the minimum value in the subtree
template<class T>
TreeNode<T>* BinarySearchTree<T>::findMin(TreeNode<T>* start)
{
	TreeNode<T>* current = start;

	while (current->left != nullptr)
		current = current->left;

	return current;
}

// Find max method
// Takes no paramters, returns a pointer to the node containing the maximum data value in the BST
template<class T>
TreeNode<T>* BinarySearchTree<T>::max()
{
	// Declare local variables
	TreeNode<T>* current = root;

	// Check if the tree is empty
	if (root == nullptr)
		// If it is, return a nullptr
		return nullptr;
	else
	{
		// Otherwise, run through the right side of the tree until a null pointer is reached
		while (current->right != nullptr)
			current = current->right;
	}

	return current;
}

// Find min method
// Takes no parameters, returns a pointer to the node containing the minimum data value in the BST
template<class T>
TreeNode<T>* BinarySearchTree<T>::min()
{
	// Declare local variables
	TreeNode<T>* current = root;

	// Check if the tree is empty
	if (root == nullptr)
		// If the tree is empty, return null pointer
		return nullptr;
	else
	{
		// Otherwise, follow the left side of the tree until a null pointer is reached
		while (current->left != nullptr)
			current = current->left;
	}
	
	return current;
}

// Find method
// Takes a paramter for the data to find, returns a pointer to the found node
template<class T>
TreeNode<T>* BinarySearchTree<T>::find(T dataToFind)
{
	// Create a starting node to search through
	TreeNode<T>* current = root;

	// If the tree is empty, return a nullptr
	if (root == nullptr)
		return nullptr;
	else
	{
		// Otherwise, run through the list searching for the node with the data to find
		while (current != nullptr && current->data != dataToFind)
		{
			if (dataToFind > current->data)
				// If the data is greater than the current node, go right
				current = current->right;
			else if (dataToFind < current->data)
				// If the data is less than the current node, go left
				current = current->left;
		}
	}
	// Return a pointer to the found node
	return current;
}

#endif // _BST_H