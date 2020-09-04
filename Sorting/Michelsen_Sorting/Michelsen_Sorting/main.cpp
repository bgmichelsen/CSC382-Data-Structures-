// This is the main file for the sorting program. It is where the 
// sorting functions are defined and tested. The Linked List project
// from the beginning of the semester is included as part of this 
// project.
//
// Author: Brandon Michelsen

#include <iostream>
#include <string>
#include <limits>
#include <time.h>
#include <chrono>
#include <fstream>
#include "linked-list.h"
#include "node.h"

using namespace std;

// Function prototypes
template<typename T>
void insertionSort(LinkedList<T>& list); // Insertion sort algorithm
template<typename T>
void quickSort(LinkedList<T>& list, Node<T>* low, Node<T>* high); // Quick sort algorithm
template<typename T>
Node<T>* quickSortPartition(LinkedList<T>& list, Node<T>* low, Node<T>* high); // Partitioning function for quick sort

void displayList(LinkedList<int>& list); // Function for displaying the list
string checkStrInput(); // Function for checking user string input
int checkInput(); // Function for testing user input
bool testSuite(); // Function for the whole test suite
bool testInsertionSort(); // Function for testing insertion sort
bool testQuickSort(); // Fucntion for testing quick sort

int main()
{
	// Declare local variables
	LinkedList<int> list; // List to add data to and sort
	ifstream inFile; // File for reading in data to the linked list
	ofstream outFile; // File for writing data from the linked list

	int menuInput = -1; // Variable for the menu input
	chrono::high_resolution_clock::time_point runTimeStart; // Variables for tracking the runtime of sorting functions
	chrono::high_resolution_clock::time_point runTimeEnd;

	// Seed the random number
	srand(static_cast<unsigned int>(time(0)));

	do {
		cout << "\tWelcome to the Sorting Algorithm Program\n\n";
		cout << "Please select an option from the menu below:\n";
		cout << "1) Enter data from a file into the linked list.\n";
		cout << "2) Sort the list using Insertion Sort.\n";
		cout << "3) Sort the list using Quicksort.\n";
		cout << "4) Display the linked list.\n";
		cout << "5) Clear the linked list.\n";
		cout << "6) Write the linked list data to a file.\n";
		cout << "7) Run the automated test suite.\n";
		cout << "0) Exit the program.\n";

		cout << "\nPlease enter an option from the menu: ";
		menuInput = checkInput();

		system("cls");

		switch (menuInput)
		{
		// Exit the program
		case 0:
		{
			continue;
			break;
		}
		// Create data to populate the linked list
		case 1:
		{
			// Declare local variables
			string fileName; // Variable for the name of the file to open
			string inDataStr; // Variable for reading in the data from the file
			int inDataInt = 0; // Variable for converting to the integer

			// Get the file to open
			cout << "Please enter the location of the file you want to sort:\n";
			fileName = checkStrInput();

			// Open the file
			cout << "Opening the file...\n";
			inFile.open(fileName);
			cout << "Done.\n";
			cout << "\nWriting the file data to the linked list...\n";
			
			// Make sure the file opened before proceeding
			if (inFile.is_open())
			{
				// Read in the data from the file while there is data to read
				while (!(inFile.eof()))
				{
					inFile >> inDataStr; 
					inDataInt = stoi(inDataStr); // Convert to integer
					list.insertNode(inDataInt); // Insert the data into the linked list
				}
				cout << "Done.\n";
			}
			else
				// Otherwise, the file could not be opened
				cout << "Error. Cannot open the file.\n";

			// Close the file
			inFile.close();
			break;
		}
		// Sort the list using insertion sort
		case 2:
		{
			cout << "****** Insertion Sort ******\n";
			cout << "\nSorting the list...\n";
			runTimeStart = chrono::high_resolution_clock::now(); // Get the start time
			insertionSort<int>(list);
			runTimeEnd = chrono::high_resolution_clock::now(); // Get the end time
			cout << "Finished.\n";
			cout << "\nTime it took to sort: ";
			cout << chrono::duration_cast<chrono::microseconds>(runTimeEnd - runTimeStart).count();
			cout << " microseconds" << endl;
			break;
		}
		// Sort the list using quicksort
		case 3:
		{
			cout << "****** Quick Sort ******\n";
			cout << "\nSorting the list...\n";
			runTimeStart = chrono::high_resolution_clock::now(); // Get the start time
			quickSort<int>(list, list.getHeadPtr(), list.getTailPtr());
			runTimeEnd = chrono::high_resolution_clock::now(); // Get the end time
			cout << "Finished.\n";
			cout << "\nTime it took to sort: ";
			cout << chrono::duration_cast<chrono::microseconds>(runTimeEnd - runTimeStart).count();
			cout << " microseconds" << endl;
			break;
		}
		// Display the list
		case 4:
		{
			displayList(list);
			break;
		}
		// Clear the linked list
		case 5:
		{
			cout << "Clearing the linked list...\n";
			list.clear();
			cout << "Finished.\n";
			break;
		}
		// Write sorted data to an output file
		case 6:
		{
			// Declare local variables
			string fileName; // Variable for the file name 
			Node<int>* current; // Variable for cycling through the list

			// Get the name of the output file
			cout << "Please enter the name of the file to write to:\n";
			fileName = checkStrInput();

			// Open the file
			cout << "Opening the file...\n";
			outFile.open(fileName);
			cout << "Done.\n";
			cout << "Writing to the file...\n";

			// Make sure the file is opened before continuing
			if (outFile.is_open())
			{
				// Start at the beginning of the linked list
				current = list.getHeadPtr();

				// Cycle through the list
				while (current->getNextNode() != nullptr)
				{
					// Write the data of the node out to the file
					outFile << current->getData() << '\n';

					// Get the next node
					current = current->getNextNode();
				}
				cout << "Done.\n";
			}
			else
				// Otherwise, the file cannot be opened
				cout << "Error. The file could not be opened.\n";

			// Close the file
			outFile.close();

			break;
		}
		// Run the automated test suite
		case 7:
		{
			if (testSuite() == true)
				cout << "****** All tests were successful ******\n";
			else
				cout << "****** Some or all tests failed ******\n";
			break;
		}
		// Default - invalid input
		default:
		{
			cout << "That is not a valid input.\n";
			break;
		}
		}
		system("pause");
		system("cls");
	} while (menuInput != 0);

	cout << "Thank you for using our program.\n";
	system("pause");
	return 0;
}

