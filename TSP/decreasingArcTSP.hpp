#ifndef _DECREASING_ARC_TSP_HPP_
#define _DECREASING_ARC_TSP_HPP_

#include <vector>
#include "TSP.h"
#include "arc.hpp"

using namespace std;

class DecreasingArc{

	private :
		std::vector<Arc> remainingArcs;
		std::vector<Arc> selectedArcs;
		std::vector<Arc> path;
			
		int nodesNumber;
		int totalLength;

		int* nextNode;
		int start;


	public :
		DecreasingArc();
		DecreasingArc(const TSPData& data);
		~DecreasingArc();
		Arc* retrieveNext();
		int isSuitable(const Arc& a);
		int isEmpty()const;
		void addSelectedArc(const Arc& a);

		int getPathSize()const;

		int getNodesNumber() const;
		int getTotalLength() const;
		Arc getArcFromPath(int i) const;
		void constructPath(const TSPData& data);

		friend ostream& operator<<(ostream& os ,const DecreasingArc& da );
};

#endif
