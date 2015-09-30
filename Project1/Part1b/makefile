all: tDeque

tDeque: tDeque_main.o
	g++ tDeque_main.o -o tDeque

tDeque_main.o: tDeque_main.cpp tDeque.h
	g++ -c tDeque_main.cpp

clean:
	rm -rf *.o
	rm -rf tDeque