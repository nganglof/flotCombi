#include <iostream>
#include <cstring>

#include "arc.hpp"

Arc::Arc():source(-1), target(-1), distance(-1){}

Arc::Arc(int s, int t, float d):source(s), target(t), distance(d){}

Arc::Arc(const Arc &a){

	source = a.getSource();
	target = a.getTarget();
	distance = a.getDistance();
}


Arc::~Arc(){}

int Arc::getSource() const {
	return source;
}

int Arc::getTarget() const {
	return target;
}

float Arc::getDistance() const{
	return distance;
}

bool Arc::operator<(const Arc& a) const
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