/* Function definitions */

// Check user input function
// Takes no parameters, returns the integer value entered by the user
int checkInput()
{
	// Declare local variables
	int x = 0;

	// While the user has not entered a valid integer, have them try again
	while (!(cin >> x))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. You must enter an integer.\n";
		cout << "Try again: ";
	}

	// Return the value they entered
	return x;
}

// Function to check user string input
// Takes no parameters, returns the user-entered string
string checkStrInput()
{
	string x;
	cin.ignore();
	getline(cin, x);
	return x;
}

// Insertion sort function
// Takes a reference for the linked list to sort, returns void
template<typename T>
void insertionSort(LinkedList<T>& list)
{
	// Declare local variables
	T key, temp; // Variables for swapping
	Node<T>* current = list.getHeadPtr(); // Get the first element to check
	Node<T>* swap = list.getHeadPtr(); // Get the element before the first element to check

	// Make sure we are not sorting an empty list
	if (list.getHeadPtr() == nullptr)
		return;
	else
	{
		// Loop through the list
		while (current->getNextNode() != nullptr)
		{
			// Ensure we are checking the proper nodes
			current = current->getNextNode();
			swap = current->getPrevNode();

			// Get the key to check
			key = current->getData();

			// Check for data that is greater than the key
			while (swap != nullptr && swap->getData() > key)
			{
				// Swap the data that is greater than the key
				temp = swap->getData();
				swap->getNextNode()->setData(temp);
				swap->setData(key);
				swap = swap->getPrevNode();
			}
		}
	}
}

