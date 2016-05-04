#include "closestInsertionTSP.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>


closestInsertion::closestInsertion(TSPData data){
  vector<int> town;
  long ** matrix = data.getMatrix();
  int size = data.getSize();
  int i0 = rand()%(size);
  town.push_back(i0);
  
  


}

closestInsertion::~closestInsertion(){}


