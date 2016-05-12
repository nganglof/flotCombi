#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "giantTourCVRP.hpp"
#include <limits.h>
#include "arcCVRP.hpp"

GiantTour::GiantTour(){


}

GiantTour::GiantTour(const CVRPData &data, char* path, int meth){

	if(meth==1){
		int n = strlen("ClosestInsertionTSP")+1;
		methode = new char[n];
		strcpy(methode,"ClosestInsertionTSP");
	}	
	else if(meth==2){
		int n = strlen("DecreasingArcTSP")+1;
		methode = new char[n];
		strcpy(methode,"DecreasingArcTSP");
	}
	else{
		int n = strlen("FurthestInsertion")+1;
		methode = new char[n];
		strcpy(methode,"FurthestInsertion");
	}

	totalLength=0;
	nodes = data.getSize();
	capacity = data.getCapacity();


	int cpt = 0;

	int number = (int)nodes;
	TSPpath = new int[number];
	permuNodes = new int[number];

	char* tmp =  strtok( path,",");
	TSPpath[cpt]=atoi(tmp);

	while(tmp!=NULL && (cpt < number)){
		int nd = atoi(tmp);
		TSPpath[cpt]=nd;
		cpt++;
		tmp = strtok(NULL,",");
	}
	
	//remettre le chemin a partir du depot
	if(TSPpath[0]!=0){
		rearrangePath();
	}

	for(unsigned int i=0;i<(nodes-1);i++){

		permuNodes[i]=TSPpath[i];
		int newdist = data.getDistance(0,TSPpath[i+1]) + data.getDistance(TSPpath[i+1],TSPpath[0]);

		ArcCVRP a(TSPpath[i],TSPpath[i+1],newdist);
		arcs.push_back(a);
	}
	permuNodes[nodes-1]=TSPpath[nodes-1];

	int newdist = data.getDistance(0,TSPpath[nodes-1]) + data.getDistance(TSPpath[nodes-1],TSPpath[0]);
	ArcCVRP a(TSPpath[nodes-1],0,newdist);
	arcs.push_back(a);

}

GiantTour::~GiantTour(){
	arcs.clear();
	shortestPath.clear();
	delete[] methode;
	delete[] permuNodes;
}

void GiantTour::rearrangePath(){

	int*  rearrange = new int[nodes];

	int start = 0;
	while(TSPpath[start]!=0)
		start++;

	for (unsigned int i = 0; i < nodes; ++i)
		rearrange[i]=TSPpath[(start+i)%nodes];

	for (unsigned int i = 0; i < nodes; ++i)
		TSPpath[i]=rearrange[i];

	delete[] rearrange;

}

int GiantTour::getPosFromRealNode(int node){
	for(unsigned int i=0;i<nodes;i++){
		if(permuNodes[i]==node){
			return i;
		}
	}
	return -1;
}

int GiantTour::getRealNodeFromPos(int pos){
	return permuNodes[pos];
}	

int GiantTour::isCapSufficient(const CVRPData &data,int posi, int posj){

	unsigned int capNeeded = 0;
	for(int k = posi ; k <= posj ; k++){
		capNeeded += data.getDemand(getRealNodeFromPos(k));
	}
	return capNeeded <= capacity;
}

int GiantTour::isArcPresent(int posi, int posj){

	int size = arcs.size();

	int i = getRealNodeFromPos(posi);
	int j = getRealNodeFromPos(posj);
	for(int k=0;k<size;k++){
		if(arcs[k].getSource()==i && arcs[k].getTarget()==j)
			return 1;
	}
	return 0;
}

int GiantTour::isPossible(const CVRPData& data,int posi, int posj){

	int poss = isArcPresent(posi,posj-1);

	if (poss && isCapSufficient(data,posi+1,posj)){
		return 1;
	}
	return 0;
}

void GiantTour::addShortcuts(const CVRPData &data){

	for(int i=0;i<(int)nodes;i++){
		for(int j=i+1;j<(int)nodes;j++){
			int possible = isPossible(data,i,j);
			if(possible){
				ArcCVRP a(getRealNodeFromPos(i),getRealNodeFromPos(j),newArcCost(data,i+1,j));
				arcs.push_back(a);
			}
		}
	}
}

int GiantTour::newArcCost(const CVRPData& data, int posi, int posj){

	int newCost = data.getDistance(0,getRealNodeFromPos(posi)) + data.getDistance(getRealNodeFromPos(posj),0);
	for(int k=posi;k<posj;k++)
		newCost+=data.getDistance(getRealNodeFromPos(k),getRealNodeFromPos(k+1));
	return newCost;
}