// Quick sort function
// Takes a reference for the linked list to sort, returns void
template<typename T>
void quickSort(LinkedList<T>& list, Node<T>* low, Node<T>* high)
{
	// Declare local variables
	Node<T>* p; // Variable for the partition

	// Ensure we are not sorting an empty list
	if (list.getHeadPtr() == nullptr)
		return;
	else
	{
		// Ensure we don't give a stack overflow error
		if (high != nullptr && low != high && low != high->getNextNode())
		{
			p = quickSortPartition<T>(list, low, high); // Get the proper partition

			// Recursive calls for proper sorting
			quickSort<T>(list, low, p->getPrevNode());
			quickSort<T>(list, p->getNextNode(), high);
		}
	}
}

// Quick sort partition function
// Takes a reference for the linked list to sort, returns an int
template<typename T>
Node<T>* quickSortPartition(LinkedList<T>& list, Node<T>* low, Node<T>* high)
{
	// Declare local variables
	T pivot = high->getData(); // Select the pivot value
	Node<T>* swap = low; // Node variable for swapping values
	Node<T>* next = low; // Node variable for running through the partition
	T temp = 0; // Temporary variable for swapping values

	// Cycle through the partition
	while (next != high)
	{
		// If the data in the current node is less than or equal to the pivot, swap
		if (next->getData() <= pivot)
		{
			// Swap the data
			temp = next->getData();
			next->setData(swap->getData());
			swap->setData(temp);

			// Get the next swap node
			swap = swap->getNextNode();
		}
		// Continue cycling through the partition
		next = next->getNextNode();
	}
	
	// Final swap
	temp = high->getData();
	high->setData(swap->getData());
	swap->setData(temp);

	// Return the swp node as the next partition
	return swap;
}

// Function to display the list
// Takes a reference for the linked list to display, returns void
void displayList(LinkedList<int>& list)
{
	// Get the head node
	auto current = list.getHeadPtr();

	// Only print the data if it contains less than or equal to 100 elements
	if (list.getSize() > 100)
		cout << "The data set is too large to print.\n";
	else
	{
		cout << "****** Displaying the List *****\n";
		// Run through the list until there are no more elements
		while (current != nullptr)
		{
			cout << current->getData() << endl;
			current = current->getNextNode();
		}
		cout << "****** Done Displaying ******\n";
	}
}

// Whole test suite function
// Takes no parameters, returns a boolean value indicating the success of the tests
bool testSuite()
{
	return (testInsertionSort() && testQuickSort());
}

