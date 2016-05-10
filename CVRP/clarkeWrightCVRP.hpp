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
  clarkeWrightCVRP(const TSPData&);
  ~clarkeWrightCVRP();
  void clarkeWrightProcedure(CVRPData);
  int savingPerConcatenation();


};

#endif
