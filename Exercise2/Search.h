// Linear vs Binary search
// Descritption: A comparison between linear O(n) vs binary O(log(n)) search
// Author: Ricardo Stefano Reyna
// Version: 1.0.0
// Date: 19/Mar/2015
// Copywrite: Stefano Reyna

#ifndef SEARCH_H
#define SEARCH_H
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Search {
private:
	int *bigArray; //Array containing all numbers
	int *smallArray; //Array containing searching numbers
	int bigElem; //Number of elements in big array
	int smallElem; //Number of elements in small array
public:
	Search(); //Constructor
	~Search(); //Destructor
	void sSearch(int n, int s); //Set size of both arrays
	void fillBigArray(int num); //Fill the big array with numbers
	void fillSmallArray(int num); //Fill the small array with search numbers
	void printArray(); //Print the array (Testing purpose)
	void linear(); //Linear search method
	void sortArray(); //Sort the big array
	bool binary(int value); //Binary search method
	void checkBinary(); //Loop through each element of the small array and call binary()
};

#endif