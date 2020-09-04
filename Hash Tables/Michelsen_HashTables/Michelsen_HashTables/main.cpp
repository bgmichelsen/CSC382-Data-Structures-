// This is the main file of the program. It is where the hash table will be tested.
//
// Author: Brandon Michelsen
// Date: 11/4/2018

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <chrono>
#include <unordered_map>
#include "HashTable.h"

using namespace std;

// Set up a hashing type based on std::hash
struct HashType {
	int operator()(string key) const
	{
		return hash<string>()(key);
	}
};

// Function prototypes
bool testSuite(); // Testing suite function
bool tableTestSuite(); // Test function for the hash table
bool entryTestSuite(); // Test function for the table entry struct
int checkIntInput(); // Function for checking user integer input
string checkStrInput(); // Function for checking user string input
void displayTable(HashTable<string, int, HashType>& hTable); // Function for diaplying the table
void runtimeAnalysis(); // Function for running the runtime analysis

int main()
{
	// Declare local variables
	int choice = -1;

	// Create an initialize the hash table
	HashTable<string, int, HashType> hTable;

	do
	{
		cout << "\tWelcome to the Phonebook Program\n";
		cout << "\nChoose an option from the menu below:\n";
		cout << "1) Create a new contact\n";
		cout << "2) Search for a contact\n";
		cout << "3) Remove a contact\n";
		cout << "4) Display the phonebook\n";
		cout << "5) Analyze the runtime of the program\n";
		cout << "6) Run the automated test suite\n";
		cout << "0) Exit the program\n";

		cout << "\nPlease enter an option from the menu: ";
		choice = checkIntInput();

		// User input variables
		string key;
		int data = 0;

		system("cls");

		// Switch case for the menu options
		switch (choice)
		{
			// Case 0, exit the program
			case 0:
			{
				continue;
				break;
			}
			// Case 1, insert a value
			case 1:
			{
				cout << "Please enter the name of the contact: ";
				key = checkStrInput();
				cout << "Please enter the contact\'s phone number: ";
				data = checkIntInput();

				cout << "Name: " << key << endl;
				cout << "Number: " << data << endl;

				hTable.insert(key, data);
				break;
			}
			// Case 2, retrieve a value from the hash table
			case 2:
			{
				cout << "Please enter the contact you would like to search for: ";
				key = checkStrInput();

				auto found = hTable.retrieve(key);

				if (found == nullptr)
					cout << "Sorry. The data could not be found.\n";
				else
				{
					cout << "Data found.\n";
					cout << "Name: " << found->key << endl;
					cout << "Number: " << found->data << endl;
				}
				break;
			}
			// Case 3, remove and element from the table
			case 3:
			{
				cout << "Please enter the contact you would like to remove: ";
				key = checkStrInput();
				cout << "Removing the node...\n";
				hTable.remove(key);
				cout << "Done.\n";
				break;
			}
			// Case 4, display the table
			case 4:
			{
				displayTable(hTable);
				break;
			}
			// Case 5, run the program analysis
			case 5:
			{
				runtimeAnalysis();
				break;
			}
			// Case 6, run the automated test suite
			case 6:
			{
				if (testSuite())
					cout << "****** All tests were successful ******\n";
				else
					cout << "****** Some or all tests failed ******\n";
				break;
			}
			// Default, non-valid option
			default:
			{
				cout << "That is not a valid option.\n";
				break;
			}
		}
		system("pause");
		cin.clear();
		system("cls");
	} while (choice != 0);

	cout << "Thank you for using this program.\n";
	system("pause");
	return 0;
}

/* Function Definitions */

// Function to check user integer input
// Takes no parameters, returns the user-entered integer
int checkIntInput()
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

// Function to check user string input
// Takes no parameters, returns the user-entered string
string checkStrInput()
{
	string x;
	cin.ignore();
	getline(cin, x);
	return x;
}

