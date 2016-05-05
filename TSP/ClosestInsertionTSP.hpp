#ifndef _CLOSEST_INSERTION_TSP_HPP_
#define _CLOSEST_INSERTION_TSP_HPP_
#include <vector>
#include <set>
#include "TSP.h"

using namespace std;

class ClosestInsertion{
  vector<int> town;
  long ** matrix; 
  int current;
  int size;
  int closest;
  int next_town;
  set<int> visited;
  set<int>::iterator it;
public:
  
  ClosestInsertion(const TSPData&);
  ~ClosestInsertion();

  vector<int> path();

  

};

#endif

