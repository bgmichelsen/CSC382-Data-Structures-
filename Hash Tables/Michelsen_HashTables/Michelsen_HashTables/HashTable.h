// This file is where the hash table class is defined. The definitions for the hashing function, 
// the insert function, and the retrieve function are given. The class will be using a template
// that gives a generic type for the value V and key K, and a generic type for the hash function
// H.
//
// 11/4/2018

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

template<typename K, typename V, typename H>
class HashTable 
{
public:
	// Struct for a table entry
	struct TableEntry
	{
		K key; // Key for the entry
		V data; // Data for the entry
		bool deleted; // Deleted flag
	};

	// Constructor and deconstructor
	HashTable();
	~HashTable();

	// Getter functions
	int getTotalSize(); // Function for returning the size of the table
	int getCurrentSize(); // Function for returning how full the table is
	TableEntry** getTable(); // Function for returning the table

	// Other functions
	int hash(K key); // Function for hashing the key
	void insert(K key, V val); // Function for inserting a new table entry
	void remove(K key); // Function for removing a table entry
	TableEntry* retrieve(K key); // Function for retrieving a value

private:
	// Declare private data members
	int TABLE_SIZE; // Total size of the table
	int currentSize; // Tracking variable for how many elements are currently in the table
	TableEntry** table; // The hash table

	// Private functions
	void resize(K key, V val); // Private function for resizing the array
	void insertPrivate(TableEntry** tempTable, int newSize, K key, V val); // Private insert helper function for resize
};

/* Method Definitions */

// Constructor
// Takes no parameters, returns nothing
template<typename K, typename V, typename H>
HashTable<K, V, H>::HashTable()
{
	// Initialize the size variables
	TABLE_SIZE = 11;
	currentSize = 0;

	// Create a new table entry array
	table = new TableEntry*[TABLE_SIZE];

	// Initialize the table elements to null pointers
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = nullptr;
}

// Deconstructor
// Takes no parameters, returns nothing
template<typename K, typename V, typename H>
HashTable<K, V, H>::~HashTable()
{
	// Delete the hash table
	for (int i = 0; i < TABLE_SIZE; i++)
		if (table[i] != nullptr)
			delete table[i];
	delete[] table;
}

// Getter for the total table size
// Takes no parameters, returns the size of the table
template<typename K, typename V, typename H>
int HashTable<K, V, H>::getTotalSize()
{
	return TABLE_SIZE;
}

// Getter for how full the table is
// Takes no parameters, returns how many elements are currently in the table
template<typename K, typename V, typename H>
int HashTable<K, V, H>::getCurrentSize()
{
	return currentSize;
}

// Getter for the table
// Takes no parameters, returns the table
template<typename K, typename V, typename H>
typename HashTable<K, V, H>::TableEntry** HashTable<K, V, H>::getTable()
{
	return table;
}

// Hashing function
// Takes a parameter for the key, returns the integer value of the hash
template<typename K, typename V, typename H>
int HashTable<K, V, H>::hash(K key)
{
	// Variable for the hash
	int hash = 0;

	// Hash the key
	hash = H()(key);
	if (hash < 0)
		hash *= -1;

	return hash;
}

// Insert function
// Takes parameters for the key and value, returns void
template<typename K, typename V, typename H>
void HashTable<K, V, H>::insert(K key, V val)
{
	// Declare local variables
	int initialIndex = -1; // Variable for tracking the initial index

	// Get the index from the hash
	int index = hash(key) % TABLE_SIZE;

	// Search for an empty spot to put the new value in (linear probing)
	while (initialIndex != index && table[index] != nullptr && table[index]->deleted != true && table[index]->key != key)
	{
		// Set the initial index
		if (initialIndex == -1)
			initialIndex = index;
		// Get the next element in the table
		index = (index + 1) % TABLE_SIZE;
	}

	// Check if the element to insert is outside the scope of the table
	if (index == initialIndex && currentSize == TABLE_SIZE)
		// If so, resize the table
		resize(key, val);
	// Check if the table element is empty
	else if (table[index] == nullptr)
	{
		// If so, create a new element and increment the current size
		table[index] = new TableEntry{ key, val, false };
		currentSize++;
	}
	// Check to see if the data has been removed
	else if (table[index]->deleted == true)
	{
		// If so, reset the element
		table[index]->key = key;
		table[index]->data = val;
		table[index]->deleted = false;
		currentSize++;
	}
	// Check if the found element's key matches the key to 
	else if (table[index]->key == key)
		// If so, reset the value
		table[index]->data = val;
}