// Function for Displaying the Table
// Takes a reference to the hash table, returns void
void displayTable(HashTable<string, int, HashType>& hTable)
{
	cout << "\n*** Displaying the Table ***\n";
	cout << "\nName\t\t\tNumber\n";
	cout << "---------------------------------\n";
	// Get the table
	typename HashTable<string, int, HashType>::TableEntry** table = hTable.getTable();

	// Display the table
	for (int i = 0; i < hTable.getTotalSize(); i++)
	{
		if (table[i] == nullptr)
			cout << "NULL\n";
		else if (table[i]->deleted == true)
			cout << "DELETED\n";
		else
		{
			cout << setw(25) << left << table[i]->key;
			cout << setw(20) << left << table[i]->data << endl;
		}
	}
	cout << "*** Finished Displaying ***\n";
}

// Runtime analysis function
// Takes no parameters, returns void
void runtimeAnalysis()
{
	/* Declare local variables */

	// Array of keys
	string keys[11] = {
		"Bob", "Sally", "Cindy", "Brian", "Craig",
		"Brent", "Nate", "Kieli", "Keith", "Lucy",
		"Blake"
	};

	// Array of values
	int values[11] = {
		2556, 2443, 2334, 2667, 2887,
		2998, 2001, 2447, 2889, 2778,
		2446
	};

	// Create a table for testing
	HashTable<string, int, HashType> testTable;

	cout << "****** Testing Runtime ******\n";

	// Test insertion time for one element
	cout << "\nTesting runtime for insertion of 10 elements.\n";
	auto tenInsertionStart = chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < 10; i++)
		testTable.insert(keys[i], values[i]);
	auto tenInsertionEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> tenInsertionDuration = tenInsertionEnd - tenInsertionStart;
	cout << "Done.\n";
	cout << "Time it took for insertion of 10 elements: " << tenInsertionDuration.count() << endl;

	// Test insertion time for one element
	cout << "\nTesting runtime for insertion of 1 element.\n";
	auto oneInsertionStart = chrono::high_resolution_clock::now();
	testTable.insert(keys[10], values[10]);
	auto oneInsertionEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> oneInsertionDuration = oneInsertionEnd - oneInsertionStart;
	cout << "Done.\n";
	cout << "Time it took to insert one element: " << oneInsertionDuration.count() << endl;

	// Test retrieval time for ten elements
	cout << "\nTesting retrieval runtime of 10 elements.\n";
	auto tenRetrievalStart = chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < 10; i++)
		testTable.retrieve(keys[i]);
	auto tenRetrievalEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> tenRetrievalDuration = tenRetrievalEnd - tenRetrievalStart;
	cout << "Done.\n";
	cout << "Time it took to retrieve 10 elements: " << tenRetrievalDuration.count() << endl;

	// Test retrieval time for 1 element
	cout << "\nTesting retrieval runtime of 1 element.\n";
	auto oneRetrievalStart = chrono::high_resolution_clock::now();
	testTable.retrieve(keys[10]);
	auto oneRetrievalEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> oneRetrievalDuration = oneRetrievalEnd - oneRetrievalStart;
	cout << "Done.\n";
	cout << "Time it took to retrieve 1 element: " << oneRetrievalDuration.count() << endl;

	// Test resize time
	cout << "\nTesting insertion and resize time.\n";
	auto resizeStart = chrono::high_resolution_clock::now();
	testTable.insert("Barbra", 2112);
	auto resizeEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> resizeDuration = resizeEnd - resizeStart;
	cout << "Done.\n";
	cout << "Time it took to resize and insert: " << resizeDuration.count() << endl;

	// Test retrieval with new table size
	cout << "\nTesting retrieval on 11 elements with new table size.\n";
	auto resizeRetrievalStart = chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < 11; i++)
		testTable.retrieve(keys[i]);
	auto resizeRetrievalEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> resizeRetrievalDuration = resizeRetrievalEnd - resizeRetrievalStart;
	cout << "Done.\n";
	cout << "Time it took for retrieval after resize: " << resizeRetrievalDuration.count() << endl;

	// Test retrieval on 1 element
	cout << "\nTesting retrieval on 1 element with new table size.\n";
	auto resizeRetrivalSingleStart = chrono::high_resolution_clock::now();
	testTable.retrieve("Barbra");
	auto resizeRetrivalSingleEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> resizeRetrievalSingleDuration = resizeRetrivalSingleEnd - resizeRetrivalSingleStart;
	cout << "Done.\n";
	cout << "Time it took for retrieval on 1 element: " << resizeRetrievalSingleDuration.count() << endl;

	cout << "\n****** Finished Runtime Testing ******\n";
}

