#include "Search.h"

int main() {
	Search s;
	int NE; //Number of elements in total
	int NS; //Number of elements to search
	int nNum; //Each element in the big array
	int sNum; //Each element in the small array
	clock_t start, finish;
	double elapsed_time;

	cin >> NE;
	cin >> NS;

	s.sSearch(NE, NS); //Creating array sizes

	// Fills in the big array
	for (int i = 0; i < NE; ++i) {
		cin >> nNum;
		s.fillBigArray(nNum);
	}

	// Fills in the small array
	for (int i = 0; i < NS; ++i) {
		cin >> sNum;
		s.fillSmallArray(sNum);
	}

	// s.printArray();

	cout << "Linear Search:\n";
	start = clock(); //Start clock
	s.linear();
	finish = clock(); //Stop clock
	elapsed_time = ((double)finish - start)/CLOCKS_PER_SEC;
	cout << "Time: " << elapsed_time << endl;

	s.sortArray();

	cout << "Binary Search:\n";
	start = clock(); //Start clock
	s.checkBinary();
	finish = clock(); //Stop clock
	elapsed_time = ((double)finish - start)/CLOCKS_PER_SEC;
	cout << "Time: " << elapsed_time << endl;

	return 0;
}