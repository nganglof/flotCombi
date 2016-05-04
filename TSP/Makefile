
CC = g++
CFLAGS  = -Wall
LDFLAGS = 

default: main

main: main.cpp arc.o decreasingArcTSP.o ClosestInsertionTSP.o
	$(CC) $(CFLAGS) -o $@ $^

decreasingArcTSP.o: decreasingArcTSP.cpp
	$(CC) $(CFLAGS) -o decreasingArcTSP.o -c decreasingArcTSP.cpp

ClosestInsertionTSP.o: ClosestInsertionTSP.cpp
	$(CC) $(CFLAGS) -o ClosestInsertionTSP.o -c ClosestInsertionTSP.cpp

furthestInsertionTSP.o: furthestInsertionTSP.cpp
	$(CC) $(CFLAGS) -o furthestInsertionTSP.o -c furthestInsertionTSP.cpp

arc.o: arc.cpp
	$(CC) $(CFLAGS) -o arc.o -c arc.cpp


clean:
	rm -rf *.o a.out
