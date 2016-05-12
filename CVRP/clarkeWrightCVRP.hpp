#ifndef _CLARKE_WRIGHT_CVRP_HPP_
#define _CLARKE_WRIGHT_CVRP_HPP_


#include "CVRP.hpp"

using namespace std;

class clarkeWrightCVRP{

  int Capacity;
  int NbNodes;
  int ** Distances;
  int * Demands;

public:
  clarkeWrightCVRP(const CVRPData&);
  ~clarkeWrightCVRP();
  int savingPerConcatetion(const CVRPData&,struct tour, struct tour);
  void clarkeWrightProcedure(const CVRPData&);

  bool thereAreConcatableLists(const CVRPData&,struct list_tour);

};

#endif
