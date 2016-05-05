#include "ClosestInsertionTSP.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>


ClosestInsertion::ClosestInsertion(const TSPData &data){
  matrix = data.getMatrix();
  size = data.getSize();
  next_town = rand()%(size); 
  town.push_back(next_town);
  visited.insert(it,next_town);
  closest = size + 1; //initialization
  
}

ClosestInsertion::~ClosestInsertion(){}

vector<int> ClosestInsertion::path(){
  set<int> visited;
    for(int j = 0; j < size; j++){
      if ((matrix[next_town][j] < closest) && ( next_town != j) && (visited.find(j) != visited.end())){
	closest = matrix[next_town][j];	
      }
      next_town = j;
      visited.insert(it,next_town);
    town.push_back(next_town);
    
  }
  return town;
}
