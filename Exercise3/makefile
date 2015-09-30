all: hash-table

hash-table: hashtable.o hashmain.o
	g++ hashtable.o hashmain.o -o hash-table

hashtable.o: hashtable.cpp hashtable.h
	g++ -c hashtable.cpp

hashmain.o: hashmain.cpp hashtable.h
	g++ -c hashmain.cpp

clean:
	rm -rf *o
	rm -rf hash-table