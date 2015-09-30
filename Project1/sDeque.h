/* Double ended queue
/* Description: A dynamic array that can add and remove elements at the back and front of the array. It also grows and shrinks accordingly.
/* Author: Ricardo Stefano Reyna.
/* Version: 1.0.1
/* Date: 23/Feb/2015
/* Copywrite Stefano Reyna
*/
#ifndef SDEQUE_H
#define SDEQUE_H
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Deque {
private:
	string *queue; //The array which holds the queue
	unsigned num_elements; //The number of elements in the queue
	unsigned size_of_queue; //The capacity of the queue
	void grow(); // It will grow twice its size when it's full
	void shrink(); // It will shrink half its size when it's less 1/4 full
public:
	// Constructor
	Deque();
	// Destructor
	~Deque();
	// Inserts the element at the front of the queue
	void push_front(string item);
	// Inserts the element at the back of the queue
	void push_back(string item);
	// Deletes the element at the front of the queue
	string pop_front();
	// Deletes the element at the back of the queue
	string pop_back();
	// Returns the number of elements in the queue
	int size();
	// Tell whether the queue is empty or not
	bool empty();
	// Prints the contents of the queue from front to back 
	// to stdout with one string per line followed by a blank line
	string toStr();
	// Helper function to check the queue size
	int print_size();
};

#endif