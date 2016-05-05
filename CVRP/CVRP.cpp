#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include"CVRP.hpp"


CVRPData::CVRPData(const char* filename){
  std::ifstream infile;
  int tmp;
  infile.open(filename,std::ios::in);
  NbNodes = 0;

  /* Reading of the data in file filename */
  char* ligne = new char[256];
  do {
    infile >> ligne >> std::ws;
  } while ((strcmp(ligne,"TYPE:") != 0) && (!infile.eof()));

  if (infile.eof()){
    std::cout << "Bad file (type not specified) !!!" << std::endl;
    abort();
  }

  infile >> ligne >> std::ws;

  if (strcmp(ligne,"CVRP") == 0){
    do {
      infile >> ligne >> std::ws;
    } while ((strcmp(ligne,"DIMENSION:") != 0) && (!infile.eof()));

    if (infile.eof()){
      std::cout << "Bad File (dimension not specified) !!!" << std::endl;
      abort();
    }

    infile >> NbNodes >> std::ws;

    Distances = new int*[NbNodes];
    for (int i = 0; i < NbNodes; i++){
      Distances[i] = new int[NbNodes];
    }

    Demands = new int[NbNodes];

    do {
      infile >> ligne >> std::ws;
    } while ((strcmp(ligne,"EDGE_WEIGHT_TYPE:") != 0) && (!infile.eof()));

    infile >> ligne >> std::ws;

    if (strcmp(ligne,"EXPLICIT") == 0){

      do {
	infile >> ligne >> std::ws;
      } while ((strcmp(ligne,"EDGE_WEIGHT_FORMAT:") != 0) && (!infile.eof()));

      infile >> ligne >> std::ws;

      if (strcmp(ligne,"FULL_MATRIX") == 0){
	do {
	  infile >> ligne >> std::ws;
	} while ((strcmp(ligne,"CAPACITY:") != 0) && (!infile.eof()));

	infile >> Capacity >> std::ws;

	do {
	  infile >> ligne >> std::ws;
	} while ((strcmp(ligne,"EDGE_WEIGHT_SECTION") != 0) && (!infile.eof()));

	if (infile.eof()){
	  std::cout << "Bad File (no arc specified) !!!" << std::endl;
	  abort();
	}

	infile >> std::ws;
	for (int i = 0; i < NbNodes; i++){
	  for (int j = 0; j < NbNodes; j++){
	    infile >> Distances[i][j] >> std::ws;
	  }
	  Distances[i][i] = std::numeric_limits<int>::max();
	}

	do {
	  infile >> ligne >> std::ws;
	} while ((strcmp(ligne,"DEMAND_SECTION") != 0) && (!infile.eof()));

	for (int i = 0; i < NbNodes; i++){
	  infile >> tmp >> Demands[i] >> std::ws;
	}


      } else {
	if (strcmp(ligne,"UPPER_ROW") == 0) {

	  do {
	    infile >> ligne >> std::ws;
	  } while ((strcmp(ligne,"CAPACITY:") != 0) && (!infile.eof()));

	  infile >> Capacity >> std::ws;

	  do {
	    infile >> ligne >> std::ws;
	  } while ((strcmp(ligne,"EDGE_WEIGHT_SECTION") != 0) && (!infile.eof()));

	  if (infile.eof()){
	    std::cout << "Bad File (no arc specified) !!!" << std::endl;
	    abort();
	  }

	  infile >> std::ws;
	  for (int i = 0; i < NbNodes-1; i++){
	    for (int j = i+1; j < NbNodes; j++){
	      infile >> Distances[i][j] >> std::ws;
	      Distances[j][i] = Distances[i][j];
	    }
	    Distances[i][i] = std::numeric_limits<int>::max();
	  }
	  Distances[NbNodes-1][NbNodes-1] = std::numeric_limits<int>::max();

	  do {
	    infile >> ligne >> std::ws;
	  } while ((strcmp(ligne,"DEMAND_SECTION") != 0) && (!infile.eof()));

	  for (int i = 0; i < NbNodes; i++){
	    infile >> tmp >> Demands[i] >> std::ws;
	  }

	} else {
	  if (strcmp(ligne,"LOWER_DIAG_ROW") == 0){
	    do {
	      infile >> ligne >> std::ws;
	    } while ((strcmp(ligne,"CAPACITY:") != 0) && (!infile.eof()));

	    infile >> Capacity >> std::ws;

	    do {
	      infile >> ligne >> std::ws;
	    } while ((strcmp(ligne,"EDGE_WEIGHT_SECTION") != 0) && (!infile.eof()));

	    if (infile.eof()){
	      std::cout << "Bad File (no arc specified) !!!" << std::endl;
	      abort();
	    }

	    infile >> std::ws;
	    for (int i = 0; i < NbNodes; i++){
	      for (int j = 0; j <= i; j++){
		infile >> Distances[i][j] >> std::ws;
		Distances[j][i] = Distances[i][j];
	      }
	      Distances[i][i] = std::numeric_limits<int>::max();
	    }

	    do {
	      infile >> ligne >> std::ws;
	    } while ((strcmp(ligne,"DEMAND_SECTION") != 0) && (!infile.eof()));

	    for (int i = 0; i < NbNodes; i++){
	      infile >> tmp >> Demands[i] >> std::ws;
	    }

	  } else {
	    if (strcmp(ligne,"LOWER_ROW") == 0){
	      do {
		infile >> ligne >> std::ws;
	      } while ((strcmp(ligne,"CAPACITY:") != 0) && (!infile.eof()));

	      infile >> Capacity >> std::ws;

	      do {
		infile >> ligne >> std::ws;
	      } while ((strcmp(ligne,"EDGE_WEIGHT_SECTION") != 0) && (!infile.eof()));

	      if (infile.eof()){
		std::cout << "Bad File (no arc specified) !!!" << std::endl;
		abort();
	      }

	      infile >> std::ws;
	      for (int i = 0; i < NbNodes; i++){
		for (int j = 0; j < i; j++){
		  infile >> Distances[i][j] >> std::ws;
		  Distances[j][i] = Distances[i][j];
		}
		Distances[i][i] = std::numeric_limits<int>::max();
	      }

	      do {
		infile >> ligne >> std::ws;
	      } while ((strcmp(ligne,"DEMAND_SECTION") != 0) && (!infile.eof()));

	      for (int i = 0; i < NbNodes; i++){
		infile >> tmp >> Demands[i] >> std::ws;
	      }

	    } else {
	      std::cout << "Edge weight format not supported" << std::endl;
	      abort();
	    }
	  }
	}
      }

    } else {
      if (strcmp(ligne,"EUC_2D") == 0){
	do {
	  infile >> ligne >> std::ws;
	} while ((strcmp(ligne,"CAPACITY:") != 0) && (!infile.eof()));

	infile >> Capacity >> std::ws;

	do {
	  infile >> ligne >> std::ws;
	} while ((strcmp(ligne,"NODE_COORD_SECTION") != 0) && (!infile.eof()));

	if (infile.eof()){
	  std::cout << "Bad File (no node specified) !!!" << std::endl;
	  abort();
	}

	std::vector<float> coordx(NbNodes);
	std::vector<float> coordy(NbNodes);
	int temp;

	infile >> std::ws;
	for (int i = 0; i < NbNodes; i++){
	  infile >> temp >> coordx[i] >> coordy[i] >> std::ws;
	}

	for (int i = 0; i < NbNodes-1; i++){
	  for (int j = i+1; j < NbNodes; j++){
	    float xd = coordx[i] - coordx[j];
	    float yd = coordy[i] - coordy[j];
	    Distances[i][j] = floor(sqrt(xd*xd + yd*yd) + 0.5);
	    Distances[j][i] = Distances[i][j];
	  }
	  Distances[i][i] = std::numeric_limits<int>::max();
	}
	Distances[NbNodes-1][NbNodes-1] = std::numeric_limits<int>::max();

	do {
	  infile >> ligne >> std::ws;
	} while ((strcmp(ligne,"DEMAND_SECTION") != 0) && (!infile.eof()));

	for (int i = 0; i < NbNodes; i++){
	  infile >> tmp >> Demands[i] >> std::ws;
	}

      } else {
	if (strcmp(ligne,"GEO") == 0){

	  double PI=3.141592;
	  double RRR=6378.388;

	  do {
	    infile >> ligne >> std::ws;
	  } while ((strcmp(ligne,"CAPACITY:") != 0) && (!infile.eof()));

	  infile >> Capacity >> std::ws;

	  do {
	    infile >> ligne >> std::ws;
	  } while ((strcmp(ligne,"NODE_COORD_SECTION") != 0) && (!infile.eof()));

	  if (infile.eof()){
	    std::cout << "Bad File (no node specified) !!!" << std::endl;
	    abort();
	  }

	  std::vector<float> latitude(NbNodes);
	  std::vector<float> longitude(NbNodes);
	  int temp,deg;
	  float xi,yi,min;

	  infile >> std::ws;
	  for (int i = 0; i < NbNodes; i++){
	    infile >> temp >> xi >> yi >> std::ws;
	    deg = floor(xi + 0.5);
	    min = xi - deg;
	    latitude[i] = PI * (deg + 5.0 * min / 3.0) / 180.0;
	    deg = floor(yi + 0.5);
	    min = yi - deg;
	    longitude[i] = PI * (deg + 5.0 * min / 3.0) / 180.0;
	  }

	  for (int i = 0; i < NbNodes; i++){
	    for (int j = 0; j < NbNodes; j++){
	      if (i != j){
		float q1 = cos(longitude[i] - longitude[j]);
		float q2 = cos(latitude[i] - latitude[j]);
		float q3 = cos(latitude[i] + latitude[j]);
		Distances[i][j] = floor (RRR * acos(0.5 * (( 1.0 + q1) * q2 - (1.0 - q1)*q3)) + 1.0);
	      }
	    }
	    Distances[i][i] = std::numeric_limits<int>::max();
	  }

	  do {
	    infile >> ligne >> std::ws;
	  } while ((strcmp(ligne,"DEMAND_SECTION") != 0) && (!infile.eof()));
	  
	  for (int i = 0; i < NbNodes; i++){
	    infile >> tmp >> Demands[i] >> std::ws;
	  }


	} else {
	  std::cout << "Edge weight type not supported" << std::endl;
	  abort();
	}
      }

    }
  } else {
    std::cout << "Problem not supported" << std::endl;
  }

  infile.close();
}

CVRPData::~CVRPData(){
  for (int i = 0; i < NbNodes; i++){
    delete[] Distances[i];
  }
  delete[] Distances;
  delete[] Demands;
}

int CVRPData::getCapacity() const {
  return Capacity;
}

int CVRPData::getSize() const {
  return NbNodes;
}

int** CVRPData::getDistances() const {
  return Distances;
}

int CVRPData::getDistance(const int & i, const int & j) const {
  return Distances[i][j];
}

int* CVRPData::getDemands() const {
  return Demands;
}

int CVRPData::getDemand(const int & i) const {
  return Demands[i];
}

std::ostream & operator<<(std::ostream & os, const CVRPData & cvrp){
  os << "Size = " << cvrp.getSize() << std::endl;
  os << "Capacity = " << cvrp.getCapacity() << std::endl;
  os << "Distances :" << std::endl;
  for (int i = 0; i < cvrp.getSize(); i++){
    for (int j = 0; j < cvrp.getSize(); j++){
      os << cvrp.getDistance(i,j) << " - ";
    }
    os << std::endl;
  }
  os << "Demands :" << std::endl;
  for (int i = 0; i < cvrp.getSize(); i++){
    os << cvrp.getDemand(i) << " - ";
  }

  return os;
}
