#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>

using namespace std;

// Link list struct
struct Node {
	string key;
	Node* next;
	Node(string key) {
		this->key = key;
		this->next=NULL;
	}
};

class hashtable {
private:
	Node** htable; //Create the table
	int n; // Size of table
public:
	hashtable(); // Constructor
	~hashtable(); // Destructor
	void setSize(int size); // Setting table size
	int hash_function(string key, int hash_table_size); // Given hash function
	void insert(string key); // insert key
	void search(string key); // Search for key
};

#endif