// This is the main file used to test the implementation of the linked list.
// It contains a test suite for ensuring that the implementation works, and
// a menu that allows the user to run their own custom tests.
//
// Author: Brandon Michelsen
// Date: 9/23/2018

#include <iostream>
#include <limits>
#include "linked-list.h"

using namespace std;

// Function prototypes
bool testSuiteLinkedList(); // Function for automatic testing of the linked list
bool testSuiteNode(); // Function for automatic tesing of the node
bool testSuite(); // Function for the full test suite
int checkInput(); // Function to ensure the user enters only an integer value as an input

int main()
{
	// Implement a linked list
	LinkedList<int> menuList;

	// Implement a menu for manual testing
	int choice = -1;
	while (choice != 0)
	{
		cout << "\tWelcome to the Linked List test program.\n";
		cout << "Note: the menu options only work with integer data types.\n";
		cout << "Please select an option from the menu below:\n";
		cout << "1) Create a linked list from the default constructor\n";
		cout << "2) Insert a node into the linked list\n";
		cout << "3) Delete a node on the linked list\n";
		cout << "4) Look at the head node of the linked list\n";
		cout << "5) Look at the tail node of the linked list\n";
		cout << "6) Find a value in the linked list\n";
		cout << "7) Find the maximum value in the linked list\n";
		cout << "8) Find the minimum value in the linked list\n";
		cout << "9) Run the automated testing suite\n";
		cout << "0) Exit the program\n";

		cout << "\nEnter an option from the menu: ";
		cin >> choice;
		
		system("cls");

		// Variable for the user to enter integers
		int userVal = 0;

		// Map the user's choice to a menu function
		if (choice == 1)
		{	// Create linked list object using default constructor
			cout << "Creating linked list with default constructor.\n";
			menuList = LinkedList<int>();
			cout << "Linked List object successfully created.\n";
		}
		else if (choice == 2)
		{	// Create a new node for the list
			cout << "Please enter a value for the node in the linked list: ";
			
			// Make sure the user only enters a valid integer
			userVal = checkInput();

			cout << "Inserting new node at the tail of the list.\n";
			menuList.insertNode(userVal);
			cout << "New node successfully created.\n";
			cout << "New node's value is: " << menuList.getTailPtr()->getData() << endl;
		}
		else if (choice == 3)
		{	// Delete a node from the list
			cout << "Enter a number stored in the node that you would like to delete: ";
			
			// Make sure the user only enters a valid integer
			userVal = checkInput();

			auto delPtr = menuList.find(userVal);

			if (delPtr == nullptr)
				cout << "Value you entered is not in the list. Node could not be deleted.\n";
			else
			{
				cout << "Deleting node from the list.\n";
				menuList.deleteNode(delPtr);
				cout << "Pointer successfully deleted.\n";
			}
		}
		else if (choice == 4)
		{	// Look at the head node of the list
			cout << "Getting the head node.\n";

			auto headPtr = menuList.getHeadPtr();
			
			if (headPtr == nullptr)
				cout << "Head pointer is null. Cannot access the data.\n";
			else
			{
				cout << "Head node retrieved.\n";
				cout << "Head node value: " << headPtr->getData() << endl;
				cout << "Head node location: " << headPtr << endl;
			}
		}
		else if (choice == 5)
		{	// Look at the tail node of the list
			cout << "Getting tail node.\n";

			auto tailPtr = menuList.getTailPtr();

			if (tailPtr == nullptr)
				cout << "Tail pointer is null. Cannot access the data.\n";
			else
			{
				cout << "Tail node retrieved.\n";
				cout << "Tail node value: " << tailPtr->getData() << endl;
				cout << "Tail node location: " << tailPtr << endl;
			}
		}
		else if (choice == 6)
		{	// Find a value in the list
			cout << "Please enter the value you would like to find: ";
			
			// Make sure the user enters only a valid integer
			userVal = checkInput();

			cout << "Looking for entered value in the list.\n";
			auto findNode = menuList.find(userVal);

			if (findNode == nullptr)
				cout << "Could not find that value in this list.\n";
			else
				cout << "Value found. Node location: " << findNode << endl;
		}
		else if (choice == 7)
		{	// Find the maximum value in the list
			cout << "Searching for the maximum value in the list.\n";

			auto maxPtr = menuList.max();

			if (maxPtr == nullptr)
				cout << "The list is empty. No maximum value could be found.\n";
			else
			{
				cout << "Maximum value found.\n";
				cout << "Maximum value in list: " << maxPtr->getData() << endl;
				cout << "Location of max value: " << maxPtr << endl;
			}
		}
		else if (choice == 8)
		{	// Find the minimum value in the list
			cout << "Searching for the minimum value in the list.\n";

			auto minPtr = menuList.min();

			if (minPtr == nullptr)
				cout << "The list is empty. No minimum value could be found.\n";
			else
			{
				cout << "Minimum value found.\n";
				cout << "Minimum value in list: " << minPtr->getData() << endl;
				cout << "Location of min value: " << minPtr << endl;
			}
		}
		else if (choice == 9)
		{	// Run the automated test suite
			testSuite();
		}
		else if (choice == 0)
		{
			continue;
		}
		else
		{
			cout << "Sorry. That is not an option in the menu.\n";
		}

		system("pause");
		system("cls");
	}

	cout << "Thank you for using this program.\n";
	system("pause");
	return 0;
}

