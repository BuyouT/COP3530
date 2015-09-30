#include "hashtable.h"

int main(int argc, char const *argv[]) {
	hashtable h;
	int op = -1;
	int size;
	string input;
	cin >> size;
	h.setSize(size);

	while (op != 0) {
		cin >> op;
		switch(op) {
			case 0:
				cin >> input;
				break;
			case 1:
				cin >> input;
				h.insert(input);
				break;
			case 2: 
				cin >> input;
				h.search(input);
				break;
			default:
				cout << "Not a valid int" << endl;
		}
	}
	
	return 0;
}