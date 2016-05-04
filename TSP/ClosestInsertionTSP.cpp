#include "ClosestInsertionTSP.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>


ClosestInsertion::ClosestInsertion(const TSPData &data){
  matrix = data.getMatrix();
  int size = data.getSize();
  int i0 = rand()%(size);
  town.push_back(i0);
  int current = i0; // departure point
  int closest = size + 1; //initialization
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if (matrix[i][j] < closest)
	closest = matrix[i][j];
      town.push_back(closest);
      current = closest;
    } 
    
  }
  
}

ClosestInsertion::~ClosestInsertion(){}


