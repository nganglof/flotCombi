#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <list>

#include "clarkeWrightCVRP.hpp"
#include "CVRP.hpp"
#include "tour.hpp"

clarkeWrightCVRP::clarkeWrightCVRP(const CVRPData&){}

clarkeWrightCVRP::~clarkeWrightCVRP(){}

void clarkeWrightCVRP::clarkeWrightProcedure(const CVRPData&){

  list<struct tour> L; // list of tours, will be the result at the end of the procedure
  for (int i = 0; i < NbNodes; i++){
    struct tour tmp_tour;
    tmp_tour.id = i;
    tmp_tour.clients_order.push_back(i + 'i');
  }
}

int clarkeWrightCVRP::savingPerConcatetion(){

  return 1;}

int clarkeWrightCVRP::areConcatable(struct tour t1, struct tour t2){

  return 1;}
