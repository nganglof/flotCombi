#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "CVRP.hpp"
#include "giantTourCVRP.hpp"
#include "clarkeWrightCVRP.hpp"

using namespace std;

void run_clarkeWright(const CVRPData &data){

}

void run_giantTour(const CVRPData &data){

}

void usage (char* s){
	cout << "Usage: " << s << " <int> <data>" << endl;
	exit(EXIT_FAILURE);
}

#define PARAM 2
int main(int argc, char * argv[]) {


	if (argc != PARAM+1) usage(argv[0]);

	CVRPData cvrp(argv[1]);
    std::cout << cvrp << std::endl;

	switch(atoi(argv[1])){

		case 1 :
			//algo 1 : clarkeWright
			run_clarkeWright(cvrp);
		break;

		case 2 :
			//algo 2 : giantTour
			run_giantTour(cvrp);
		break;

		case 4 :
			//comparaison des trois algo
		break;
	}

	return 0;
}
