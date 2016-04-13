//============================================================================
// Name        : TSP.cpp
// Author      : F.C.
// Version     :
// Copyright   : Free for all
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "TSP.h"

using namespace std;



int main(int argc, char * argv[]) {

	fstream toto(argv[1], fstream::in);

	TSPData data(toto);


	toto.close();

	return 0;
}
