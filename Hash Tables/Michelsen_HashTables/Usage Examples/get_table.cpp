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

	auto table = hTable.getTable();

	return 0;
}