// Test Suite Function
// Takes no parameters, returns a bool for the success of the tests
bool testSuite()
{
	// Return the success or failure of the tests
	return (entryTestSuite() && tableTestSuite());
}

// Test Suite for the Table Entry Struct
// Takes no parameters, returns a bool for the success of the tests
bool entryTestSuite()
{
	// Declare local variables
	bool entryTest = true; // Variable for tracking the success of the tests

	// Create a new table entry instance for the tests
	HashTable<int, int, HashType>::TableEntry testEntry;

	cout << "****** Testing the Table Entry Struct *****\n";

	// Test if the key can be set
	testEntry.key = 5;
	if (testEntry.key == 5)
		cout << "SUCCESS - Key for the test table entry successfully set to a value of 5.\n";
	else
	{
		cout << "FAIL - Key for the test table entry failed to be set to a value of 5.\n";
		entryTest = false;
	}

	// Test if the data can be set
	testEntry.data = 10;
	if (testEntry.data == 10)
		cout << "SUCCESS - Data for the test table entry successfully set to a value of 10.\n";
	else
	{
		cout << "FAIL - Data for the test table entry failed to be set to a value of 10.\n";
		entryTest = false;
	}

	// Test if the deleted flag can be set
	testEntry.deleted = false;
	if (testEntry.deleted == false)
		cout << "SUCCESS - Deleted flag for the test table entry successfully set to false.\n";
	else
	{
		cout << "FAIL - Deleted flag for the test table entry failed to be set to false.\n";
		entryTest = false;
	}

	cout << "****** Finished Testing Table Entry ******\n";

	return entryTest;
}

