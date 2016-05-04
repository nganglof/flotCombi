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
			if(i!=j) {
				Arc a(i,j,matrix[i][j]);
				remainingArcs.push_back(a);
			}
		}
	}

	std::sort(remainingArcs.begin(), remainingArcs.end());

	for (unsigned i=0; i < remainingArcs.size(); i++) {
    	cout << "arc : " << remainingArcs[i].getSource() << "," << remainingArcs[i].getTarget() << " dist : " << remainingArcs[i].getDistance() << endl;
	}
}

DecreasingArc::~DecreasingArc(){
	remainingArcs.clear();
	selectedArcs.clear();
}



int DecreasingArc::isSuitable(const Arc& a){

	return 1;
}


Arc DecreasingArc::retrieveNext(){

	int found = 0;
	int i =0;

	while(!found){
		if(isSuitable(remainingArcs[i])){
			found = 1;
		}
		else 
			i++;
	}
	Arc a = remainingArcs[i];
	remainingArcs.erase(remainingArcs.begin()+i);
	return a;
}


void DecreasingArc::addSelectedArc(const Arc& a){
	selectedArcs.push_back(a);
}

int DecreasingArc::isEmpty() const{
	return !remainingArcs.size();
}

int DecreasingArc::getPathSize() const{
	return path.size();
}

Arc DecreasingArc::getArcFromPath(int i) const{
	return path[i];
}

void DecreasingArc::constructPath(){

	//remettre les arcs choisis dans l'ordre
	path.push_back(selectedArcs.front());
	selectedArcs.erase(selectedArcs.begin());
	int current = path.front().getTarget();
	int i=0;
	int sizeSelected = selectedArcs.size();
	int found = 0;

	//tant qu'il reste des arcs
	while(sizeSelected){

		//on cherche l'arc consécutif
		while(!found) {

			if(selectedArcs[i].getSource() == current){

				path.push_back(selectedArcs[i]);
				current=selectedArcs[i].getTarget();
				selectedArcs.erase(selectedArcs.begin()+i);
				sizeSelected--;
				i=0;
				found = 1;
			}
			else
				i++;
		}
		found = 0;
	}
}

ostream& operator<<(ostream& os,const DecreasingArc& da )
{
	int i;
	for(i=0; i < da.getPathSize(); i++) {
		os << da.getArcFromPath(i).getSource() << "," << da.getArcFromPath(i).getTarget() << " ; ";
	}

    return os;
}