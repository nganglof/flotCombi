#include <iostream>
#include <vector>
#include <algorithm>


#include "decreasingArcTSP.hpp"



DecreasingArc::DecreasingArc(){

}


DecreasingArc::DecreasingArc(const TSPData &data){

	long ** matrix = data.getMatrix();
	int size = data.getSize();

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			//Arc* a = new Arc(i,j,matrix[i][j]);
			//cout << "arc : " << a->getSource() << "," << a->getTarget() << " dist : " << a->getDistance() << endl;
			if(i!=j) {
				Arc a(i,j,matrix[i][j]);
				arcs.push_back(a);
			}
		}
	}


	std::sort(arcs.begin(), arcs.end());


	for (unsigned i=0; i < arcs.size(); i++) {
    	cout << "arc : " << arcs[i].getSource() << "," << arcs[i].getTarget() << " dist : " << arcs[i].getDistance() << endl;
	}
}

DecreasingArc::~DecreasingArc(){
	vector<Arc >::iterator it;
	for(it=arcs.begin() ; it < arcs.end(); it++ ) {
	    //delete *it;
	}
	arcs.clear();
}



int DecreasingArc::isSuitable(const Arc& a){

	return 1;
}


Arc DecreasingArc::retrieveNext(){

	int found = 0;
	int i =0;

	while(!found){
		if(isSuitable(arcs[i])){
			found = 1;
		}
		else 
			i++;
	}
	Arc a = arcs[i];
	arcs.erase(arcs.begin()+i);
	return a;
}


void DecreasingArc::addArcPath(const Arc& a){
	path.push_back(a);
}

int DecreasingArc::isEmpty() const{
	return !arcs.size();
}

int DecreasingArc::getPathSize() const{
	return path.size();
}

Arc DecreasingArc::getArcFromArcs(int i) const{
	return path[i];
}

ostream& operator<<(ostream& os,const DecreasingArc& da )
{
	int i;
	for(i=0; i < da.getPathSize(); i++) {
		os << da.getArcFromArcs(i).getSource() << " , ";
	}
	os << da.getArcFromArcs(i).getTarget();

    return os;
}