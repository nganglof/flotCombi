#include "ClosestInsertionTSP.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <limits.h>


ClosestInsertion::ClosestInsertion(const TSPData &data){
  visited = new set<int>();
  it = visited->begin(); 
  matrix = data.getMatrix();
  size = data.getSize();
  srand(time(NULL));
  length = 0;
  next_town = rand()%(size - 1); 
  
  closest = size + 1; 
  visited->insert(it,next_town);  
  nodesPath.push_back(next_town);
}

ClosestInsertion::~ClosestInsertion(){
  delete(visited);
}

void ClosestInsertion::path(){
  cout << "taille visited : " << visited->size() << " et size : " << size << endl;

  while((int)visited->size()<size){
    
    closest = INT_MAX;
    int closestTown = -1;

    for(int j = 0; j < size; j++){

      const bool is_in = visited->count(j);

      if ((matrix[next_town][j] < closest) && ( next_town != j) && (!is_in)){
	closest = matrix[next_town][j];
	closestTown = j;
      }
    }

    length += matrix[next_town][closestTown];
    next_town = closestTown;
    nodesPath.push_back(next_town);
    visited->insert(it,next_town);  
  }
  length+=matrix[nodesPath.back()][nodesPath.front()];
  nodesPath.push_back(nodesPath.front());
 
}



ostream& operator<<(ostream& os,const ClosestInsertion& ci )
{
	int i;
	int nodes = ci.size;

	for(i=0; i < nodes+1; i++) {
	  os << ci.nodesPath[i] << "\t" ;
	}
	os << " / taille total : "<< ci.length << endl;

    return os;
}
