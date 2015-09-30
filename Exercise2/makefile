all: Search

Search: Search.o Search-main.o
	g++ Search.o Search-main.o -o search

Search.o: Search.cpp Search.h
	g++ -c Search.cpp

Search-main.o: Search-main.cpp Search.h
	g++ -c Search-main.cpp

clean:
	rm -rf *.o
	rm -rf Search