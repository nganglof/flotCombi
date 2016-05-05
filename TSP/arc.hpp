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
		Arc(const Arc&);
		~Arc();

		int getSource() const;
		int getTarget() const;
		float getDistance() const;

		bool operator<(const Arc& a) const;
};

#endif
