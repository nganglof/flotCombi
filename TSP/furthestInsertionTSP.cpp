#include "TSP.h"
#include <iostream>
#include <vector>
#include <iterator>
//#include <array>
#include <cstdio>
#include <cstdlib>
#include "furthestInsertionTSP.hpp"
#include <utility>
#include <algorithm>
#include <string.h>

FurthestInsertion::FurthestInsertion(){

}

FurthestInsertion::FurthestInsertion(const TSPData &data){
  size = data.getSize();
  townsList = new std::vector<long>();
   for(int i = 0; i < size; i++){
    townsList->push_back(i);
  }  
  totalDist = 0;
  route = new std::vector<long>();
  
  //Init
  std::pair <int, int> furthest = findFurthest(data);
  route->push_back(furthest.first);
  townsList->erase(townsList->begin() + furthest.first);//Remove 'first'th element
  route->push_back(furthest.second);
  if(furthest.first > furthest.second)
    townsList->erase(townsList->begin() + furthest.second);//Remove 'second'th element
  else
    townsList->erase(townsList->begin() + furthest.second - 1);
  
  //Algo
  int furthestTown;
  int bestInsertionTmp;
  int bestInsertion;
  int zTmp;
  int z = -1;
  int maxCost = -1;
  int bestTown;
  int bestTownIndex = -1;
  //while client dans townsList do
  while(!townsList->empty()){
  //for i dans townsList do
    furthestTown = -1;
    bestInsertionTmp = -1;
    maxCost = -1;
    z = -1;
    for (std::vector<long>::iterator iter = townsList->begin(); iter != townsList->end(); ++iter){
      int i = std::distance(townsList->begin(), iter);
      if(furthestTown < 0)
	     furthestTown = i;
      for(std::vector<long>::iterator jter = route->begin(); jter != route->end(); ++jter){
	int j = std::distance(route->begin(), jter);
	if(j == 0){
	  zTmp = (data.getVal(route->at(std::distance(route->begin(), route->end()) - 1), townsList->at(i)) + data.getVal(route->at(0), townsList->at(i))) - data.getVal(route->at(std::distance(route->begin(), route->end()) - 1), route->at(0));
	}
	else{
	  zTmp = (data.getVal(route->at(j), townsList->at(i)) + data.getVal(townsList->at(i), route->at(j-1))) - data.getVal(route->at(j),route->at(j-1));
	}
	if((z > zTmp) || (z == -1)){//min
	  bestInsertionTmp = j;
	  z = zTmp;
	}
      }
      if((maxCost < z) || (maxCost == -1)){
	maxCost = z;
	bestInsertion = bestInsertionTmp;
	bestTown = townsList->at(i);
     	bestTownIndex = i;
      }
    }
    //prendre i,j tq z_i max , retirer dans townsList et ajouter dans route
    route->insert(route->begin() + bestInsertion, bestTown);
    townsList->erase(townsList->begin() + bestTownIndex);
  }

  for(std::vector<long>::iterator iter = route->begin(); iter != route->end(); ++iter){
    int i = std::distance(route->begin(), iter);
    if(i > 0)
      totalDist += data.getVal(route->at(i), route->at(i-1));
    else if (i == 0){
      totalDist += data.getVal(route->at(i), route->at(std::distance(route->begin(), route->end()) - 1));
    }
  } 
}

FurthestInsertion::~FurthestInsertion(){
  delete(townsList);
  delete(route);
}
 
std::pair <int, int> FurthestInsertion::findFurthest(const TSPData &data){
  std::pair <int, int> furthest;
  long distance = -1;
  furthest = std::make_pair(0,0);
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(i == j)
	continue;
      else{
	if(distance <= data.getVal(i,j) || distance == -1){
	  distance = data.getVal(i,j);
	  furthest = std::make_pair(i, j); 
	}
      }
    }
  }
  return furthest;
}


char* FurthestInsertion::getPathString() const{

  char* path = new char[size];
  memset(path,'\0',size);
  for(std::vector<long>::iterator iter = route->begin(); iter != route->end(); ++iter){
    int i = std::distance(route->begin(), iter);
    asprintf(&path,"%s%ld,",path,route->at(i));
  } 
  asprintf(&path,"%s%ld",path,route->front());

  return path;
}

int FurthestInsertion::getTotalDist() const{
  return totalDist;
}

int FurthestInsertion::getSize() const{
  return size;
};

ostream& operator<<(ostream& os,const FurthestInsertion& fi )
{
  os << "FurthestInsertion" << endl;
  os << "\tNodes number : " << fi.getSize() << endl;
  os << "\tPath : " << fi.getPathString() << endl;
  os << "\tTotal distance : " << fi.getTotalDist() << endl;
  return os;
}