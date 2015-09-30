#include "Search.h"

Search::Search() {
	bigElem = 0;
	smallElem = 0;
}

Search::~Search() {
	delete [] bigArray;
	delete [] smallArray;
}

void Search::sSearch(int n, int s) {
	bigArray = new int[n];
	smallArray = new int[s];
}

void Search::fillBigArray(int num) {
	bigArray[bigElem] = num;
	++bigElem;
}

void Search::fillSmallArray(int num) {
	smallArray[smallElem] = num;
	++smallElem;
}

void Search::printArray() {
	// Check if the numbers are being put inside the array
	cout << "Big Array\n";
	for (int i = 0; i < bigElem; ++i) {
		cout << bigArray[i] << endl;
	}

	cout << "Small Array\n";
	for (int i = 0; i < smallElem; ++i) {
		cout << smallArray[i] << endl;
	}
}

void Search::linear() {
	bool found = false; //Used to check if element is found
	for (int i = 0; i < smallElem; ++i) {
		for (int j = 0; j < bigElem; ++j) {
			// Check if the value is in the array
			if (smallArray[i] == bigArray[j]) {
				cout << "Yes" << endl;
				found = true; 
			}
		}
		// Go through here if not found
		if(!found) {
			cout << "No" << endl;
		}
		found = false;
	}
}

void Search::sortArray() {
	sort(bigArray, bigArray+bigElem);
}

bool Search::binary(int value) {
	int low = 0; //First index
	int high = bigElem-1; //Last index
	bool found = false; //Check if it's been found
	while (low <= high) {
		int mid = low + (high-low)/2; //Position of the array starting at mid-point
		if (bigArray[mid] == value) {
			found = true;
			return true;
		}
		else if (bigArray[mid] < value) {
			// If the value is greater than the mid-point check upper half
			low = mid + 1;
		}

		else {
			// If the value is greater than the mid-point check bottom half
			high = mid - 1;
		}
	}

	if (!found) {
		return false;
	}
}

void Search::checkBinary() {
	for (int i = 0; i < smallElem; ++i) {
		if (binary(smallArray[i])) {
			// Value was found
			cout << "Yes" << endl;
		}

		else {
			// Value is not in the array
			cout << "No" << endl;
		}
	}
}