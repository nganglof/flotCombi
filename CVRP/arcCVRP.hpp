#ifndef _ARC_CVRP_HPP_
#define _ARC_CVRP_HPP_

using namespace std;

class ArcCVRP{

	private :
		int source;
		int target;
		float distance;

	public :
		ArcCVRP();
		ArcCVRP(int s, int t, float d);
		ArcCVRP(const ArcCVRP&);
		~ArcCVRP();

		int getSource() const;
		int getTarget() const;
		float getDistance() const;

		bool operator<(const ArcCVRP& a) const;
};

#endif
