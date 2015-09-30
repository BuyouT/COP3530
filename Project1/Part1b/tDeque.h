/* Double ended queue
/* Description: A dynamic array that can add and remove elements at the back and front of the array. It also grows and shrinks accordingly.
/* Author: Ricardo Stefano Reyna.
/* Version: 1.1.2
/* Date: 23/Feb/2015
/* Copywrite Stefano Reyna
*/
#ifndef TDEQUE_H
#define TDEQUE_H
#include <string>
#include <iostream>
// Used for the toStr() function
#include <sstream>
// Exception handling
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
private:
	T *queue; //The array which holds the queue
	int num_elements; //The number of elements in the queue
	int size_of_queue; //The capacity of the queue
	void grow(); // It will grow twice its size when it's full
	void shrink(); // It will shrink half its size when it's less 1/4 full
public:
	// Constructor
	Deque();
	// Destructor
	~Deque();
	// Inserts the element at the front of the queue
	void push_front(T item);
	// Inserts the element at the back of the queue
	void push_back(T item);
	// Deletes the element at the front of the queue
	T pop_front();
	// Deletes the element at the back of the queue
	T pop_back();
	// Returns the number of elements in the queue
	int size();
	// Tell whether the queue is empty or not
	bool empty();
	// Prints the contents of the queue from front to back 
	// to stdout with one string per line followed by a blank line
	string toStr();
};

template <typename T>
Deque<T>::Deque() {
	// Array starts with a size 8 with no elements
	num_elements = 0;
	size_of_queue = 8;
	// initiate queue with an array of size 8
	queue = new T[size_of_queue];
}

template <typename T>
Deque<T>::~Deque() {
	delete [] queue;
}

template <typename T>
void Deque<T>::push_front(T item) {
	// Shift the whole array down and set item to the first array element
	if(num_elements < size_of_queue) {	
		for (int i = num_elements; i >= 0; --i) {
			queue[i+1] = queue[i];
		}
		queue[0] = item;
		++num_elements;
	}
	// Recursive function used in case queue is full
	else if (num_elements == size_of_queue) {
		grow();
		push_front(item);
	}
}

template <typename T>
void Deque<T>::push_back(T item) {
	// Set item to the last element
	if(num_elements < size_of_queue) {	
		queue[num_elements] = item;
		++num_elements;
	}
	// Recursive function used in case queue is full
	else if (num_elements == size_of_queue) {
		grow();
		push_back(item);
	}
}

template <typename T>
T Deque<T>::pop_front() {
	T tempString = queue[0];
	if (!empty()) {
		// Recursive function used in case queue is less tha 1/4 filled
		if (num_elements < size_of_queue/4 && size_of_queue > 8) {
			shrink();
			return pop_front();
		}

		else {
			// Shift array upwards
			for (int i = 0; i < num_elements; ++i) {
				queue[i] = queue[i+1];
			}
			--num_elements;
		}
		return tempString;
	}

	else {
		throw range_error("Popped empty queue");
	}
}

template <typename T>
T Deque<T>::pop_back() {
	T tempString;
	if (!empty()) {
		// Recursive function used in case queue is less tha 1/4 filled
		if (num_elements < size_of_queue/4 && size_of_queue > 8) {
			shrink();
			return pop_back();
		}

		else {
			tempString = queue[num_elements];
			--num_elements;
		}
		return tempString;
	} 

	else {
		throw range_error("Popped empty queue");
	}
}

template <typename T>
int Deque<T>::size() {
	return num_elements;
}

template <typename T>
bool Deque<T>::empty() {
	return size() == 0;
}

template <typename T>
string Deque<T>::toStr() {
	string s = "";
	int i = 0;
	// Sets s to all the values of the queue and appends it to the previous s
	while (i < num_elements) {
		string append;
		ostringstream convert;
		T elem = queue[i];
		convert << elem;
		append = convert.str();
		s = s + append + "\n";
		++i;
	}
	return s;
}

// Grow will be called in push_front() and push_back()
template <typename T>
void Deque<T>::grow() {
	// Creates a temp array twice the size of queue
	T *temp1;
	try {
		T *temp1 = new T[2*size_of_queue];
	}

	catch (bad_alloc) {
		throw range_error("");
	}

	T * temp;
	temp = new T[2*size_of_queue];
	size_of_queue *= 2;
	for (int i = 0; i < num_elements; ++i) {
		temp[i] = queue[i];
	}
	delete [] queue;
	// Set queue with new size
	queue = new T[size_of_queue];
	queue = temp;
	
}

// Shrink will be called in pop_front() and pop_back()
template <typename T>
void Deque<T>::shrink() {
	// Creates a temp array half the size of queue
	T *other = new T[size_of_queue/2];
	size_of_queue = size_of_queue/2;
	for (int i = 0; i < num_elements; ++i) {
		other[i] = queue[i];
	}
	delete [] queue;
	// Set queue with new size
	queue = new T[size_of_queue];
	queue = other;
}

#endif