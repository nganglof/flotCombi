
CC = g++
CFLAGS  = -Wall -g
LDFLAGS = 

default: clean main

main: main.cpp arc.o decreasingArcTSP.o closestInsertionTSP.o furthestInsertionTSP.o
	$(CC) $(CFLAGS) -o $@ $^

decreasingArcTSP.o: decreasingArcTSP.cpp
	$(CC) $(CFLAGS) -o decreasingArcTSP.o -c decreasingArcTSP.cpp

closestInsertionTSP.o: closestInsertionTSP.cpp
	$(CC) $(CFLAGS) -o closestInsertionTSP.o -c closestInsertionTSP.cpp

furthestInsertionTSP.o: furthestInsertionTSP.cpp
	$(CC) $(CFLAGS) -o furthestInsertionTSP.o -c furthestInsertionTSP.cpp

arc.o: arc.cpp
	$(CC) $(CFLAGS) -o arc.o -c arc.cpp
	
clean:
	rm -rf *.o a.out
