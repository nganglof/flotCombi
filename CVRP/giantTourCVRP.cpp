#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "giantTourCVRP.hpp"
#include <limits.h>
#include "arcCVRP.hpp"

GiantTour::GiantTour(){


}

GiantTour::GiantTour(const CVRPData &data, char* path){

	nodes = data.getSize();
	TSPpath = new int[nodes];
	int cpt=0;
	char* tmp =  strtok( path,",");

	while(tmp!=NULL){
		TSPpath[cpt]=atoi(tmp);
		cpt++;
		tmp = strtok(NULL,",");
	}

	for(unsigned int i=0;i<nodes;i++){
		cout << "case" << i << ": " << TSPpath[i] << endl;
	}
}

GiantTour::~GiantTour(){


}


void GiantTour::getShortestPath(const CVRPData &data){

	std::vector<ArcCVRP> shortestPath;
	std::vector<int> treatedNodes;
	treatedNodes.push_back(0);

	int distFromStart[nodes];
	distFromStart[0]=0;
	
	for(unsigned int i=1;i<nodes;i++){
		distFromStart[i]= INT_MAX;
	}

	while(treatedNodes.size()< nodes){

		for (std::vector<ArcCVRP>::iterator it = arcs.begin() ; it != arcs.end(); ++it){



		}
	}
}



/*
ostream& operator<<(ostream& os ,const GiantTour& gt ){

	return os;
}*/