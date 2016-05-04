#ifndef _DECREASING_ARC_TSP_HPP_
#define _DECREASING_ARC_TSP_HPP_

#include <vector>
#include "TSP.h"
#include "arc.hpp"

using namespace std;

class DecreasingArc{

	private :
		std::vector<Arc> arcs;

	public :
		DecreasingArc();
		DecreasingArc(TSPData data);
		~DecreasingArc();

};

#endif
