#ifndef _DECREASING_ARC_TSP_HPP_
#define _DECREASING_ARC_TSP_HPP_

using namespace std;

class decreasingArc{
  template < class T, class Alloc = allocator<T> > class vector;
  int cpt = 1; 
public:
  
  decreasingArc();
  ~decreasingArc();
  void path(vector <int> Sommets);
}







#endif
