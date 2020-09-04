// This is the main file for the Binary Search Tree program.
// It is where the testing of the BinarySearchTree class will
// take place.
//
// Author: Brandon Michelsen
// Date: 10/14/2018

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include "BST.h"

using namespace std;

// Function prototypes
bool testSuiteBST(); // Function for testing the BST class
bool testSuiteTreeNode(); // Function for testing the the tree node class
bool testSuite(); // Function for the full test suite
int checkInput(); // Function to ensure the user only enters numbers
void populateBST(const int nodes); // Function to populate a BST with an array
void inOrderTraversal(TreeNode<int>* node, BinarySearchTree<int>& tree); // Function to traverse the tree

int main()
{
	// Implement a BST
	BinarySearchTree<int> bst;

	// Test the BST based on user input
	int choice = -1;
	while (choice != 0)
	{
		cout << "\tWelcome to the Binary Search Tree Test Program\n";
		cout << "Please select an option from the menu below:\n";
		cout << "1) Create a Binary Search Tree from the default constructor\n";
		cout << "2) Insert a new node into the tree\n";
		cout << "3) Delete a node from the tree\n";
		cout << "4) Find a node in the tree\n";
		cout << "5) Find the maximum value in the tree\n";
		cout << "6) Find the minimum value in the tree\n";
		cout << "7) Traverse the tree\n";
		cout << "8) Create a BST and populate with an array\n";
		cout << "9) Run the automated test suite\n";
		cout << "0) Exit the program\n";

		cout << "\nPlease enter your choice from the menu: ";
		choice = checkInput();

		system("cls");

		// Variable for user input
		int userVal = 0;

		// Map the user's choice to the desired functionality
		if (choice == 1)
		{
			// Create a BST object from default constructor
			cout << "Createing BST from default constructor.\n";
			bst = BinarySearchTree<int>();
			cout << "BST successfully created.\n";
		}
		else if (choice == 2)
		{
			// Have the user insert a new node
			cout << "Please enter an integer to insert: ";
			userVal = checkInput();

			cout << "Inserting node...\n";
			bst.insertNode(userVal);
			cout << "Finished.\n";
		}
		else if (choice == 3)
		{
			// Have the user delete a node based on a value
			cout << "Please enter the value of the node you would like to delete: ";
			userVal = checkInput();

			cout << "Deleting node.\n";
			bst.deleteNode(userVal);
			cout << "Finished.\n";
		}
		else if (choice == 4)
		{
			// Have the user search for a node
			cout << "Please enter the value you would like to find: ";
			userVal = checkInput();

			cout << "Searching for the value...\n";
			TreeNode<int>* foundNode = bst.find(userVal);

			if (foundNode == nullptr)
				cout << "Sorry. The node could not be found.\n";
			else
				cout << "The value " << userVal << " was found at node: " << foundNode << endl;
		}
		else if (choice == 5)
		{
			// Find the maximum value in the BST
			cout << "Searching for the maximum value in the list...\n";
			TreeNode<int>* max = bst.max();

			if (max == nullptr)
				cout << "Max value could not be found. Tree is empty.\n";
			else
				cout << "Max value found. Value is: " << max->data << endl;
		}
		else if (choice == 6)
		{
			// Find the minimum value in the BST
			cout << "Searching for the minimum value in the list...\n";
			TreeNode<int>* min = bst.min();

			if (min == nullptr)
				cout << "Min value could not be found. Tree is empty.\n";
			else
				cout << "Min value found. Value is: " << min->data << endl;
		}
		else if (choice == 7)
		{
			// Print out the tree using in-order traversal
			cout << "=========Traversing Tree=========\n";
			inOrderTraversal(bst.getRoot(), bst);
			cout << "=================================\n";
		}
		else if (choice == 8)
		{
			// Create a BST and populate it with an array
			cout << "Please enter the amount of nodes you would like the BST to have: ";
			userVal = checkInput();

			populateBST(userVal);
		}
		else if (choice == 9)
		{
			// Run the automated test suite
			if (testSuite() == true)
				cout << "\nSUCCESS: All tests passed.\n";
			else
				cout << "\nFAIL: Some or all tests failed.\n";
		}
		else if (choice == 0)
		{
			// Exit the program
			continue;
		}
		else
		{
			// Otherwise, the user entered an invalid choice
			cout << "That is not a valid option.\n";
		}

		system("pause");
		system("cls");
	}

	cout << "Thank you for using this program.\n";
	system("pause");
	return 0;
}

