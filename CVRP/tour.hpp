#ifndef _TOUR_HPP_
#define _TOUR_HPP_

#include <list>
using namespace std;


/* This class implements a tour */ 
struct tour{
  list<char> clients_order;
  int id;
  int length;
  int size;
  int used_capacity;
};

#endif
