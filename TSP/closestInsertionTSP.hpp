#ifndef _CLOSEST_INSERTION_TSP_HPP_
#define _CLOSEST_INSERTION_TSP_HPP_
#include <vector>
#include <set>
#include "TSP.h"

using namespace std;

class ClosestInsertion{
  
  private: 
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
    
    void path();

    char* getPathString()const;
    int getSize() const;
    float getLength() const;
    friend ostream& operator<<(ostream& os ,const ClosestInsertion& ci );
};

#endif

