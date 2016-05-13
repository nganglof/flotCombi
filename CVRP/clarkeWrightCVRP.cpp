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

  int before_value = i.length + j.length;

  int after_value = i.length + j.length + data.getDistance(getiFroma(i.clients_order.back()),getiFroma(j.clients_order.front()));
  after_value -= data.getDistance(getiFroma(i.clients_order.back()),0);
  after_value -= data.getDistance(0,getiFroma(i.clients_order.front()));

  int gain = after_value - before_value;

  return gain;
}

/* This method runs the Clarke & Wright procedure to build an approximative solution */ 

void clarkeWrightCVRP::clarkeWrightProcedure(const CVRPData& data){
    
    struct list_tour L;

    L.size = 0; // tour_list is empty by default
    L.name = new char[strlen("Liste resultat")];
    strcpy(L.name,"Liste resultat");
    for(int i=1; i < data.getSize(); i++){
    	// create a tour made of single visit
    	struct tour tmp_tour;
    	tmp_tour.id = i-1;
    	tmp_tour.clients_order.push_back(i + '0');
    	tmp_tour.size = 1;
      tmp_tour.length = data.getDistance(i,0) + data.getDistance(0,i);
    	tmp_tour.used_capacity = data.getDemand(i);
    	L.tour_list.push_back(tmp_tour);
    	L.size++;
    }

    list<tour>::iterator it = L.tour_list.begin();
    for(unsigned int i=0 ; i<L.tour_list.size();i++){
        advance(it,1);
    }

    int gain = -1;
    int tmpPos;

    bool wasConcat = true; 

    while(wasConcat){
    
      gain = -1;
      wasConcat = false;

      list<struct tour>::iterator it_Li_keeped;
      list<struct tour>::iterator it_Lj_keeped;
      list<struct tour>::iterator it_Li = L.tour_list.begin();
      list<struct tour>::iterator it_Lj = L.tour_list.begin();
      advance(it_Lj,1);

      for(int i = 0 ; i < (L.size -1) ; i++){

       for(int j = 1; j < L.size; j++){


        int tmp_gain = savingPerConcatetion(data,(*it_Li),(*it_Lj));
        int concat = areConcatable(data,L,(*it_Li),(*it_Lj));

         if ( ((*it_Li).id != (*it_Lj).id)
              && ( concat )
              && ( tmp_gain > gain )) {

	         it_Lj_keeped = it_Lj;
           it_Li_keeped = it_Li;
           tmpPos = j ;
           gain = tmp_gain;
          }

         advance(it_Lj,1);

        }
        it_Lj = L.tour_list.begin();
        advance(it_Lj,1);
        advance(it_Li,1);
      }

    // concate the two best tours

    if(gain >= 0){
        wasConcat = true;

        int tailleij = data.getDistance(getiFroma((*it_Li_keeped).clients_order.back()),getiFroma((*it_Lj_keeped).clients_order.front()));
        int taillei0 = data.getDistance(getiFroma((*it_Li_keeped).clients_order.front()),0);
        int taille0j = data.getDistance(0,getiFroma((*it_Lj_keeped).clients_order.front()));

      	(*it_Li_keeped).clients_order.splice((*it_Li_keeped).clients_order.end(),(*it_Lj_keeped).clients_order);
        (*it_Li_keeped).used_capacity += (*it_Li_keeped).used_capacity;
        (*it_Li_keeped).size++;//updating size of first list
        (*it_Li_keeped).length = (*it_Li_keeped).length + (*it_Lj_keeped).length;
        
        (*it_Li_keeped).length = (*it_Li_keeped).length +tailleij - taille0j - taillei0;

        list<tour>::iterator iterase = L.tour_list.begin();
        advance(iterase,tmpPos);
        L.tour_list.erase(iterase);

      	L.size--; //updating size of the set 
      }
    }
    printf("Le nb final de tournees vaut: %d\n", L.size);
    displayTour(L);
}


int clarkeWrightCVRP::getiFroma(char c){
    return c - '0';
}

void clarkeWrightCVRP::displayTour(struct list_tour L){

  list<struct tour>::iterator it = L.tour_list.begin();
  printf("j'ai %d tournées\n",L.size);
  int totalLength = 0 ;
  for (unsigned int i = 0; i < L.tour_list.size(); ++i)
  {
    totalLength += (*it).length;
    printf("Tournée %d d'id %d de distance %d\n",i,(*it).id,(*it).length);
    list<char>::iterator it2 = (*it).clients_order.begin();
    for (int j = 0; j < (*it).size; ++j){
      printf("\tclient %c\n",(*it2));
      advance(it2,1);
    }
    advance(it,1);
  }
  printf("de distance total %d\n",totalLength);
}

/* This method return if there are at least two tours which can be concated */ 

bool clarkeWrightCVRP::thereAreConcatableLists(const CVRPData& data,struct list_tour L){  
  if ( (L.size != 0) && (L.size != 1)){
    list<struct tour>::iterator it_i = L.tour_list.begin();
    list<struct tour>::iterator it_j = L.tour_list.begin();

    advance(it_j,1);
    for(int i = 0 ; i < L.size; i++){
      for(int j = 1; j < L.size - 1; j++){

      	if ( ((*it_j).id != (*it_i).id) && (((*it_j).used_capacity + (*it_j).used_capacity) <= data.getCapacity())){
      	  return true;
      	}
        advance(it_i,1);
        advance(it_j,1);        
      }
    }
    return false;
  }
  else
    return false;
}


bool clarkeWrightCVRP::areConcatable(const CVRPData& data,struct list_tour L ,struct tour tour_i, struct tour tour_j){

  return ((tour_j.used_capacity + tour_i.used_capacity) <= data.getCapacity());

}