// Test insertion sort function
// Takes no parameters, returns a boolean value indicating the success of the tests
bool testInsertionSort()
{
	// Declare local variables
	bool testSort = true; // Variable for tracking test success and failure
	LinkedList<int> testList; // List for testing sorting on

	cout << "****** Insertion Sort Test Function ******\n";
	// Add data to the list
	cout << "Adding elements to the list...\n";
	testList.insertNode(10);
	testList.insertNode(1);
	testList.insertNode(5);
	cout << "Elements currently in the list:\n";
	cout << testList.getHeadPtr()->getData() << endl;
	cout << testList.getHeadPtr()->getNextNode()->getData() << endl;
	cout << testList.getTailPtr()->getData() << endl;

	/* Test insertion sort With 3 unsorted elements */
	cout << "Testing insertion sort on unsorted data...\n";
	insertionSort<int>(testList);

	// Test if the value of 1 was sorted to the correct spot
	if (testList.getHeadPtr()->getData() == 1)
		cout << "SUCCESS - Element containing value of 1 successfully sorted to first element.\n";
	else
	{
		cout << "FAIL - Element containing value of 1 failed to be sorted to first element.\n";
		testSort = false;
	}

	// Test if the value of 5 was sorted to the correct spot
	if (testList.getHeadPtr()->getNextNode()->getData() == 5)
		cout << "SUCCESS - Element containing value of 5 successfully sorted to second element.\n";
	else
	{
		cout << "FAIL - Element containing value of 5 failed to be sorted to second element.\n";
		testSort = false;
	}

	// Test if the value of ten was sorted to the correct spot
	if (testList.getTailPtr()->getData() == 10)
		cout << "SUCCESS - Element containing value of 10 successfully sorted to third element.\n";
	else
	{
		cout << "FAIL - Element containing value of 10 failed to be sorted to third element.\n";
		testSort = false;
	}

	cout << "Clearing the list...\n";
	testList.clear();
	cout << "Done.\n";
	/* End test on unsorted data */

	/* Test insertion sort with duplicate data*/
	cout << "Adding new data to the list...\n";
	testList.insertNode(5);
	testList.insertNode(10);
	testList.insertNode(5);
	cout << "Elements currently in the list:\n";
	cout << testList.getHeadPtr()->getData() << endl;
	cout << testList.getHeadPtr()->getNextNode()->getData() << endl;
	cout << testList.getTailPtr()->getData() << endl;

	cout << "Testing insertion sort with duplicate data...\n";
	insertionSort<int>(testList);

	// Test if the first element was sorted correctly
	if (testList.getHeadPtr()->getData() == 5)
		cout << "SUCCESS - Element containing value 5 successfully sorted to the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 5 failed to be sorted to the correct location.\n";
		testSort = false;
	}

	// Test if the duplicate data was sorted correctly
	if (testList.getHeadPtr()->getNextNode()->getData() == testList.getHeadPtr()->getData())
		cout << "SUCCESS - Duplicate data successfully sorted to the correct location.\n";
	else
	{
		cout << "FAIL - Duplicate data failed to be sorted to the correct location.\n";
		testSort = false;
	}

	// Test if the last element was sorted correctly
	if (testList.getTailPtr()->getData() == 10)
		cout << "SUCCESS - Element containing value 10 successfully sorted to the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 10 failed to be sorted to the correct location.\n";
		testSort = false;
	}

	cout << "Clearing the list...\n";
	testList.clear();
	cout << "Done.\n";
	/* End test on duplicate data */

	/* Test insertion sort on sorted data */
	cout << "Adding new data to the list...\n";
	testList.insertNode(1);
	testList.insertNode(5);
	testList.insertNode(10);
	cout << "Elements currently in the list:\n";
	cout << testList.getHeadPtr()->getData() << endl;
	cout << testList.getHeadPtr()->getNextNode()->getData() << endl;
	cout << testList.getTailPtr()->getData() << endl;

	cout << "Testing insertion sort on sorted data...\n";
	insertionSort<int>(testList);

	// Test if the first element has not changed
	if (testList.getHeadPtr()->getData() == 1)
		cout << "SUCCESS - Element containing value 1 is still in the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 1 changed its location.\n";
		testSort = false;
	}

	// Test if the second element has not changed
	if (testList.getHeadPtr()->getNextNode()->getData() == 5)
		cout << "SUCCESS - Element containing value 5 is still in the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 5 changed its location.\n";
		testSort = false;
	}

	// Test if final element has not changed
	if (testList.getTailPtr()->getData() == 10)
		cout << "SUCCESS - Element containing value 10 is still in the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 10 changed its location.\n";
		testSort = false;
	}
	/* End test on sorted data */
	cout << "****** End Insertion Sort Test ******\n\n";

	return testSort;
}

