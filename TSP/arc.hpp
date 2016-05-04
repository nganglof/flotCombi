#ifndef _ARC_HPP_
#define _ARC_HPP_

using namespace std;

class Arc{

	private :
		int source;
		int target;
		float distance;

	public :
		Arc();
		Arc(int s, int t, float d);
		~Arc();

		int getSource();
		int getTarget();
		float getDistance();

		bool operator<(const Arc& a) const;
};

#endif
