
CC = g++
CFLAGS  = -Wall -g
LDFLAGS = 

TSP = ../TSP/decreasingArcTSP.o ../TSP/arc.o ../TSP/closestInsertionTSP.o ../TSP/furthestInsertionTSP.o

default: clean main

main: main.cpp CVRP.o giantTourCVRP.o arcCVRP.o
	$(CC) $(CFLAGS) -o $@  $^ $(TSP)

CVRP.o: CVRP.cpp
	$(CC) $(CFLAGS) -o CVRP.o -c CVRP.cpp

clarkeWrightCVRP.o: clarkeWrightCVRP.cpp
	$(CC) $(CFLAGS) -o clarkeWrightCVRP.o -c clarkeWrightCVRP.cpp


#____________________________________________________GIANTTOUR


giantTourCVRP.o: giantTourCVRP.cpp
	$(CC) $(CFLAGS) -o giantTourCVRP.o -c giantTourCVRP.cpp

arcCVRP.o: arcCVRP.cpp
	$(CC) $(CFLAGS) -o arcCVRP.o -c arcCVRP.cpp

#____________________________________________________


clean:
	rm -rf *.o a.out
