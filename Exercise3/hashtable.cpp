#include "hashtable.h"

hashtable::hashtable() {
	n = 0;
}

hashtable::~hashtable() {
	// Deletes every element in the linked list
	for (int i = 0; i < n; ++i) {
        Node* entry = htable[i];
        while (entry != NULL) {
            Node* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
    // Delete the table
    delete[] htable;
}

void hashtable::setSize(int size) {
	// Set the size according to the parameter
	n = size;
	// Create the table according to its size
	htable = new Node*[n];
	for (int i = 0; i<n; ++i) {
		htable[i] = NULL;
	}
}

int hashtable::hash_function(string key, int hash_table_size) {
	// Given hash function from the document
	int index = 0;
	for (int i=0; i<key.length(); i++) {
		index += key[i];
	}
	return index % hash_table_size;
}

void hashtable::insert(string key) {
	// set entry to current key
	int hvalue = hash_function(key, n);
	Node* prev = NULL;
	Node* entry = htable[hvalue];
	// Move forward on the linked list until it's NULL
	while (entry != NULL) {
		prev = entry;
		entry = entry->next;
	}
	// Insert the key when the entry is NULL
	if (entry == NULL) {
    	entry = new Node(key);
        if (prev == NULL) {
            htable[hvalue] = entry;
        }
        else {
            prev->next = entry;
    	}
	}
	
}

void hashtable::search(string key) {
    bool found = false;
    int hval = hash_function(key, n);
    Node* entry = htable[hval];
    // Go through the link list until it finds the key
    while (entry != NULL) {
        if (entry->key == key) {
			cout << "Yes" << endl;
			found = true;
        }
        entry = entry->next;
    }

    // If found isn't true then it's not in the link list
    if (!found) {
    	cout << "No" << endl;
    }
}