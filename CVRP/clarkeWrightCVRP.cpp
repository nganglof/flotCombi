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

clarkeWrightCVRP::clarkeWrightCVRP(const CVRPData& data){}
clarkeWrightCVRP::~clarkeWrightCVRP(){}

void clarkeWrightCVRP::clarkeWrightProcedure(const CVRPData& data){
  struct list_tour L;


    L.size = 0; // tour_list initialisee a vide par defaut
    L.name = new char[strlen("Liste resultat")];
    strcpy(L.name,"Liste resultat");
    for(int i=0; i < data.getSize(); i++){
      for(int j= 0; j < data.getSize(); j++){
	// on cree une tournee a un sommet
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
	if ( (i != j) && (savingPerConcatetion(data,advance(it_i,i),advance(it_j,j)) > gain))  {
	  tour_j.id = j; //on stocke les tournees concatenables
	  tour_i.id = i;
	  gain = savingPerConcatetion(advance(it_L,i),advance(it_L,j));                                      
	}
      }
    }
    //concaténer i et j trouves comme optimales a fusionner;
    //L.list_tour[tour_i].splice(list_tour[tour_i].end(),list_tour[tour_j].begin()); 
    tour_i.length++;
    L.size--;
    
  }

  //cout << res << endl;
}

int clarkeWrightCVRP::savingPerConcatetion(const CVRPData& data,struct tour i, struct tour j){
  int gain = 0;
  list<char>::iterator it_i = i.clients_order.begin();
  list<char>::iterator it_j = j.clients_order.begin();
  int before_value = i.length + j.length + data.getDistance(*i.clients_order.end(),*j.clients_order.begin());
  int after_value = i.length + j.length + data.getDistance(*i.clients_order.end(),*j.clients_order.begin());
  gain = before_value - after_value;

  return gain;
}


bool clarkeWrightCVRP::thereAreConcatableLists(const CVRPData& data,struct list_tour L){  
  if ( (L.size != 0) )
    return true;
  else
    return false;
}