// Function to ensure the user only enters integer values at the console
// Takes no parameters, returns an integer value
int checkInput()
{
	// Local variable for the value
	int x = 0;

	// While the user has not entered a proper integer value, have them re-enter a value
	while (!(cin >> x))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input. You must enter an integer.\n";
		cout << "Try again: ";
	}

	// Return the entered value
	return x;
}

// Function for the testing suite
// Takes no parameters, returns a boolean value
bool testSuite()
{
	// Clear the screen
	system("cls");

	cout << "******* Starting Tests *******\n\n";

	// Run tests on the linked list and node
	bool testNode = testSuiteNode();
	bool testLinkedList = testSuiteLinkedList();

	// Check if the tests were successful
	if (testLinkedList && testNode)
	{
		cout << "******* All tests passed successfully *******\n";
		return true;
	}
	else
	{
		cout << "******* Some or all tests failed *******\n";
		return false;
	}
}

// Function for testing the linked list
// Takes no parameters, returns a boolean value
bool testSuiteLinkedList()
{
	// Return value of the function
	bool testSucceeded = true;

	// Create default constructor for the linked list
	LinkedList<int> defaultLinkedList;

	/* Check if the default head and tail are nullptr */
	if (defaultLinkedList.getHeadPtr() == nullptr)
	{
		cout << "SUCCESS - Head pointer successfully defaulted to nullptr.\n";
	}
	else
	{
		cout << "FAIL - Head pointer failed to default to nullptr.\n";
		testSucceeded = false;
	}

	if (defaultLinkedList.getTailPtr() == nullptr)
	{
		cout << "SUCCESS - Tail pointer successfully defaulted to nullptr.\n";
	}
	else
	{
		cout << "FAIL - Tail pointer failed to default to nullptr.\n";
		testSucceeded = false;
	}
	/* End default head and tail test */

	/* Test the addition of a single node */
	defaultLinkedList.insertNode(1); // Insert node with value of 1

	// Test if the new head pointer has been set
	if (defaultLinkedList.getHeadPtr() != nullptr)
	{
		cout << "SUCCESS - Head pointer successfully reset to point to the newly created node.\n";
	}
	else
	{
		cout << "FAIL - Head pointer failed to point to the newly created node.\n";
		testSucceeded = false;
	}

	// Test if new tail pointer has been reset
	if (defaultLinkedList.getTailPtr() != nullptr)
	{
		cout << "SUCCESS - Tail pointer successfully reset to point to newly created node.\n";
	}
	else
	{
		cout << "FAIL - Tail pointer failed to reset to point to newly created node.\n";
		testSucceeded = false;
	}

	// Test if data for the new node successfully set
	if (defaultLinkedList.getHeadPtr()->getData() == 1)
	{
		cout << "SUCCESS - New node successfully stores the value of 1 as expected.\n";
	}
	else
	{
		cout << "FAIL - New node failed to store the value of 1.\n";
		testSucceeded = false;
	}
	/* End new head node creation test */
	
	/* Test second node creation */
	defaultLinkedList.insertNode(5); // Create another node with the value of 5

	// Test to see if tail ptr successfully reset
	if (defaultLinkedList.getTailPtr() != defaultLinkedList.getHeadPtr())
	{
		cout << "SUCCESS - Tail pointer successfully reset to the newly created node.\n";
	}
	else
	{
		cout << "FAIL - Tail pointer failed to reset to the newly created node.\n";
		testSucceeded = false;
	}

	// Test if the previous node is the head node
	if (defaultLinkedList.getTailPtr()->getPrevNode() == defaultLinkedList.getHeadPtr())
	{
		cout << "SUCCESS - New node successfully points back to the head node as the previous node.\n";
	}
	else
	{
		cout << "FAIL - New node failed to update its previous node pointer to the head node.\n";
		testSucceeded = false;
	}

	// Test if next node in tail is nullptr
	if (defaultLinkedList.getTailPtr()->getNextNode() == nullptr)
	{
		cout << "SUCCESS - New node's next pointer is nullptr as expected.\n";
	}
	else
	{
		cout << "FAIL - New node's next pointer failed to update to nullptr.\n";
		testSucceeded = false;
	}

	// Test if the data was set properly
	if (defaultLinkedList.getTailPtr()->getData() == 5)
	{
		cout << "SUCCESS - New node successfully stores the value of 5 as expected.\n";
	}
	else
	{
		cout << "FAIL - New node failed to store the expected value of 5.\n";
		testSucceeded = false;
	}
	/* End second node test */

	/* Test third node insertion */
	auto lastTail = defaultLinkedList.getTailPtr(); // Get the previous tail for testing
	defaultLinkedList.insertNode(3); // Create another node with the value of 3

	// Test if the tail node has been updated
	if (defaultLinkedList.getTailPtr() != lastTail)
	{
		cout << "SUCCESS - Tail node successfully updated to the newly created node.\n";
	}
	else
	{
		cout << "FAIL - Tail node failed to update to newly created node.\n";
		testSucceeded = false;
	}

	// Test if previous node is the last tail node
	if (defaultLinkedList.getTailPtr()->getPrevNode() == lastTail)
	{
		cout << "SUCCESS - New node successfully points back to the last tail node as the previous node.\n";
	}
	else
	{
		cout << "FAIL - New node failed to point back to the last tail as the previous node.\n";
		testSucceeded = false;
	}

	// Test if the tail node's next pointer is nullptr
	if (defaultLinkedList.getTailPtr()->getNextNode() == nullptr)
	{
		cout << "SUCCESS - New node successfully points to nullptr as next node.\n";
	}
	else
	{
		cout << "FAIL - New node failed to point to nullptr as next node.\n";
		testSucceeded = false;
	}

	// Test if data successfully set
	if (defaultLinkedList.getTailPtr()->getData() == 3)
	{
		cout << "SUCCESS - New node successfully stores the value of 3 as expected.\n";
	}
	else
	{
		cout << "FAIL - New node failed to store the value of 3.\n";
		testSucceeded = false;
	}
	/* End third node test */

	/* Test find function */
	// Test if find function finds the head node
	if (defaultLinkedList.find(1) == defaultLinkedList.getHeadPtr())
	{
		cout << "SUCCESS - Find function successfully found the head node based on the given value of 1.\n";
	}
	else
	{
		cout << "FAIL - Find function failed to find the head node based on the given value of 1.\n";
		testSucceeded = false;
	}

	// Test if find function finds the tail node
	if (defaultLinkedList.find(3) == defaultLinkedList.getTailPtr())
	{
		cout << "SUCCESS - Find function successfully found the tail node based on the given value of 3.\n";
	}
	else
	{
		cout << "FAIL - Find function failed to find the tail node based on the given value of 3.\n";
		testSucceeded = false;
	}

	// Test if find function finds the middle node
	if (defaultLinkedList.find(5) == defaultLinkedList.getTailPtr()->getPrevNode())
	{
		cout << "SUCCESS - Find function successfully found the middle node based on the given value of 5.\n";
	}
	else
	{
		cout << "FAIL - Find function failed to find the middle node based on the given value of 5.\n";
		testSucceeded = false;
	}
	/* End find function test*/

	/* Test min function */
	// Test if the minimum data member in the list is 1 (head node)
	if (defaultLinkedList.min() == defaultLinkedList.getHeadPtr())
	{
		cout << "SUCCESS - Min function successfully found the minimum value of 1 at the head node.\n";
	}
	else
	{
		cout << "FAIL - Min function failed to find the minium value of 1 at the head node.\n";
		testSucceeded = false;
	}
	/* End min function test */

	/* Test max function */
	// Test if maximum data member in the list is 5 (middle node)
	if (defaultLinkedList.max() == defaultLinkedList.getTailPtr()->getPrevNode())
	{
		cout << "SUCCESS - Max function successfully found the maximum value of 5 at the middle node.\n";
	}
	else
	{
		cout << "FAIL - Max function failed to find the maximum value of 5 at the middle node.\n";
	}
	/* End max function test */

	/* Test node deletion */
	// Add another node to test all cases in node deletion
	defaultLinkedList.insertNode(4);

	// Test node deletion on the tail
	int previousTailValue = defaultLinkedList.getTailPtr()->getData();
	defaultLinkedList.deleteNode(defaultLinkedList.getTailPtr());
	if (defaultLinkedList.getTailPtr()->getData() != previousTailValue)
	{
		cout << "SUCCESS - Tail node successfully deleted and tail node successfully reset.\n";
	}
	else
	{
		cout << "FAIL - Tail node failed to be deleted and tail node not reset.\n";
		testSucceeded = false;
	}
	
	// Make sure tail's next pointer reset to nullptr
	if (defaultLinkedList.getTailPtr()->getNextNode() == nullptr)
	{
		cout << "SUCCESS - Tail node's next pointer reset to nullptr.\n";
	}
	else
	{
		cout << "FAIL - Tail node's next pointer failed to reset to nullptr.\n";
		testSucceeded = false;
	}

	// Test node deletion on the middle node
	defaultLinkedList.deleteNode(defaultLinkedList.getTailPtr()->getPrevNode());
	if (defaultLinkedList.getTailPtr()->getPrevNode() == defaultLinkedList.getHeadPtr())
	{
		cout << "SUCCESS - Middle node successfully deleted.\n";
	}
	else
	{
		cout << "FAIL - Middle node failed to be deleted.\n";
		testSucceeded = false;
	}

	// Test if head node points to tail node
	if (defaultLinkedList.getHeadPtr()->getNextNode() == defaultLinkedList.getTailPtr())
	{
		cout << "SUCCESS - Head node successfully points to tail node.\n";
	}
	else
	{
		cout << "FAIL - Head node failed to point to the tail node.\n";
		testSucceeded = false;
	}

	// Test head node deletion
	defaultLinkedList.deleteNode(defaultLinkedList.getHeadPtr());
	if (defaultLinkedList.getHeadPtr() == defaultLinkedList.getTailPtr())
	{
		cout << "SUCCESS - Head node successfully deleted and head pointer successfully reset.\n";
	}
	else
	{
		cout << "FAIL - Head node failed to delete and head pointer failed to reset.\n";
		testSucceeded = false;
	}

	// Test Final node deletion
	defaultLinkedList.deleteNode(defaultLinkedList.getHeadPtr());
	if (defaultLinkedList.getHeadPtr() == nullptr && defaultLinkedList.getTailPtr() == nullptr)
	{
		cout << "SUCCESS - Final node successfully deleted and head and tail pointers successfully updated.\n";
	}
	else
	{
		cout << "FAIL - Final node failed to delete and head and tail pointers failed to update.\n";
		testSucceeded = false;
	}
	/* End node deletion test */

	cout << "****** Linked List Tests Finished *****\n\n";
	return testSucceeded;
}

