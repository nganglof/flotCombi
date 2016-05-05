#include "ClosestInsertionTSP.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>


ClosestInsertion::ClosestInsertion(const TSPData &data){
  visited = new set<int>();
  it = visited->begin(); 
  matrix = data.getMatrix();
  size = data.getSize();
  srand(time(NULL));
  next_town = rand()%(size - 1); 
  cout << "Departure :\n" << next_town; //initialization
  
  //visited.insert(it,next_town);
  cout << "end of initialization" << endl;
  closest = size + 1; 
  
  
}

ClosestInsertion::~ClosestInsertion(){
  delete(visited);
}

void ClosestInsertion::path(){
    for(int j = 0; j < size; j++){
      //cout << "Je suis ici" << j ;
      if ((matrix[next_town][j] < closest) && ( next_town != j) && (visited->find(j) == visited->end())){
	closest = matrix[next_town][j];	
      }
      next_town = j;
      visited->insert(it,next_town);    
  }
}
