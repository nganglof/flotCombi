#include <iostream>
#include <cstring>

#include "arc.hpp"

Arc::Arc():source(-1), target(-1), distance(-1){}

Arc::Arc(int s, int t, float d):source(s), target(t), distance(d){}

Arc::~Arc(){}

int Arc::getSource(){
	return source;
}

int Arc::getTarget(){
	return target;
}

float Arc::getDistance(){
	return distance;
}

bool Arc::operator<(const Arc& a) const
{
    return (distance < a.distance);
}