// Function for testing the node
// Takes no parameters, returns a boolean value
bool testSuiteNode()
{
	// Return value for the testing suite
	bool testSucceeded = true;

	/* Test default values set properly */
	// Create a default node
	Node<int> defaultNode;

	// Test if the data is set to correct default
	if (defaultNode.getData() == NULL)
	{
		cout << "SUCCESS - Data in node successfully set to default value of NULL.\n";
	}
	else
	{
		cout << "FAIL - Data failed to be set to the default value of NULL.\n";
		testSucceeded = false;
	}

	// Test if the previous node pointer is set to the default value
	if (defaultNode.getPrevNode() == nullptr)
	{
		cout << "SUCCESS - Node's previous node pointer successfully set to default value of nullptr.\n";
	}
	else
	{
		cout << "FAIL - Node's previous node pointer failed to be set to default value of nullptr.\n";
		testSucceeded = false;
	}

	// Test if next node pointer is set to default value
	if (defaultNode.getNextNode() == nullptr)
	{
		cout << "SUCCESS - Node's next node pointer successfully set to default value of nullptr.\n";
	}
	else
	{
		cout << "FAIL - Node's next node pointer failed to be set to default value of nullptr.\n";
		testSucceeded = false;
	}
	/* End default values test */

	/* Test node creation with data parameter */
	// Create parameter node with value of 5
	Node<int> parameterNode(5);

	// Test if the node contains the proper parameter data
	if (parameterNode.getData() == 5)
	{
		cout << "SUCCESS - Node successfully created with parameter value of 5.\n";
	}
	else
	{
		cout << "FAIL - Node failed to be created with parameter value of 5.\n";
		testSucceeded = false;
	}
	/* End data parameter test */

	/* Test if new data set properly */
	// Set new data value for the default node
	defaultNode.setData(2);

	// Test if the node successfully updated its data
	if (defaultNode.getData() == 2)
	{
		cout << "SUCCESS - Node's data successfully updated to a value of 2.\n";
	}
	else
	{
		cout << "FAIL - Node's data failed to update to a value of 2.\n";
		testSucceeded = false;
	}
	/* End new data test */

	/* Test next and previous nodes set properly */
	// Test if node's next node pointer can be reset
	defaultNode.setNextNode(&parameterNode);
	if (defaultNode.getNextNode() == (&parameterNode))
	{
		cout << "SUCCESS - Node's next node pointer successfully updated to parameter node.\n";
	}
	else
	{
		cout << "FAIL - Node's next node pointer failed to update to parameter node.\n";
		testSucceeded = false;
	}

	// Test if node's previous node pointer can be reset
	defaultNode.setPrevNode(&parameterNode);
	if (defaultNode.getPrevNode() == (&parameterNode))
	{
		cout << "SUCCESS - Node's previous pointer successfully updated to parameter node.\n";
	}
	else
	{
		cout << "FAIL - Node's previous node pointer failed to update to parameter node.\n";
		testSucceeded = false;
	}
	/* End next and previous node tests */

	cout << "****** Node Tests Finished ******\n\n";
	return testSucceeded;
}