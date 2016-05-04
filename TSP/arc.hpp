#ifndef _ARC_HPP_
#define _ARC_HPP_

using namespace std;

class Arc{

	private :
		int source;
		int target;


	public :
		Arc();
		Arc(int s, int t);
		~Arc();
};

#endif
