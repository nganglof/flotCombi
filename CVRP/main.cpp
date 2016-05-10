#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "CVRP.hpp"
#include "giantTourCVRP.hpp"
#include "clarkeWrightCVRP.hpp"
#include "../TSP/interfaceTSP.hpp"
#include "../TSP/TSP.h"

using namespace std;


TSPData convertCVRPtoTSP(const CVRPData &data){

	TSPData convert(data.getSize(),data.getDistances());
	return convert; 
}

void run_clarkeWright(const CVRPData &data){

}

char* retrieveTSP(int i,const TSPData & data){

	char * path;
	DecreasingArc DA(data);
	while(!DA.isEmpty()){

		Arc* next = DA.retrieveNext();
		if(next!= NULL){
			DA.addSelectedArc(*next);
		}
	}
	DA.constructPath(data);
	path = DA.getPathString();
	return path;
}



void run_giantTour(const CVRPData &data){


	TSPData conv = convertCVRPtoTSP(data);
	char* path = retrieveTSP(2,conv);

	GiantTour DA(data,path);

	/*
	while(!DA.isEmpty()){

		Arc* next = DA.retrieveNext();
		if(next!= NULL){
			DA.addSelectedArc(*next);
		}
	}

	DA.constructPath(data);
	cout << DA << endl;*/

}

void usage (char* s){
	cout << "Usage: " << s << " <int> <data>" << endl;
	exit(EXIT_FAILURE);
}

#define PARAM 2
int main(int argc, char * argv[]) {


	if (argc != PARAM+1) usage(argv[0]);

	CVRPData cvrp(argv[2]);
    //std::cout << cvrp << std::endl;

	switch(atoi(argv[1])){

		case 1 :
			//algo 1 : clarkeWright
			//run_clarkeWright(cvrp);
		break;

		case 2 :
			//algo 2 : giantTour
			run_giantTour(cvrp);
		break;

		case 4 :
			//comparaison des trois algo
		break;
	}

	return 0;
}