// Test quick sort function
// Takes no parameters, returns a boolean value indicating the success of the tests
bool testQuickSort()
{
	// Declare local variables
	bool testSort = true; // Variable for tracking test success and failure
	LinkedList<int> testList; // List for testing on

	cout << "****** Quicksort Test Function ******\n";

	// Add data to the list
	cout << "Adding elements to the list...\n";
	testList.insertNode(10);
	testList.insertNode(1);
	testList.insertNode(5);
	cout << "Elements currently in the list:\n";
	cout << testList.getHeadPtr()->getData() << endl;
	cout << testList.getHeadPtr()->getNextNode()->getData() << endl;
	cout << testList.getTailPtr()->getData() << endl;

	/* Test quicksort With 3 unsorted elements */
	cout << "Testing quick sort on unsorted data...\n";
	quickSort<int>(testList, testList.getHeadPtr(), testList.getTailPtr());

	// Test if the value of 1 was sorted to the correct spot
	if (testList.getHeadPtr()->getData() == 1)
		cout << "SUCCESS - Element containing value of 1 successfully sorted to first element.\n";
	else
	{
		cout << "FAIL - Element containing value of 1 failed to be sorted to first element.\n";
		testSort = false;
	}

	// Test if the value of 5 was sorted to the correct spot
	if (testList.getHeadPtr()->getNextNode()->getData() == 5)
		cout << "SUCCESS - Element containing value of 5 successfully sorted to second element.\n";
	else
	{
		cout << "FAIL - Element containing value of 5 failed to be sorted to second element.\n";
		testSort = false;
	}

	// Test if the value of ten was sorted to the correct spot
	if (testList.getTailPtr()->getData() == 10)
		cout << "SUCCESS - Element containing value of 10 successfully sorted to third element.\n";
	else
	{
		cout << "FAIL - Element containing value of 10 failed to be sorted to third element.\n";
		testSort = false;
	}

	cout << "Clearing the list...\n";
	testList.clear();
	cout << "Done.\n";
	/* End test on unsorted data */

	/* Test quicksort with duplicate data*/
	cout << "Adding new data to the list...\n";
	testList.insertNode(5);
	testList.insertNode(10);
	testList.insertNode(5);
	cout << "Elements currently in the list:\n";
	cout << testList.getHeadPtr()->getData() << endl;
	cout << testList.getHeadPtr()->getNextNode()->getData() << endl;
	cout << testList.getTailPtr()->getData() << endl;

	cout << "Testing quick sort with duplicate data...\n";
	quickSort<int>(testList, testList.getHeadPtr(), testList.getTailPtr());

	// Test if the first element was sorted correctly
	if (testList.getHeadPtr()->getData() == 5)
		cout << "SUCCESS - Element containing value 5 successfully sorted to the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 5 failed to be sorted to the correct location.\n";
		testSort = false;
	}

	// Test if the duplicate data was sorted correctly
	if (testList.getHeadPtr()->getNextNode()->getData() == testList.getHeadPtr()->getData())
		cout << "SUCCESS - Duplicate data successfully sorted to the correct location.\n";
	else
	{
		cout << "FAIL - Duplicate data failed to be sorted to the correct location.\n";
		testSort = false;
	}

	// Test if the last element was sorted correctly
	if (testList.getTailPtr()->getData() == 10)
		cout << "SUCCESS - Element containing value 10 successfully sorted to the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 10 failed to be sorted to the correct location.\n";
		testSort = false;
	}

	cout << "Clearing the list...\n";
	testList.clear();
	cout << "Done.\n";
	/* End test on duplicate data */

	/* Test quicksort on sorted data */
	cout << "Adding new data to the list...\n";
	testList.insertNode(1);
	testList.insertNode(5);
	testList.insertNode(10);
	cout << "Elements currently in the list:\n";
	cout << testList.getHeadPtr()->getData() << endl;
	cout << testList.getHeadPtr()->getNextNode()->getData() << endl;
	cout << testList.getTailPtr()->getData() << endl;

	cout << "Testing quick sort on sorted data...\n";
	quickSort<int>(testList, testList.getHeadPtr(), testList.getTailPtr());

	// Test if the first element has not changed
	if (testList.getHeadPtr()->getData() == 1)
		cout << "SUCCESS - Element containing value 1 is still in the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 1 changed its location.\n";
		testSort = false;
	}

	// Test if the second element has not changed
	if (testList.getHeadPtr()->getNextNode()->getData() == 5)
		cout << "SUCCESS - Element containing value 5 is still in the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 5 changed its location.\n";
		testSort = false;
	}

	// Test if final element has not changed
	if (testList.getTailPtr()->getData() == 10)
		cout << "SUCCESS - Element containing value 10 is still in the correct location.\n";
	else
	{
		cout << "FAIL - Element containing value 10 changed its location.\n";
		testSort = false;
	}
	/* End test on sorted data */
	cout << "****** End Quicksort Test ******\n\n";

	return testSort;
}