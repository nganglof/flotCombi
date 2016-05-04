#ifndef _DECREASING_ARC_TSP_HPP_
#define _DECREASING_ARC_TSP_HPP_

#include <vector>
#include "TSP.h"
#include "arc.hpp"

using namespace std;

class DecreasingArc{

	private :
		//std::vector<Arc*> arcs;
		std::vector<Arc> arcs;
		std::vector<Arc> path;

	public :
		DecreasingArc();
		DecreasingArc(const TSPData& data);
		~DecreasingArc();
		Arc retrieveNext();
		int isSuitable(const Arc& a);
		int isEmpty()const;
		void addArcPath(const Arc& a);
		int getPathSize()const;
		
		Arc getArcFromArcs(int i) const;

		friend ostream& operator<<(ostream& os ,const DecreasingArc& da );
};

#endif
