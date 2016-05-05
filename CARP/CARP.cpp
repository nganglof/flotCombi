#include <fstream>
#include <limits>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <utility>
#include <list>
#include <vector>
#include"CARP.hpp"


  /*******************/
 /* Methods of Edge */
/*******************/

Edge::Edge(const int & ext1, const int & ext2, const int & co, const int & de):
  pair(ext1,ext2),Cost(co),Demand(de){}

Edge::~Edge(){}

int Edge::getCost() const{
  return Cost;
}

int Edge::getDemand() const {
  return Demand;
}

int Edge::getFirst() const {
  return this->first;
}

int Edge::getSecond() const {
  return this->second;
}

std::ostream & operator<<(std::ostream & os, const Edge & ed){
  os << "Edge " << ed.getFirst() << "--" << ed.getSecond()
     << " : Cost = " << ed.getCost() << " \t Demand = " << ed.getDemand();
}




  /***********************/
 /* Methods of CARDdata */
/***********************/

CARPData::CARPData(const char* filename){
  std::ifstream infile;
  infile.open(filename,std::ios::in);
  NbNodes = 0;

  char* ligne = new char[256];
  do {
    infile >> ligne >> std::ws;
  } while ((strcmp(ligne,"VERTICES") != 0) && (!infile.eof()));

  if (infile.eof()){
    std::cout << "Bad file (type not specified) !!!" << std::endl;
    abort();
  }

  infile >> ligne >> std::ws;
  infile >> NbNodes >> std::ws;

  Graph = std::vector<std::list<Edge> >(NbNodes);

  do {
    infile >> ligne >> std::ws;
  } while ((strcmp(ligne,"ARISTAS_REQ") != 0) && (!infile.eof()));

  if (infile.eof()){
    std::cout << "Bad file (type not specified) !!!" << std::endl;
    abort();
  }

  int NbEdges;
  infile >> ligne >> std::ws;
  infile >> NbEdges >> std::ws;

  do {
    infile >> ligne >> std::ws;
  } while ((strcmp(ligne,"VEHICULOS") != 0) && (!infile.eof()));

  if (infile.eof()){
    std::cout << "Bad file (type not specified) !!!" << std::endl;
    abort();
  }

  infile >> ligne >> std::ws;
  infile >> NbVehicles >> std::ws;

  do {
    infile >> ligne >> std::ws;
  } while ((strcmp(ligne,"CAPACIDAD") != 0) && (!infile.eof()));

  if (infile.eof()){
    std::cout << "Bad file (type not specified) !!!" << std::endl;
    abort();
  }

  infile >> ligne >> std::ws;
  infile >> VehCapacity >> std::ws;

  do {
    infile >> ligne >> std::ws;
  } while ((strcmp(ligne,"LISTA_ARISTAS_REQ") != 0) && (!infile.eof()));

  if (infile.eof()){
    std::cout << "Bad file (type not specified) !!!" << std::endl;
    abort();
  }

  infile >> ligne >> std::ws;

  std::string tmp;
  int ext1, ext2, cost, demand;

  for (int i = 0; i < NbEdges; i++){
    infile >> tmp >> ext1 >> tmp >> ext2 >> tmp >> tmp >> cost >> tmp >> demand >> std::ws;
    ext1--;
    ext2--;
    Graph[ext1].push_back(Edge(ext1,ext2,cost,demand));
    Graph[ext2].push_back(Edge(ext2,ext1,cost,demand));
  }
}

CARPData::~CARPData(){}

int CARPData::getVehicleCapacity() const {
  return VehCapacity;
}

int CARPData::getSize() const {
  return NbNodes;
}

int CARPData::getNbVeh() const {
  return NbVehicles;
}

std::vector<std::list<Edge> > & CARPData::getVectorNodes() {
  return Graph;
}

std::list<Edge> & CARPData::getEdgesListOfNode(const int & i) {
  return Graph[i];
}

std::ostream & operator<<(std::ostream & os, CARPData & carp){
  os << "Size = " << carp.getSize() << std::endl;
  os << "Number of vehicles = " << carp.getNbVeh() << std::endl;
  os << "Vehicle capacity = " << carp.getVehicleCapacity() << std::endl;
  os << std::endl;
  os << "Graph :" << std::endl;
  for (int i = 0; i < carp.getSize(); i++){
    os << "Edges incident to node " << i << " :" << std::endl;
    for (std::list<Edge>::iterator it = carp.getEdgesListOfNode(i).begin();
    it != carp.getEdgesListOfNode(i).end(); it++){
      os << *it << std::endl;
    }
    os << std::endl;
  }

  return os;
}


