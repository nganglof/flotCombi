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
#include "ClosestInsertionTSP.hpp"

using namespace std;


void run_decreasingArc(const TSPData &data){


	DecreasingArc DA(data);
	while(!DA.isEmpty()){

		Arc next = DA.retrieveNext();
		DA.addArcPath(next);
	}

	cout << DA << endl;

}

void run_closestInsertion(const TSPData &data){
  ClosestInsertion CI(data);
  
}

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
			run_decreasingArc(data);
			//DecreasingArc DA(data);
			break;

		case 3 :
			//algo 3 : furthestInsertion
			break;
	}

	toto.close();

	return 0;
}
