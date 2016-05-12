#ifndef _FURTHEST_INSERTION_TSP_HPP_
#define _FURTHEST_INSERTION_TSP_HPP_

#include "TSP.h"

using namespace std;

class FurthestInsertion{
 
private :
  std::vector<long>* townsList;
  std::vector<long>* route;
  int size;
  
public :
  FurthestInsertion();
  FurthestInsertion(const TSPData &data);
  ~FurthestInsertion();
  std::pair <int, int> findFurthest(const TSPData &data);

  char* getPathString();
};

#endif
