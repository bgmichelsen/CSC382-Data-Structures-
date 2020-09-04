// This file defines the TreeNode class along with its data members and member functions. 
// The TreeNode class has data members for stored data, a pointer to the next node to the left, 
// and a pointer to the next node to the right. The member functions are the getter and setter 
// functions for each of these data members.

#ifndef _TREE_NODE_H
#define _TREE_NODE_H

template<class T>
struct TreeNode {
	TreeNode<T>* left = nullptr;
	TreeNode<T>* right = nullptr;
	T data = NULL;
};

#endif // _TREE_NODE_H