#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "TSP.h"
#include "decreasingArcTSP.hpp"
#include "closestInsertionTSP.hpp"
#include "furthestInsertionTSP.hpp"
#include "interfaceTSP.hpp"


void InterfaceTSP::run_decreasingArc(const TSPData &data){

	DecreasingArc DA(data);
	while(!DA.isEmpty()){

		Arc* next = DA.retrieveNext();
		if(next!= NULL){
			DA.addSelectedArc(*next);
		}
	}

	DA.constructPath(data);
	cout << DA << endl;
	cout << DA.getPathString() << endl;

}

void InterfaceTSP::run_closestInsertion(const TSPData &data){
  ClosestInsertion CI(data);
  CI.path();
  cout << CI << endl;
}



void InterfaceTSP::run_furthestInsertion(const TSPData &data){
	FurthestInsertion FI(data);
}