#include <iostream>
#include <cstring>



#include "arcCVRP.hpp"

ArcCVRP::ArcCVRP():source(-1), target(-1), distance(-1){}

ArcCVRP::ArcCVRP(int s, int t, float d):source(s), target(t), distance(d){}

ArcCVRP::ArcCVRP(const ArcCVRP &a){

	source = a.getSource();
	target = a.getTarget();
	distance = a.getDistance();
}


ArcCVRP::~ArcCVRP(){}

int ArcCVRP::getSource() const {
	return source;
}

int ArcCVRP::getTarget() const {
	return target;
}

float ArcCVRP::getDistance() const{
	return distance;
}

bool ArcCVRP::operator<(const ArcCVRP& a) const
{
	if(distance == a.distance){
		if(source == a.source){
			return target<a.getTarget();

		}
		else
			return source<a.getSource();
	}
	else
    	return (distance < a.distance);
}