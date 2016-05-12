#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <list>
#include <cstring>

#include "clarkeWrightCVRP.hpp"
#include "tour.hpp"
#include "list_tour.hpp"
#include "CVRP.hpp"


/* Constructor initializes the object */ 

clarkeWrightCVRP::clarkeWrightCVRP(const CVRPData& data){}

/*Destructor */ 
clarkeWrightCVRP::~clarkeWrightCVRP(){}



/* This method is useful to calculate the saving given a concatation between two tours */ 

int clarkeWrightCVRP::savingPerConcatetion(const CVRPData& data,struct tour i, struct tour j){
  int gain = 0;
  list<char>::iterator it_i = i.clients_order.begin();
  list<char>::iterator it_j = j.clients_order.begin();
  int before_value = i.length + j.length + data.getDistance(*i.clients_order.end(),*j.clients_order.begin());
  int after_value = i.length + j.length + data.getDistance(*i.clients_order.end(),*j.clients_order.begin());
  gain = before_value - after_value;

  return gain;
}

/* This method runs the Clarke & Wright procedure to build an approximative solution */ 

void clarkeWrightCVRP::clarkeWrightProcedure(const CVRPData& data){
  struct list_tour L;


    L.size = 0; // tour_list is empty by default
    L.name = new char[strlen("Liste resultat")];
    strcpy(L.name,"Liste resultat");
    for(int i=0; i < data.getSize(); i++){
      for(int j= 0; j < data.getSize(); j++){
	// create a tour made of single visit
	struct tour tmp_tour;
	tmp_tour.id = i;
	tmp_tour.clients_order.push_back(i + 'i');
	tmp_tour.length = 0;
	
	L.tour_list.push_back(tmp_tour);
      }
    }
    while(thereAreConcatableLists(data,L)){
    int gain = 0;
    struct tour tour_i;
    struct tour tour_j;
    list<char>::iterator it_i = tour_i.clients_order.begin();
    list<char>::iterator it_j = tour_j.clients_order.begin();
    list<struct tour>::iterator it_L = L.tour_list.begin();
    for(int i = 0 ; i < L.size ; i++){
      for(int j = 0; j < L.size; j++){
	advance(it_i,i);
	advance(it_j,j);
	if ( (i != j) && (savingPerConcatetion(data,tour_i,tour_j)> gain ))  {
	  tour_j.id = j; //stock good candidates
	  tour_i.id = i;
	  gain = savingPerConcatetion(data,tour_i,tour_j);                                      
	}
      }
    }
    // concate the two best tours
    // L.list_tour[tour_i].splice(list_tour[tour_i].end(),list_tour[tour_j].begin()); 
    tour_i.length++;
    L.size--; //updating size of the set 
    
  }

  //cout << res << endl;
}



/* This method return if there are at least two tours which can be concated */ 

bool clarkeWrightCVRP::thereAreConcatableLists(const CVRPData& data,struct list_tour L){  
  if ( (L.size != 0) ){
    list<struct tour>::iterator it_i = L.tour_list.begin();
    list<struct tour>::iterator it_j = L.tour_list.begin();
    for(int i = 0 ; i < L.size; i++){
      for(int j = 1; j < L.size - 1; j++){
	advance(it_i,i);
	advance(it_j,j);
	if ( (*it_j).used_capacity + (*it_j).used_capacity < data.getCapacity())
	  return true;
      }
    }
    return false;
  }
  else
    return false;
}
