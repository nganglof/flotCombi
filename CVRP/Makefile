
CC = g++
CFLAGS  = -Wall -g
LDFLAGS = 

default: clean main

main: main.cpp CVRP.o giantTourCVRP.o clarkeWrightCVRP.o
	$(CC) $(CFLAGS) -o $@ $^

giantTourCVRP.o: giantTourCVRP.cpp
	$(CC) $(CFLAGS) -o giantTourCVRP.o -c giantTourCVRP.cpp

clarkeWrightCVRP.o: clarkeWrightCVRP.cpp
	$(CC) $(CFLAGS) -o clarkeWrightCVRP.o -c clarkeWrightCVRP.cpp

CVRP.o: CVRP.cpp
	$(CC) $(CFLAGS) -o CVRP.o -c CVRP.cpp


clean:
	rm -rf *.o a.out
