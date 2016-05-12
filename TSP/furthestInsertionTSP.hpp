#ifndef _FURTHEST_INSERTION_TSP_HPP_
#define _FURTHEST_INSERTION_TSP_HPP_

#include "TSP.h"

using namespace std;

class FurthestInsertion{
 
private :
  std::vector<long>* townsList;
  std::vector<long>* route;
  int size;
  int totalDist;
  
public :
  FurthestInsertion();
  FurthestInsertion(const TSPData &data);
  ~FurthestInsertion();
  std::pair <int, int> findFurthest(const TSPData &data);
  char* getPathString()const;
  int getSize()const;
  int getTotalDist()const;

  friend ostream& operator<<(ostream& os ,const FurthestInsertion& fi );

};

#endif
