CC = g++
CFLAGS = -O3 -Wall -std=c++11
all: main.o Graph.o
	$(CC) -o program main.o Graph.o $(CFLAGS)

test: main_test.o Graph_test.o
	$(CC) -o test main_test.o Graph_test.o $(CFLAGS)

main.o: main.cpp Graph.h
	$(CC) -c $(CFLAGS) main.cpp

main_test.o: main.cpp Graph.h
	$(CC)  -o main_test.o -c $(CFLAGS) -DTEST main.cpp

Graph.o: Graph.cpp Graph.h
	$(CC) -c $(CFLAGS) Graph.cpp

Graph_test.o: Graph.cpp Graph.h
	$(CC) -o Graph_test.o -c $(CFLAGS) -DTEST Graph.cpp

clean:
	rm -f *.o