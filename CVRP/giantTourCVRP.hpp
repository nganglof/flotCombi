#ifndef _GIANT_TOUR_TSP_HPP_
#define _GIANT_TOUR_TSP_HPP_

#include <vector>
#include "CVRP.hpp"
#include "arcCVRP.hpp"

using namespace std;

class GiantTour{

	private :
		int* TSPpath;

		unsigned int nodes;
		std::vector<ArcCVRP> arcs;

		//CVRPData data;

	public :
		GiantTour();
		GiantTour(const CVRPData &data, char* path);
		~GiantTour();

		void getShortestPath(const CVRPData &data);

		//friend ostream& operator<<(ostream& os ,const GiantTour& gt );
};

#endif
