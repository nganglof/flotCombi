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

	//si il y a deja un arc qui part de ce sommet
	if(nextNode[a.getSource()]!=-1)
		isPossible=0;

	if(isPossible){
		for(i=0;i<nodesNumber;i++){

			//si il y a deja un arc qui arrive dans ce sommet
			if(nextNode[i]==a.getTarget()){
				isPossible=0;
			}
			//sinon on augmente la taille du sous-circuit actuelle
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

	return isPossible;
}


Arc* DecreasingArc::retrieveNext(){

	int found = 0;
	int i =0;
	Arc* a;

	while(!found){

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


void DecreasingArc::addSelectedArc(const TSPData &data, const Arc& a){

	if(start==-1){
		start = a.getSource();
	}
	selectedArcs.push_back(a);

	int val = data.getVal(a.getSource(),a.getTarget());
	totalLength+=val;

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

char* DecreasingArc::getPathString() const{

	char* path;

	int i;
	int nodes = getNodesNumber();
	asprintf(&path,"%d",start);
	for(i=0; i < nodes; i++) {
		asprintf(&path,"%s,%d",path,getArcFromPath(i).getTarget());
	}
	return path;
}

ostream& operator<<(ostream& os,const DecreasingArc& da )
{
  	os << "DecreasingArc" << endl;
  	os << "\tNodes number : " << da.getNodesNumber() << endl;
  	os << "\tPath : " << da.getPathString() << endl;
  	os << "\tTotal distance : " << da.getTotalLength() << endl;
    return os;
}