// Retrieve function
// Takes a parameter for the key to find, returns a pointer to the found element
template<typename K, typename V, typename H>
typename HashTable<K, V, H>::TableEntry* HashTable<K, V, H>::retrieve(K key)
{
	// Declare local variables
	int initialIndex = -1; // Variable for tracking the initial index

	// Get the index from the key
	int index = hash(key) % TABLE_SIZE;

	// Search for the data (linear probing)
	while (initialIndex != index && table[index] != nullptr && table[index]->deleted != true && table[index]->key != key)
	{
		// Set the initial index
		if (initialIndex == -1)
			initialIndex = index;
		// Get the next element in the table
		index = (index + 1) % TABLE_SIZE;
	}

	// If the value is a null pointer or the keys do not match, return a null pointer
	if (table[index] == nullptr || table[index]->key != key || table[index]->deleted == true)
		return nullptr;

	// Get the data at that index
	return table[index];
}

// Remove function
// Takes a parameter for the key to remove, returns void
template<typename K, typename V, typename H>
void HashTable<K, V, H>::remove(K key)
{
	// Find the entry to remove
	TableEntry* delEntry = retrieve(key);

	// Make sure we are not accessing a null pointer
	if (delEntry == nullptr)
		return;
	else
	{
		// Otherwise, remove the node
		delEntry->deleted = true;
		currentSize--;
	}
}

// Resize function
// Takes a parameter for the new data element, returns void
template<typename K, typename V, typename H>
void HashTable<K, V, H>::resize(K key, V val)
{
	// Declare local variables
	int index = 0; // Variable for tracking the new index
	
	// Reset the current size to 0
	currentSize = 0;

	// Create a new array with a new size
	TableEntry** newTable = new TableEntry*[TABLE_SIZE * 3];

	// Initialize the new array for null pointers
	for (int i = 0; i < (TABLE_SIZE * 3); i++)
		newTable[i] = nullptr;

	// Copy the contents of the old table over
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i] != nullptr || table[i]->deleted != true)
		{
			insertPrivate(newTable, TABLE_SIZE*3, table[i]->key, table[i]->data);
		}
	}

	// Add in the new value of the array
	insertPrivate(newTable, TABLE_SIZE*3, key, val);

	// Set new values
	TABLE_SIZE *= 3;
	delete[] table;
	table = newTable;
}

// Insert private function
// Takes parameters for the table the new table size the key and the value, returns void
template<typename K, typename V, typename H>
void HashTable<K, V, H>::insertPrivate(TableEntry** tempTable, int newSize, K key, V val)
{
	// Declare local variables
	int initialIndex = -1; // Variable for tracking the initial index

	// Get the index from the hash
	int index = hash(key) % newSize;

	// Search for an empty spot to put the new value in (linear probing)
	while (initialIndex != index && tempTable[index] != nullptr && tempTable[index]->deleted != true && 
		tempTable[index]->key != key)
	{
		// Set the initial index
		if (initialIndex == -1)
			initialIndex = index;
		// Get the next element in the table
		index = (index + 1) % newSize;
	}

	// Check if the table element is empty
	if (tempTable[index] == nullptr)
	{
		// If so, create a new element and increment the current size
		tempTable[index] = new TableEntry{ key, val, false };
		currentSize++;
	}
	// Check if the found element's key matches the key to 
	else if (tempTable[index]->key == key)
		// If so, reset the value
		tempTable[index]->data = val;
	else
		// Otherwise, create a new element
		tempTable[index] = new TableEntry{ key, val };
}
#endif // HASH_TABLE_H_