// Test Suite for the Hash Table
// Takes no parameters, returns a bool for the success of the tests
bool tableTestSuite()
{
	// Declare local variables
	bool tableTest = true; // Variable for tracking the success of the tests

	// Create a new hashtable to use in the tests
	HashTable<string, int, HashType> testTable;

	cout << "\n****** Testing the Hash Table ******\n";

	/* Test initial conditions */

	// Test the initial table size
	if (testTable.getTotalSize() == 11)
		cout << "SUCCESS - Table size successfully initialized to 11 elements.\n";
	else
	{
		cout << "FAIL - Table size failed to initialize to 11 elements.\n";
		tableTest = false;
	}

	// Test the current size of the table
	if (testTable.getCurrentSize() == 0)
		cout << "SUCCESS - Table successfully initialized with 0 elements occupied.\n";
	else
	{
		cout << "FAIL - Table failed to initilize with 0 elements occupied.\n";
		tableTest = false;
	}

	// Test that elements are initialized to null pointers
	if (testTable.getTable()[0] == nullptr)
		cout << "SUCCESS - Table elements successfully intilialized to null pointers.\n";
	else
	{
		cout << "FAIL - Table elements failed to be initialized to null pointers.\n";
		tableTest = false;
	}

	/* Test hash function */
	cout << "Hashing value Bob...\n";
	if (testTable.hash("Bob") == (-1*HashType()("Bob")))
		cout << "SUCCESS - Value of Bob successfully hashed.\n";
	else
	{
		cout << "FAIL - Value of Bob failed to be hashed.\n";
		tableTest = false;
	}

	/* Test single element insertion */

	// Test insertion based on key
	cout << "Inserting element with key = Bob and value = 2556...\n";
	testTable.insert("Bob", 2556);
	if (testTable.retrieve("Bob") != nullptr && testTable.retrieve("Bob")->key == "Bob")
		cout << "SUCCESS - Table entry with key = Bob successfully inserted.\n";
	else
	{
		cout << "FAIL - Table entry with key = Bob failed to be inserted.\n";
		tableTest = false;
	}

	// Test if value was inserted with the key
	if (testTable.retrieve("Bob")->data == 2556)
		cout << "SUCCESS - Data associated with Bob successfully set to 2556.\n";
	else
	{
		cout << "FAIL - Data associated with Bob failed to be set to 2556.\n";
		tableTest = false;
	}

	// Test if the current table size has increased to 1
	if (testTable.getCurrentSize() == 1)
		cout << "SUCCESS - Current table size has increased to 1 element.\n";
	else
	{
		cout << "FAIL - Current table size failed to increase to 1 with the new insertion.\n";
		tableTest = false;
	}

	/* Test insertion of multiple elements */
	cout << "Inserting 10 more elements...\n";
	testTable.insert("Cindy", 2338);
	testTable.insert("Brian", 2893);
	testTable.insert("Craig", 2547);
	testTable.insert("Nancy", 2886);
	testTable.insert("Brent", 2775);
	testTable.insert("Brittany", 2368);
	testTable.insert("John", 2779);
	testTable.insert("Joe", 2347);
	testTable.insert("Keith", 2987);
	testTable.insert("Kyle", 2654);

	// Test if the current size of the table has increased
	if (testTable.getCurrentSize() == 11)
		cout << "SUCCESS - An extra 10 elements were successfully inserted.\n";
	else
	{
		cout << "FAIL - 10 elements failed to be inserted.\n";
		tableTest = false;
	}

	// Manual check for the table insertion
	cout << "Manual Check of the displayed table below:\n";
	displayTable(testTable);

	/* Test removal of an element */
	cout << "\nRemoving Brittany from the table...\n";
	testTable.remove("Brittany");

	// Test to see if Brittany can be found
	if (testTable.retrieve("Brittany") == nullptr)
		cout << "SUCCESS - Brittany could not be found in the table after removal.\n";
	else
	{
		cout << "FAIL - Brittany was found in the table after removal.\n";
		tableTest = false;
	}

	// Test to see if the size of the table decreased
	if (testTable.getCurrentSize() == 10)
		cout << "SUCCESS - The removal successsfully brought the current size of the table down by 1 element.\n";
	else
	{
		cout << "FAIL - The removal failed to downgrade the current size of the table by 1.\n";
		tableTest = false;
	}

	// Manual check of the table
	cout << "Manually check the table below for a DELETED element:\n";
	displayTable(testTable);

	/* Test re-insertion of an element */
	cout << "\nInserting a new element with key = Billy and value = 2399...\n";
	testTable.insert("Billy", 2399);

	// Test to see if the data can be found
	if (testTable.retrieve("Billy") != nullptr)
		cout << "SUCCESS - Billy successfully inserted and found in the table.\n";
	else
	{
		cout << "FAIL - Billy failed to be inserted and found in the table.\n";
		tableTest = false;
	}

	// Test if the size successfully increased
	if (testTable.getCurrentSize() == 11)
		cout << "SUCCESS - Re-insertion successfully increased the current size of the table.\n";
	else
	{
		cout << "FAIL - Re-insertion failed to increase the current size of the table.\n";
		tableTest = false;
	}

	// Manual check of the table
	cout << "Manually check the table below for Billy:\n";
	displayTable(testTable);

	/* Test data re-assigning */
	cout << "\nGiving Bob a new value (value = 2446)...\n";
	testTable.insert("Bob", 2446);

	if (testTable.retrieve("Bob")->data == 2446)
		cout << "SUCCESS - Bob\'s value successfully reset to 2446.\n";
	else
	{
		cout << "FAIL - Bob\'s value failed to be reset to 2446.\n";
		tableTest = false;
	}

	/* Test resizing */
	cout << "Inserting a new element (key = Cynthia, value = 2359) to resize the table...\n";
	testTable.insert("Cynthia", 2359);

	// Test if Cynthia inserted
	if (testTable.retrieve("Cynthia") != nullptr)
		cout << "SUCCESS - Cynthia successfully inserted into the table.\n";
	else
	{
		cout << "FAIL - Cynthia failed to be inserted into the table.\n";
		tableTest = false;
	}

	// Test if total table size increased
	if (testTable.getTotalSize() == 33)
		cout << "SUCCESS - Table successfully resized to 33 elements total.\n";
	else
	{
		cout << "FAIL - Table failed to resize to 33 elements total.\n";
		tableTest = false;
	}

	// Test if the current size is 12
	if (testTable.getCurrentSize() == 12)
		cout << "SUCCESS - There are currently 12 elements in the table.\n";
	else
	{
		cout << "FAIL - The current number of elements in the table failed to properly update to 12.\n";
		tableTest = false;
	}

	cout << "****** Finished Testing the Hash Table ******\n\n";
	return tableTest;
}