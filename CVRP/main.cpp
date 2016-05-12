#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>


#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "CVRP.hpp"
#include "giantTourCVRP.hpp"
#include "clarkeWrightCVRP.hpp"
#include "../TSP/decreasingArcTSP.hpp"
#include "../TSP/furthestInsertionTSP.hpp"
#include "../TSP/closestInsertionTSP.hpp"

#include "../TSP/TSP.h"

using namespace std;


TSPData convertCVRPtoTSP(const CVRPData &data){

	TSPData convert(data.getSize(),data.getDistances());
	return convert; 
}

void run_clarkeWright(const CVRPData &data){
  clarkeWrightCVRP CWCVRP(data);
  CWCVRP.clarkeWrightProcedure(data);
  //cout << CWCVRP << endl;

}

char* retrieveTSP(int methode,const TSPData & data){
	
	char * path;
	if(methode==1){
  		ClosestInsertion CI(data);
  		CI.path();
  		path=CI.getPathString();
	}
	else if(methode==2){
		DecreasingArc DA(data);
		while(!DA.isEmpty()){
			Arc* next = DA.retrieveNext();
			if(next!= NULL){
				DA.addSelectedArc(*next);
			}
		}
		DA.constructPath(data);
		path = DA.getPathString();
	}
	else{
		FurthestInsertion FI(data);
		path=FI.getPathString();
	}
	return path;
}

void run_giantTour(const CVRPData &data, int methode){


	TSPData conv = convertCVRPtoTSP(data);
	char* path = retrieveTSP(methode,conv);

	GiantTour DA(data,path);
	
	DA.addShortcuts(data);
	DA.getShortestPath(data);
	DA.getTours(data);
	DA.displayTours();

	printf("methode : %d\n",methode);
}

void usage (char* s){
	cout << "Usage: " << s << " <int methode 1=clarkeWright, 2=giantTour> <data> <methode TSP pour cvrp (1,2,3)" << endl;
	exit(EXIT_FAILURE);
}

#define PARAM 2
int main(int argc, char * argv[]) {


	if (argc < PARAM+1) usage(argv[0]);

	CVRPData cvrp(argv[2]);

    printf("nb argu : %d\n",argc);
    int methode = 2; //methode par defaut
    if(argc>3){
    	methode = atoi(argv[3]);
    }

	switch(atoi(argv[1])){

		case 1 :
			//algo 1 : clarkeWright
			run_clarkeWright(cvrp);
		break;

		case 2 :
			//algo 2 : giantTour
			run_giantTour(cvrp,methode);
		break;

		case 3 :
			//comparaison des trois algo
		break;
	}

	return 0;
}
