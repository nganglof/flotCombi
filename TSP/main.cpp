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
#include "furthestInsertionTSP.hpp"

using namespace std;

void run_decreasingArc(const TSPData &data){

	DecreasingArc DA(data);
	while(!DA.isEmpty()){

		Arc* next = DA.retrieveNext();
		if(next!= NULL){
			DA.addSelectedArc(*next);
		}
	}

	DA.constructPath(data);
	cout << DA << endl;

}

void run_closestInsertion(const TSPData &data){
	ClosestInsertion CI(data);
	vector<int> v;
	v = CI.path();
	for(int i = 0; i < data.getSize(); i++){
		cout << "Town path" << endl;
		cout << "\n" << v[i];
	}
}


void run_furthestInsertion(const TSPData &data){
	FurthestInsertion FI(data);
}

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
		run_closestInsertion(data);
		break;

		case 2 :
			//algo 2 : decreasingArc
		run_decreasingArc(data);
		break;

		case 3 :
			//algo 3 : furthestInsertion
		run_furthestInsertion(data);
		break;

		case 4 :
			//comparaison des trois algo
	}

	toto.close();

	return 0;
}
