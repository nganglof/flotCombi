#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <list>
#include <cstring>
#include <functional>
#include <cstdio>
#include "clarkeWrightCVRP.hpp"
#include "tour.hpp"
#include "list_tour.hpp"
#include "CVRP.hpp"


/* Constructor initializes the object */ 

clarkeWrightCVRP::clarkeWrightCVRP(const CVRPData& data){
  Capacity = data.getCapacity();
  NbNodes = data.getSize();
  Distances = data.getDistances();
  Demands = data.getDemands();
  }

/*Destructor */ 
clarkeWrightCVRP::~clarkeWrightCVRP(){}



/* This method is useful to calculate the saving given a concatation between two tours */ 

int clarkeWrightCVRP::savingPerConcatetion(const CVRPData& data,struct tour i, struct tour j){
  int gain = 0;
  int before_value = i.length + j.length + data.getDistance(i.clients_order.back(),j.clients_order.front());
  printf("Avant le cout etait: %d\n",before_value);
  printf("le cout entre deux tours vaut : %d\n", data.getDistance(i.clients_order.back(),j.clients_order.front()));
  int after_value = i.length + j.length + data.getDistance(i.clients_order.back(),j.clients_order.front());
  printf("Apres le cout etait: %d\n",after_value);
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
	// create a tour made of single visit
	struct tour tmp_tour;
	tmp_tour.id = i;
	tmp_tour.clients_order.push_back(i + 'i');
	tmp_tour.length = 0;
	L.tour_list.push_back(tmp_tour);
	L.size++;
    }
    printf("La taille de L est: %d\n",L.size);
    printf("Jusque la cest bon !!!\n");
    int gain = 0;
    printf("gain init :%d\n", gain);

    while(thereAreConcatableLists(data,L)){
    
    
      struct tour tour_i;
      struct tour tour_j;
      struct tour tmp_i;
      struct tour tmp_j;
      list<char>::iterator it_i = tour_i.clients_order.begin();
      list<char>::iterator it_j = tour_j.clients_order.begin();
      list<struct tour>::iterator it_L = L.tour_list.begin();

      for(int i = 0 ; i < L.size ; i++){
	for(int j = 1; j < L.size - 1; j++){
	  advance(it_i,i);
	  advance(it_j,j);
	  if ( (i != j) && (savingPerConcatetion(data,tour_i,tour_j) > gain ))  {
	    gain = savingPerConcatetion(data,tour_i,tour_j); 
	    tmp_i = tour_i; //stock good candidates
	    tmp_j = tour_j;
	    
	    printf("gain trouve a : %d\n",gain);
	}
      }
    }
    // concate the two best tours
    //advance(it_i,tour_i.clients_order.end());
      if(gain != 0){
	tmp_i.clients_order.splice(tmp_i.clients_order.end(),tmp_j.clients_order); 
	tmp_i.length++;//updating size of first list
	tour_i.length ++;
	L.size--; //updating size of the set 
	printf("fusion de 2:%d\n", L.size);
      }
    }
    printf("Le nb final de tournees vaut: %d\n", L.size);
  //cout << res << endl;
}



/* This method return if there are at least two tours which can be concated */ 

bool clarkeWrightCVRP::thereAreConcatableLists(const CVRPData& data,struct list_tour L){  
  if ( (L.size != 0) && (L.size != 1)){
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


bool clarkeWrightCVRP::areConcatable(CVRPData& data,struct list_tour L ,struct tour tour_i, struct tour tour_j){
  list<struct tour>::iterator it_i = L.tour_list.begin();
  list<struct tour>::iterator it_j = L.tour_list.begin();
  if ( (*it_j).used_capacity + (*it_j).used_capacity < data.getCapacity())
    return true;
  return false;
}
