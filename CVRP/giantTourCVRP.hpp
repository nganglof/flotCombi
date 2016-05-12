#ifndef _GIANT_TOUR_TSP_HPP_
#define _GIANT_TOUR_TSP_HPP_

#include <vector>
#include "CVRP.hpp"
#include "arcCVRP.hpp"

using namespace std;

struct Tour{
	std::vector<int> clients;
	int totalLength;
};

class GiantTour{

	private :
		int* TSPpath;

		unsigned int capacity;
		unsigned int nodes;
		std::vector<ArcCVRP> arcs;
		std::vector<ArcCVRP> shortestPath;
		int* permuNodes;
		int totalLength;

		std::vector<Tour> tours;

	public :
		GiantTour();
		GiantTour(const CVRPData &data, char* path);
		~GiantTour();

		void rearrangePath();

		int getPosFromRealNode(int node);
		int getRealNodeFromPos(int pos);
		int isCapSufficient(const CVRPData &data, int posi, int posj);
		int isArcPresent(int posi, int posj);
		int isPossible(const CVRPData & data, int posi, int posj);
		void addShortcuts(const CVRPData &data);

		int newArcCost(const CVRPData& data, int posi, int posj);

		int getNearestNode(int dist[], unsigned int size, int treated[]);
		int getMinDist(int d1, int d2);
		void getShortestPath(const CVRPData &data);
		void displayArcs(const CVRPData& data);
		void displayTours();

		void getTours(const CVRPData &data);

		//friend ostream& operator<<(ostream& os ,const GiantTour& gt );
};

#endif