/* Function Definitions */

// Function to ensure user only enters integers
// Takes no paramters, returns the number the user entered
int checkInput()
{
	// Declare local variables
	int x = 0;

	// While the user is entering incorrect data, have them re-enter
	while (!(cin >> x))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input. You must enter an integer.\n";
		cout << "Try again: ";
	}

	// Return the value that the user entered
	return x;
}

// Function to populate a BST with an unsorted array
// Takes in a parameter indicating the amount of nodes to create, returns void
void populateBST(const int nodes)
{
	// Declare local variables
	vector<int> populateArray;
	BinarySearchTree<int> tree = BinarySearchTree<int>();
	int populateValue = 0;

	// Set the RNG seed
	srand(time(NULL));

	// Populate the array with unsorted values
	for (int i = 0; i < nodes; i++)
	{
		populateValue = rand();
		populateArray.push_back(populateValue);
	}

	// Insert the unsorted values
	cout << "Inserting the unsorted array elements into the BST...\n";
	auto insertionStart = chrono::high_resolution_clock::now(); // Track time it takes to populate the BST
	for (unsigned int j = 0; j < populateArray.size(); j++)
		tree.insertNode(populateArray[j]);
	auto insertionEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> insertionTime = insertionEnd - insertionStart;
	cout << "Done.\n";
	cout << "\nTime it took to insert all the nodes: " << insertionTime.count() << endl;

	// Display the tree
	cout << "\n====== New Tree ======\n";
	auto traverseStart = chrono::high_resolution_clock::now();
	inOrderTraversal(tree.getRoot(), tree);
	auto traverseEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> traverseTime = traverseEnd - traverseStart;
	cout << "======================\n";
	cout << "\nTime it took to traverse the tree: " << traverseTime.count() << endl;

	cout << "\nTime it took to insert all the nodes: " << insertionTime.count() << endl;

	// Track the amount of time it takes to execute the find function'
	cout << "\nSearching for value 10...\n";
	auto findStart = chrono::high_resolution_clock::now();
	auto found = tree.find(10);
	auto findEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> findTime = findEnd - findStart;
	cout << "Done.\n";
	if (found == nullptr)
		cout << "Value not found.\n";
	else
		cout << "Value found at node: " << found << endl;
	cout << "Time it took to run the find() function: " << findTime.count() << endl;

	// Track the amount of time it takes to find the maximum value
	cout << "\nLooking for the maximum value...\n";
	auto maxStart = chrono::high_resolution_clock::now();
	auto max = tree.max();
	auto maxEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> maxTime = maxEnd - maxStart;
	cout << "Done. Max value is: " << max << endl;
	cout << "Time it took to find the max value: " << maxTime.count() << endl;

	// Track the amount of time it takes to find the minimum value
	cout << "\nLooking for the minimum value...\n";
	auto minStart = chrono::high_resolution_clock::now();
	auto min = tree.min();
	auto minEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> minTime = minEnd - minStart;
	cout << "Done. Min value is: " << min << endl;
	cout << "Time it took to find the min value: " << minTime.count() << endl;

	// Track the amount of time it takes to delete all the nodes
	cout << "\nDeleting all the nodes...\n";
	auto deleteStart = chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < populateArray.size(); i++)
		tree.deleteNode(populateArray[i]);
	auto deleteEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> deleteTime = deleteEnd - deleteStart;
	cout << "Done.\n";
	cout << "Time it took to delete: " << deleteTime.count() << "\n\n";
}

// Function to traverse the tree
// Takes parameters for the starting node and the tree to traverse, returns void
void inOrderTraversal(TreeNode<int>* node, BinarySearchTree<int>& tree)
{
	if (node == nullptr)
		// If the node is a nullptr, return
		return;
	else
	{
		// Otherwise, continue traversing the tree
		inOrderTraversal(node->left, tree);
		if (node == tree.getRoot())
			cout << node->data << " <- Root\n";
		else
			cout << node->data << endl;
		inOrderTraversal(node->right, tree);
	}
}

