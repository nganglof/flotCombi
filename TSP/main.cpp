//============================================================================
// Name        : TSP.cpp
// Author      : F.C.
// Version     :
// Copyright   : Free for all
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "TSP.h"
#include "decreasingArcTSP.hpp"
#include "closestInsertion.hpp"


using namespace std;

void usage (char* s){
  cout << "Usage: " << s << " <int> <data.tsp>" << endl;
  exit(EXIT_FAILURE);
}

#define PARAM 2
int main(int argc, char * argv[]) {


	// argv[1] methode
	// closest decreasing furthest
	//selon methode
    if (argc != PARAM+1) usage(argv[0]);

	fstream toto(argv[2], fstream::in);
	TSPData data(toto);

	switch(atoi(argv[1])){

		case 1 :
			//algo 1 : closestInsertion
			break;

		case 2 :
			//algo 2 : decreasingArc
			break;

		case 3 :
			//algo 3 : furthestInsertion
			break;
	}

	toto.close();

	return 0;
}
