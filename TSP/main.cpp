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
#include <vector>

#include "TSP.h"
#include "decreasingArcTSP.hpp"
#include "closestInsertionTSP.hpp"
#include "furthestInsertionTSP.hpp"
#include "interfaceTSP.hpp"

using namespace std;


void usage (char* s){
	cout << "Usage: " << s << " <int> <data.tsp>" << endl;
	exit(EXIT_FAILURE);
}

#define PARAM 2
int main(int argc, char * argv[]) {


	if (argc != PARAM+1) usage(argv[0]);

	fstream toto(argv[2], fstream::in);
	TSPData data(toto);

	switch(atoi(argv[1])){

		case 1 :
			//algo 1 : closestInsertion
			InterfaceTSP::run_closestInsertion(data);
		break;

		case 2 :
			//algo 2 : decreasingArc
			InterfaceTSP::run_decreasingArc(data);
		break;

		case 3 :
			//algo 3 : furthestInsertion
			InterfaceTSP::run_furthestInsertion(data);
		break;

		case 4 :
			//comparaison des trois algo
		break;
	}

	toto.close();

	return 0;
}
