#ifndef _CLOSEST_INSERTION_TSP_HPP_
#define _CLOSEST_INSERTION_TSP_HPP_
#include <vector>
#include <set>
#include "TSP.h"

using namespace std;

class ClosestInsertion{
public: 
  long ** matrix; 
  int current;
  int size;
  int closest;
  int next_town;
  set<int> *visited;
  set<int>::iterator it;
  vector<int> nodesPath;
  float length;
public:
  
  ClosestInsertion(const TSPData&);
  ~ClosestInsertion();
  char* getPathString();
  
  friend ostream& operator<<(ostream& os ,const ClosestInsertion& ci );

  void path();

  

};

#endif

