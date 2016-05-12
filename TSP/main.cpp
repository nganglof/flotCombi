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
#include <sys/time.h>

using namespace std;

unsigned long getTime(struct timeval tv1, struct timeval tv2){
	return (tv2.tv_sec-tv1.tv_sec)*1000000+(tv2.tv_usec-tv1.tv_usec);
}

void usage (char* s){
	cout << "Usage: " << s << " <int> <data.tsp>" << endl;
	exit(EXIT_FAILURE);
}

void run_decreasingArc(const TSPData &data){

  	struct timeval tv1, tv2;
  	gettimeofday(&tv1, NULL);

	DecreasingArc DA(data);
	while(!DA.isEmpty()){
		Arc* next = DA.retrieveNext();
		if(next!= NULL)
			DA.addSelectedArc(data,*next);
	}
	cout << DA;

	gettimeofday(&tv2, NULL);
	cout << "\tAlgorithme executé en " << getTime(tv1,tv2) << "ms" << endl;
}

void run_closestInsertion(const TSPData &data){

	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	ClosestInsertion CI(data);
	CI.path();
	cout << CI;

	gettimeofday(&tv2, NULL);
	cout << "\tAlgorithme executé en " << getTime(tv1,tv2) << "ms" << endl;
}

void run_furthestInsertion(const TSPData &data){

	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	FurthestInsertion FI(data);
  	cout << FI;

	gettimeofday(&tv2, NULL);
	cout << "\tAlgorithme executé en " << getTime(tv1,tv2) << "ms" << endl;
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
			run_closestInsertion(data);
			run_decreasingArc(data);
			run_furthestInsertion(data);
		break;
	}

	toto.close();

	return 0;
}
