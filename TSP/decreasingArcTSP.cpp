#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>

#include "decreasingArcTSP.hpp"



DecreasingArc::DecreasingArc(){

}


DecreasingArc::DecreasingArc(const TSPData &data){

	long ** matrix = data.getMatrix();
	nodesNumber = data.getSize();

	start = -1;
	totalLength = 0;
	nextNode = new int[nodesNumber];

	for (int i = 0; i < nodesNumber; ++i) {

		nextNode[i]=-1;
		for (int j = 0; j < nodesNumber; ++j) {
			if(i!=j) {
				Arc a(i,j,matrix[i][j]);
				remainingArcs.push_back(a);
			}
		}
	}

	std::sort(remainingArcs.begin(), remainingArcs.end());

}

DecreasingArc::~DecreasingArc(){
	remainingArcs.clear();
	selectedArcs.clear();
	delete []nextNode;
}

int DecreasingArc::isSuitable(const Arc& a){

	int i=0;
	int isPossible = 1;

	int currentPathSize = 0;

	if(nextNode[a.getSource()]!=-1)
		isPossible=0;

	if(isPossible){
		for(i=0;i<nodesNumber;i++){

			if(nextNode[i]==a.getTarget()){
				isPossible=0;
			}
			if(nextNode[i]!=-1){
				currentPathSize++;
			}
		}
	}

	//lorsque taille path < nodesNumber, verifier les sous-circuits
	if(currentPathSize<(nodesNumber-1) && isPossible){

		int start = a.getSource();
		int next = a.getTarget();

		while(nextNode[next]!=-1 && isPossible){
			if(nextNode[next]==start)
				isPossible=0;
			else
				next = nextNode[next];
		}
	}



	if(isPossible){
		return 1;
	}
	else{
		return 0;
	}
}


Arc* DecreasingArc::retrieveNext(){

	int found = 0;
	int i =0;
	Arc* a;

	while(!found){
		usleep(10000);

		if(isSuitable(remainingArcs[i])){
			a = new Arc(remainingArcs[i]);
			remainingArcs.erase(remainingArcs.begin()+i);
			found = 1;
		}
		else{
			a = NULL;
			remainingArcs.erase(remainingArcs.begin()+i);
			if(!remainingArcs.size())
				found=1;
		}
	}
	

	return a;
}


void DecreasingArc::addSelectedArc(const Arc& a){

	if(start==-1){
		start = a.getSource();
	}
	selectedArcs.push_back(a);
	nextNode[a.getSource()]=a.getTarget();
}


int DecreasingArc::isEmpty() const{
	return !remainingArcs.size();
}

int DecreasingArc::getPathSize() const{
	return selectedArcs.size();
}

Arc DecreasingArc::getArcFromPath(int i) const{
	return selectedArcs[i];
}

int DecreasingArc::getNodesNumber() const{
	return nodesNumber;
}

int DecreasingArc::getTotalLength() const{
	return totalLength;
}

void DecreasingArc::constructPath(const TSPData &data){

	int i =0;
	int next = start;

	selectedArcs.clear();

	while(i<nodesNumber){
		int val = data.getVal(next,nextNode[next]);
		Arc a(next,nextNode[next],val);
		totalLength+=val;
		selectedArcs.push_back(a);
		next = nextNode[next];
		i++;
	}
}

ostream& operator<<(ostream& os,const DecreasingArc& da )
{
	int i;
	int nodes = da.getNodesNumber();

	for(i=0; i < nodes; i++) {
		os << da.getArcFromPath(i).getSource() << "," << da.getArcFromPath(i).getTarget() << " ; ";
	}
	os << " taille total : "<< da.getTotalLength() << endl;

    return os;
}