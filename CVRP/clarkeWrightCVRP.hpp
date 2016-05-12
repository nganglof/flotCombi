#ifndef _CLARKE_WRIGHT_CVRP_HPP_
#define _CLARKE_WRIGHT_CVRP_HPP_


#include "CVRP.hpp"
#include "tour.hpp"
#include "list_tour.hpp"

/*This class implements Clarke & Wright algorithm */ 


using namespace std;

class clarkeWrightCVRP{


  /* Attributes */ 
  int Capacity;
  int NbNodes;
  int ** Distances;
  int * Demands;




  /*Methods*/ 


public:
  clarkeWrightCVRP(const CVRPData&);
  ~clarkeWrightCVRP();
  int savingPerConcatetion(const CVRPData&,struct tour, struct tour);
  void clarkeWrightProcedure(const CVRPData&);

  bool thereAreConcatableLists(const CVRPData&,struct list_tour);
  bool areConcatable(const CVRPData&,struct list_tour L, struct tour, struct tour);
};

#endif