int GiantTour::getNearestNode(int dist[], unsigned int size, int treated[]){
	int shortestDist = INT_MAX;
	int nearest = -1;
	for(unsigned int i=0;i<size;i++){
		if((shortestDist > dist[i]) && (treated[i]==0)){
			shortestDist = dist[i];
			nearest = i;
		}
	}
	return nearest;
}

int GiantTour::getMinDist(int d1, int d2){
	if(d1<d2)
		return d1;
	else
		return d2;
}

void GiantTour::getShortestPath(const CVRPData &data){

	int current;
	int treatedNodes[nodes];
	int distFromStart[nodes];
	int previousNode[nodes];

	distFromStart[0]=0;
	
	for(unsigned int i=0;i<nodes;i++){
		distFromStart[i]= INT_MAX - 1;
		treatedNodes[i]=0;
		previousNode[i]=-1;
	}
	distFromStart[0]=0;
	previousNode[0]=0;

	for(unsigned int i=0;i<arcs.size();i++){
		if(arcs[i].getSource() == 0){
			distFromStart[arcs[i].getTarget()] = getMinDist(distFromStart[arcs[i].getTarget()],arcs[i].getDistance());
			previousNode[arcs[i].getTarget()] = arcs[i].getSource();
		}
	}

	unsigned int cptnode=0;

	while(cptnode<nodes){

		current = getNearestNode(distFromStart,nodes,treatedNodes);

		for(unsigned int i=0;i<arcs.size();i++){

			if(arcs[i].getSource() == current && !treatedNodes[arcs[i].getTarget()]){

				int actual = distFromStart[arcs[i].getTarget()];
				int newd = arcs[i].getDistance() + distFromStart[arcs[i].getSource()];
				if(newd < actual){
					distFromStart[arcs[i].getTarget()] = newd;
					previousNode[arcs[i].getTarget()] = current;
				}

			}
		}
		cptnode++;
		treatedNodes[current]=1;
	}

	while(current!=0){
		ArcCVRP a(previousNode[current],current,distFromStart[current]);
		shortestPath.push_back(a);
		current=previousNode[current];
	}
}

void GiantTour::getTours(const CVRPData& data){

	int j,i;

	for(i=(shortestPath.size()-1);i>=0;i--){
		Tour t;
		t.totalLength=0;
		t.totalLength += data.getDistance(0,getRealNodeFromPos(getPosFromRealNode(shortestPath[i].getSource())+1));

		for(j = (getPosFromRealNode(shortestPath[i].getSource())+1) ; j<(getPosFromRealNode(shortestPath[i].getTarget())) ; j++){

			int reali = getRealNodeFromPos(j);
			t.clients.push_back(reali);
			int len = data.getDistance(reali, getRealNodeFromPos(j+1));
			t.totalLength +=len;
		}
		t.totalLength += data.getDistance(getRealNodeFromPos(j),0);
		t.clients.push_back(shortestPath[i].getTarget());
		
		tours.push_back(t);

		totalLength += t.totalLength;
	}
}

void GiantTour::displayArcs(const CVRPData& data){

	for(unsigned int i=0;i<arcs.size();i++){
		cout << "arc " << arcs[i].getSource() << "," << arcs[i].getTarget() << " distance : " << arcs[i].getDistance() << endl;
	}
}

void GiantTour::displayTours(){

	cout << "\t\tNombre de tournées : "<<  tours.size() << endl;
	for(unsigned int i=0;i<tours.size();i++){
		totalLength += tours[i].totalLength;
		cout << "\tTour " << i << " de distance " << tours[i].totalLength << endl;
		for(unsigned int j=0;j<tours[i].clients.size();j++)
			cout << "\t\tClient " << tours[i].clients[j] << endl;
	}
	cout << "\t\t\tpour une distance total de " << totalLength << endl;
}

char* GiantTour::getToursString() const{
	char * s;
	asprintf(&s,"%ld tournées\n",tours.size());
	for(unsigned int i=0;i<tours.size();i++){
		asprintf(&s,"%sTour #%d de distance %d : ",s,i+1,tours[i].totalLength);
		for(unsigned int j=0;j<tours[i].clients.size();j++)
			asprintf(&s,"%s%d ",s,tours[i].clients[j]);
		asprintf(&s,"%s\n",s);
	}
	asprintf(&s,"%spour une distance totale de %d",s,totalLength);
	return s;
}

unsigned int GiantTour::getNbNodes()const{
	return nodes;
}

unsigned int GiantTour::getCapacity() const{
	return capacity;
}

int GiantTour::getNbTours() const{
	return tours.size();
}

char* GiantTour::getMethode() const{
	return methode;
}

ostream& operator<<(ostream& os ,const GiantTour& gt ){
  	os << " avec " << gt.getMethode() <<endl;
  	os << "Tours : " << gt.getToursString();
    return os;
}