// Function for the test suite
// Takes no parameters, returns a boolean value indicating if the test passed or failed
bool testSuite()
{
	return (testSuiteTreeNode() && testSuiteBST());
}

// Function to test the Tree Node class
// Takes no parameters, returns a boolean value indicating if the test passed or failed
bool testSuiteTreeNode()
{
	// Declare local variables
	bool nodeTest = true; // Variable for tracking the test scenarios

	// Create a tree node
	TreeNode<int> testNode;

	cout << "========= Testing Tree Nodes =========\n";

	/* Test the initialization of the tree node */
	if (testNode.left == nullptr)
	{
		cout << "SUCCESS - Test node\'s left pointer successfully initialized to null pointer.\n";
	}
	else
	{
		cout << "FAIL - Test node\'s left pointer failed to be initialized to null pointer.\n";
		nodeTest = false;
	}

	if (testNode.right == nullptr)
	{
		cout << "SUCCESS - Test node\'s right pointer successfully initialized to null pointer.\n";
	}
	else
	{
		cout << "FAIL - Test node\'s right pointer failed to be initialized to null pointer.\n";
		nodeTest = false;
	}

	if (testNode.data == NULL)
	{
		cout << "SUCCESS - Test node\'s data successfully initialized to null.\n";
	}
	else
	{
		cout << "FAIL - Test node\'s data failed to initialize to null.\n";
		nodeTest = false;
	}

	/* Test to see if data elements can be changed */
	TreeNode<int> pointerNode; // Node for testing left and right pointers

	testNode.data = 5; // Reset data for the test node to 5
	if (testNode.data == 5)
	{
		cout << "SUCCESS - Test node\'s data successfully set to the value 5.\n";
	}
	else
	{
		cout << "FAIL - Test node\'s data failed to be set to the value 5.\n";
		nodeTest = false;
	}

	testNode.left = &pointerNode; // Reset test node's left pointer
	if (testNode.left == &pointerNode)
	{
		cout << "SUCCESS - Test node\'s left pointer successfully points to another node.\n";
	}
	else
	{
		cout << "FAIL - Test node\'s left pointer failed to be set to another node.\n";
		nodeTest = false;
	}

	testNode.right = &pointerNode; // Reset test node's right pointer
	if (testNode.right == &pointerNode)
	{
		cout << "SUCCESS - Test node\'s right pointer successfully points to another node.\n";
	}
	else
	{
		cout << "FAIL - Test node\'s right pointer failed to be set to another node.\n";
		nodeTest = false;
	}

	cout << "========= End Tree Node Tests =========\n";

	return nodeTest;
}

