#ifndef _INTERFACE_TSP_HPP_
#define _INTERFACE_TSP_HPP_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "TSP.h"
#include "decreasingArcTSP.hpp"
#include "closestInsertionTSP.hpp"
#include "furthestInsertionTSP.hpp"

using namespace std;

class InterfaceTSP{

	private :

	public :
		static void run_decreasingArc(const TSPData &data);
		static void run_closestInsertion(const TSPData &data);
		static void run_furthestInsertion(const TSPData &data);

};

#endif
