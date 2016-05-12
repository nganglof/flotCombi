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

  printf("\tcoucou\n");
  printf("\tje veux saving de %d a %d \n",i.id,j.id);

  printf("\tet pour de vrai de %d a %d \n",getiFroma(i.clients_order.back()),getiFroma(j.clients_order.front()));

  int before_value = i.length + j.length;
  printf("\tAvant le cout etait: %d\n",before_value);
  printf("\tle cout entre deux tours vaut : %d\n", data.getDistance(getiFroma(i.clients_order.back()),getiFroma(j.clients_order.front())));
  int after_value = i.length + j.length + data.getDistance(getiFroma(i.clients_order.back()),getiFroma(j.clients_order.front()));
  
  //moins distance entre dernier et depot et premier et depot
  after_value -= data.getDistance(getiFroma(i.clients_order.back()),0);
  after_value -= data.getDistance(0,getiFroma(i.clients_order.front()));
  gain = after_value - before_value;

  //printf("Apres le cout etait: %d\n",after_value);

  return gain;
}

/* This method runs the Clarke & Wright procedure to build an approximative solution */ 

void clarkeWrightCVRP::clarkeWrightProcedure(const CVRPData& data){
    
    struct list_tour L;

    printf("demande de %d : %d\n",0,data.getDemand(0));
    printf("demande de %d : %d\n",1,data.getDemand(1));
    printf("demande de %d : %d\n",5,data.getDemand(5));

    L.size = 0; // tour_list is empty by default
    L.name = new char[strlen("Liste resultat")];
    strcpy(L.name,"Liste resultat");
    for(int i=1; i < data.getSize(); i++){
    	// create a tour made of single visit
    	struct tour tmp_tour;
    	tmp_tour.id = i;
    	tmp_tour.clients_order.push_back(i + '0');
    	tmp_tour.size = 1;
      tmp_tour.length = data.getDistance(i,0) + data.getDistance(0,i);
    	tmp_tour.used_capacity = data.getDemand(i);
    	L.tour_list.push_back(tmp_tour);
    	L.size++;
    }


    printf("sommet : %c\n",L.tour_list.front().clients_order.front());
    list<tour>::iterator it = L.tour_list.begin();
    for(unsigned int i=0 ; i<L.tour_list.size();i++){
      printf("tour %d de cap %d e id %d\n",i,(*it).used_capacity,(*it).id);
      advance(it,1);
    }

    //tmp_i.clients_order.splice(tmp_i.clients_order.end(),tmp_j.clients_order);
/*
    printf("taiile avant splice %ld\n",L.tour_list.front().clients_order.size() );
    L.tour_list.front().clients_order.splice(L.tour_list.front().clients_order.end(),L.tour_list.back().clients_order);
    printf("taiile apres %ld\n",L.tour_list.front().clients_order.size() );
    L.tour_list.front().size++;

        list<tour>::iterator iterase2 = L.tour_list.begin();
        advance(iterase2,5);
        L.tour_list.erase(iterase2);

    displayTour(L);

*/
    printf("La taille de L est: %d\n",L.size);
    printf("Jusque la cest bon !!!\n");
    int gain = -1;
    printf("gain init :%d\n", gain);
    int tmpPos;

    //while(thereAreConcatableLists(data,L)){
    
      gain = -1;


      list<struct tour>::iterator it_Li_keeped;
      list<struct tour>::iterator it_Lj_keeped;

      list<struct tour>::iterator it_Li = L.tour_list.begin();
      list<struct tour>::iterator it_Lj = L.tour_list.begin();
      advance(it_Lj,1);

      for(int i = 0 ; i < (L.size -1) ; i++){

       for(int j = 1; j < L.size; j++){

        printf("coucou je regarde les tours %d %d",(*it_Li).id,(*it_Lj).id);

        int tmp_gain = savingPerConcatetion(data,(*it_Li),(*it_Lj));
        printf("tmp_gain : %d, gain : %d\n",tmp_gain,gain);

        int concat = areConcatable(data,L,(*it_Li),(*it_Lj));
        printf("concat ? %d\n",concat);

         if ( ((*it_Li).id != (*it_Lj).id)
              && (areConcatable(data,L,(*it_Li),(*it_Lj)))
              && ( tmp_gain > gain )) {

	         it_Lj_keeped = it_Lj;
           it_Li_keeped = it_Lj;
           tmpPos = j;
	         printf("gain trouve a : %d\n",tmp_gain);
           gain = tmp_gain;
          }

         advance(it_Lj,1);

        }
        printf("je change de tour \n");
        it_Lj = L.tour_list.begin();
        advance(it_Li,1);
      }
    // concate the two best tours
    //advance(it_i,tour_i.clients_order.end());
          displayTour(L);

    if(gain >= 0){

        printf("FUSIOOONNN %d %d\n",(*it_Li_keeped).id,(*it_Li_keeped).id);
        printf("taille avant %d compose de %c\n",(*it_Li_keeped).clients_order.size(),(*it_Lj_keeped).clients_order.front());
        cout << "il avait "<< (*it_Li_keeped).clients_order.front() << endl;
      	(*it_Li_keeped).clients_order.splice((*it_Li_keeped).clients_order.end(),(*it_Lj_keeped).clients_order);
        (*it_Li_keeped).used_capacity += (*it_Li_keeped).used_capacity;
        (*it_Li_keeped).size++;//updating size of first list
        (*it_Li_keeped).length += gain;

         printf("taille apres %d\n",(*it_Li_keeped).clients_order.size());

        list<tour>::iterator iterase = L.tour_list.begin();
        advance(iterase,tmpPos);
        L.tour_list.erase(iterase);

      	L.size--; //updating size of the set 
      	printf("fusion de 2:%d\n", L.size);
      }
    //}
    printf("Le nb final de tournees vaut: %d\n", L.size);
  //cout << res << endl;
        displayTour(L);

}

int clarkeWrightCVRP::getiFroma(char c){
    return c - '0';
}

void clarkeWrightCVRP::displayTour(struct list_tour L){

  list<struct tour>::iterator it = L.tour_list.begin();
  printf("j'ai %d tournées\n",L.size);

  for (unsigned int i = 0; i < L.tour_list.size(); ++i)
  {
    printf("Tournée %d de taille %d\n",i,(*it).size);
    list<char>::iterator it2 = (*it).clients_order.begin();
    for (int j = 0; j < (*it).size; ++j){
      printf("\tclient %c\n",(*it2));
      advance(it2,1);
    }
    advance(it,1);
  }

}

/* This method return if there are at least two tours which can be concated */ 

bool clarkeWrightCVRP::thereAreConcatableLists(const CVRPData& data,struct list_tour L){  
  if ( (L.size != 0) && (L.size != 1)){
    list<struct tour>::iterator it_i = L.tour_list.begin();
    list<struct tour>::iterator it_j = L.tour_list.begin();

    advance(it_j,1);
    for(int i = 0 ; i < L.size; i++){
      for(int j = 1; j < L.size - 1; j++){

      	if ( ((*it_j).used_capacity + (*it_j).used_capacity) < data.getCapacity()){
      	  //printf("total ? %d et cap %d \n", (*it_j).used_capacity + (*it_j).used_capacity,data.getCapacity()); 

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
  list<struct tour>::iterator it_i = L.tour_list.begin();
  list<struct tour>::iterator it_j = L.tour_list.begin();

  if ( ((*it_j).used_capacity + (*it_j).used_capacity) <= data.getCapacity())
    return true;

  printf("\t\tdesolee coco :(\n");
  return false;
}