// Function to test the BST class
// Takes no paramters, returns a boolean value indicating if the test passed or failed
bool testSuiteBST()
{
	// Declare local variables
	bool bstTest = true; // Variable for tracking test scenarios

	// Create a BST to run tests on
	BinarySearchTree<int> testBST = BinarySearchTree<int>();

	cout << "\n========= Testing BST =========\n";

	/* Test default values */
	if (testBST.getRoot() == nullptr)
	{
		cout << "SUCCESS - BST successfully created with the root initialized to null pointer.\n";
	}
	else
	{
		cout << "FAIL - BST failed to be created with the root initialized to null pointer.\n";
		bstTest = false;
	}

	/* Test insertion */

	// Test insertion at the root
	testBST.insertNode(10);
	if (testBST.getRoot()->data == 10)
	{
		cout << "SUCCESS - Root node inserted into BST with value of 10.\n";
	}
	else
	{
		cout << "FAIL - Root node failed to be inserted with value of 10.\n";
		bstTest = false;
	}

	// Test insertion to the left of the root
	testBST.insertNode(5);
	if (testBST.getRoot()->left->data == 5)
	{
		cout << "SUCCESS - Node with a value of 5 successfully inserted to the left of the root.\n";
	}
	else
	{
		cout << "FAIL - Node with a value of 5 failed to be inserted to the left of the root.\n";
		bstTest = false;
	}

	// Test insertion to the right of the root
	testBST.insertNode(16);
	if (testBST.getRoot()->right->data == 16)
	{
		cout << "SUCCESS - Node with a value of 16 successfully inserted to the right of the root.\n";
	}
	else
	{
		cout << "FAIL - Node with a value of 16 failed to be inserted to to the right of the root.\n";
		bstTest = false;
	}

	// Test creation of the left subtree
	testBST.insertNode(3);
	testBST.insertNode(7);
	if (testBST.getRoot()->left->left != nullptr && testBST.getRoot()->left->right != nullptr)
	{
		cout << "SUCCESS - Left subtree successfully created.\n";
	}
	else
	{
		cout << "FAIL - Left subtree failed to be created.\n";
		bstTest = false;
	}
	
	// Test creation of right subtree
	testBST.insertNode(18);
	testBST.insertNode(14);
	if (testBST.getRoot()->right->left != nullptr && testBST.getRoot()->right->right != nullptr)
	{
		cout << "SUCCESS - Right subtree successfully created.\n";
	}
	else
	{
		cout << "FAIL - Right subtree failed to be created.\n";
		bstTest = false;
	}

	// Test insertion of a dublicate node
	cout << "***NOTE: To check duplicate value insertion, must manually check below:\n";
	cout << "Inserting duplicate value 5...\n";
	testBST.insertNode(5);
	cout << "*** Check tree for duplicate value below (two 5\'s) ***\n";
	inOrderTraversal(testBST.getRoot(), testBST);
	cout << "*** End of Tree ***\n";

	/* Test searching */
	cout << "Searching for value 5...\n";
	if (testBST.find(5) != nullptr)
	{
		cout << "SUCCESS - Node containing value 5 successfully found.\n";
	}
	else
	{
		cout << "FAIL - Find function failed to find the node containing value 5.\n";
		bstTest = false;
	}

	/* Test min and max */
	cout << "Finding maximum value in BST...\n";
	if (testBST.max() != nullptr)
	{
		cout << "SUCCESS - A node containing a maximum value of " << testBST.max()->data << " was found.\n";
	}
	else
	{
		cout << "FAIL - A maximum value in the BST failed to be found.\n";
		bstTest = false;
	}

	cout << "Finding minimum value in BST...\n";
	if (testBST.min() != nullptr)
	{
		cout << "SUCCESS - A node containing a minimum value of " << testBST.min()->data << " was found.\n";
	}
	else
	{
		cout << "FAIL - A minimum value in the BST failed to be found.\n";
		bstTest = false;
	}

	/* Test deletion */

	// Test deletion of a leaf node
	testBST.deleteNode(7);
	if (testBST.getRoot()->left->right == nullptr)
	{
		cout << "SUCCESS - Leaf node containing the value 7 successfully deleted.\n";
	}
	else
	{
		cout << "FAIL - Leaf node containing the value 7 failed to be properly deleted.\n";
		bstTest = false;
	}

	// Test deletion of a node with a single child
	testBST.deleteNode(5);
	if (testBST.getRoot()->left->data == 3)
	{
		cout << "SUCCESS - Node containing 5 successfully deleted and root\'s left pointer points to value 3.\n";
	}
	else
	{
		cout << "FAIL - Node containing 5 failed to be deleted and root\'s left pointer failed to be reset.\n";
		bstTest = false;
	}

	// Test deletion of a node with two children
	testBST.deleteNode(16);
	if (testBST.getRoot()->right->data == 18) // Smallest value in right subtree is 18
	{
		cout << "SUCCESS - Node containing 16 successfully deleted and root\'s right pointer successfully reset to 14.\n";
	}
	else
	{
		cout << "FAIL - Node containing 16 failed to be properly deleted and root\'s right pointer to be reset.\n";
		bstTest = false;
	}
	
	// Test deletion of the root
	testBST.deleteNode(10);
	if (testBST.getRoot()->data = 14)
	{
		cout << "SUCCESS - Root node (value of 10) successfully deleted and replaced with value 14.\n";
	}
	else
	{
		cout << "FAIL - Root node failed to be deleted and replaced.\n";
		bstTest = false;
	}

	// Delete the rest of the tree
	cout << "Finishing tree deletion...\n";
	testBST.deleteNode(18);
	testBST.deleteNode(3);
	testBST.deleteNode(14);

	cout << "========= End BST Tests =========\n";

	return bstTest;
}