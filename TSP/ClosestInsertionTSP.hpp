#ifndef _CLOSEST_INSERTION_TSP_HPP_
#define _CLOSEST_INSERTION_TSP_HPP_
#include <vector>
#include "TSP.h"

using namespace std;

class ClosestInsertion{
  vector<int> town;
  long ** matrix; 
  int current;
  int size;
  int closest;
public:
  
  ClosestInsertion(const TSPData&);
  ~ClosestInsertion();

  vector<int> path();

  

};

#endif

