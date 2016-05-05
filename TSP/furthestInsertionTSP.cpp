#include "TSP.h"
#include <iostream>
#include <vector>
#include <iterator>
//#include <array>
#include <cstdio>
#include "furthestInsertionTSP.hpp"
#include <utility>

FurthestInsertion::FurthestInsertion(){

}

FurthestInsertion::FurthestInsertion(const TSPData &data){
  size = data.getSize();
  townsList = new std::vector<long>();
   for(int i = 0; i < size; i++){
    townsList->push_back(i);
  }  

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
  std::cout << "Removed: " << furthest.first;
  std::cout << " and " << furthest.second;
  std::cout << "\n";
  
  //Algo
  int furthestTown;
  int bestInsertionTmp;
  int bestInsertion;
  int zTmp;
  int z = -1;
  int maxCost = -1;
  int bestTown;
  //while client dans townsList do
  while(!townsList->empty()){
  //for i dans townsList do
    furthestTown = -1;
    bestInsertionTmp = -1;
    maxCost = -1;
    for (std::vector<long>::iterator iter = townsList->begin(); iter != townsList->end(); ++iter){
      int i = std::distance(townsList->begin(), iter);
      if(furthestTown < 0)
	furthestTown = i;
      for(std::vector<long>::iterator jter = route->begin(); jter != route->end(); ++jter){
	//Don't need to check last insertion, same than beginning)
	//prendre max z_i de la meilleure insertion pour i: pour chaque arc (k,l) du circuit, calculer cout remplacer (k,l) par (k,i) + (i,l), garder insertion j
	int j = std::distance(route->begin(), jter);
	std::cout << "j : " << j << "\n";
	std::cout << "dist: " << std::distance(route->begin(), route->end()) << "\n";
	if(j == 0)
	  zTmp = (data.getVal(std::distance(route->begin(), route->end()) - 1, townsList->at(i)) + data.getVal(route->at(0), townsList->at(i))) - data.getVal(std::distance(route->begin(), route->end()) - 1, route->at(0));
	else
	  zTmp = (data.getVal(route->at(j), townsList->at(i)) + data.getVal(townsList->at(i), route->at(j-1))) - data.getVal(route->at(j),route->at(j-1));
	std::cout << "zTmp: " << zTmp << "\n";
	if(z > zTmp || z == -1){//min
	  bestInsertionTmp = j;
	  z = zTmp;
	  std::cout << "z: " << z << "\n";
	  std::cout << "Insertion: " << bestInsertionTmp << "\n";
	}
      }
      if(maxCost <= z || maxCost == -1){
	maxCost = z;
	bestInsertion = bestInsertionTmp;
	bestTown = i;
      }
    }
  //prendre i,j tq z_i max , retirer dans townsList et ajouter dans route
    route->insert(route->begin() + bestInsertion, bestTown);
    std::cout << "erasing ";
    std::cout << bestTown;
    std::cout << "\n";
    townsList->erase(townsList->begin() + bestTown);
  }
  //Print route
  std::cout << "Furthest insertion\n";
  std::cout << "Sorted list of towns:\n";
  long totalDist = 0;
  for(std::vector<long>::iterator iter = route->begin(); iter != route->end(); ++iter){
    int i = std::distance(route->begin(), iter);
    std::cout << "Town: ";
    std::cout << route->at(i);
    std::cout << "\n";
    if(i > 0)
      totalDist += data.getVal(route->at(i), route->at(i-1));
    else if (i == 0){
      totalDist += data.getVal(route->at(i), route->at(std::distance(route->begin(), route->end()) - 1));
    }
  } 
  std::cout << "Total distance:\n";
  std::cout << totalDist;
  std::cout << "\n";
  std::cout << "End\n";
  
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
	if(distance >= data.getVal(i,j) || distance == -1){
	  distance = data.getVal(i,j);
	  furthest = std::make_pair(i, j); 
	}
      }
    }
  }
  return furthest;
}
