#include <iostream>
#include <string>
#include <unordered_map>
#include "HashTable.h"

// Create struct for hash type
struct HashType 
{
	int operator()(string key)
	{
		return std::hash<string>()(key);
	}
};

int main()
{
	HashTable<string, int, HashType> hTable;

	hTable.insert("Bob", 21);
	hTable.insert("Mary", 24);
	hTable.insert("Gary", 32);

	auto foundBob = hTable.retrieve("Bob");

	if (foundBob == nullptr)
		std::cout << "Sorry, Bob could not be found." << std::endl;
	else
		std::cout << "Bob\'s Data: " << foundBob->data << std::endl;

	return 0;
}