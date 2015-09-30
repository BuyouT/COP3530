#include "sDeque.h"

Deque::Deque() {
	num_elements = 0;
	size_of_queue = 8;
	queue = new string[size_of_queue];
	if (queue == NULL) {
		throw memoryfail;
	}
}

Deque::~Deque() {
	delete [] queue;
}

void Deque::push_front(string item) {
	if(num_elements < size_of_queue) {	
		for (unsigned i = num_elements; i >= 0; --i) {
			queue[i+1] = queue[i];
		}
		queue[0] = item;
		++num_elements;
	}

	else if (num_elements == size_of_queue) {
		// throw "Deque is currently full... Growing its size.";
		grow();
		push_front(item);
	}
}

void Deque::push_back(string item) {
	if(num_elements < size_of_queue) {	
		queue[num_elements] = item;
		++num_elements;
	}

	else if (num_elements == size_of_queue) {
		// throw "Deque is currently full... Growing it's size.";
		grow();
		push_back(item);
	}
}

string Deque::pop_front() {
	string tempString = queue[0];
	if (!empty()) {
		if (num_elements < size_of_queue/4 && size_of_queue > 8) {
			shrink();
			return pop_front();
		}

		else {
			for (unsigned i = 0; i < num_elements; ++i) {
				queue[i] = queue[i+1];
			}
			--num_elements;
			return tempString;
		}
	}

	else {
		// throw "Deque is currently empty";
		return "";
	}
}

string Deque::pop_back() {
	if (!empty()) {
		if (num_elements < size_of_queue/4 && size_of_queue > 8) {
			shrink();
			return pop_back();
		}

		else {
			std::string tempString = queue[num_elements];
			--num_elements;
			return tempString;
		}
	}

	else {
		// throw "Deque is currently empty";
		return "";
	}
}

int Deque::size() {
	return num_elements;
}

bool Deque::empty() {
	return size() == 0;
}

string Deque::toStr() {
	stringstream ss;
	if (empty()) {
		ss.str("Deque is currently empty\n");
	}

	else {
		for (int i = 0; i < num_elements; ++i) {
			ss << queue[i] << "\n";
		}		
	}
	cout << "test\n";
	std::string s = ss.str();
	return s;
}

void Deque::grow() {
	string *temp = new string[2*size_of_queue];
	size_of_queue *= 2;
	for (int i = 0; i < num_elements; ++i) {
		temp[i] = queue[i];
	}
	delete [] queue;
	queue = new string[size_of_queue];
	queue = temp;
}

void Deque::shrink() {
	string *other = new string[size_of_queue/2];
	size_of_queue = size_of_queue/2;
	for (int i = 0; i < num_elements; ++i) {
		other[i] = queue[i];
	}
	delete [] queue;
	queue = new string[size_of_queue];
	queue = other;	
}

