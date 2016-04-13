/*
 * TSP.h
 *
 *  Created on: 22 janv. 2015
 *      Author: fclautiaux
 */

#ifndef TSP_H_
#define TSP_H_


#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std;


class TSPData{
private :

	/* matrice de distances*/
	long ** matrix;
	/* taille de la matrice (size * size) */
	int size;

public :

	/* initialise la donnée TSP avec un fichier d'entrée */
	TSPData(fstream & in){

		string s;

		size=-1; // plus facile à débuger si bug lecture

		getline(in,s); // ligne de blabla
		getline(in,s); // ligne de blabla
		getline(in,s); // ligne de blabla

		in >> s; // blabla

		in >> size; // lecture de la taille

		matrix = new long* [size];
		for (int i = 0; i < size; i++) {
			matrix[i] = new long[size];
		}

		getline(in,s); // blabla
		getline(in,s); // blabla
		getline(in,s); // blabla

		double * x = new double[size]; // lecture des coordonnees
		double * y = new double[size];
		for (int i = 0; i < size; i++) {
			in >> s; // numero de ligne
			in >> x[i];
			in >> y[i];
		}

		for (int i = 0; i < size; ++i) { // calcul des distances
			for (int j = 0; j < size; ++j) {
				if (i == j) {
					matrix[i][j] = std::numeric_limits<long>::max();
				} else {
					matrix[i][j] = (long)floor(sqrt((x[i] - x[j]) * (x[i] - x[j])
							+ (y[i] - y[j]) * (y[i] - y[j]))+0.5);
				}
			}
		}

		delete[] y;
		delete[] x;
	}

	~TSPData(){
		for(int i=0;i<size;++i){
			delete[] matrix[i];
		}
		delete[] matrix;
	}


	/* retourne la matrice de doubles */
	long ** getMatrix(){
		return matrix;
	}

	/* retourne la taille du probleme lu */
	int getSize() const{return size;}

	/* retourne la distance entre i et j */
	long getVal(int i, int j) const{return matrix[i][j];}


};


#endif /* TSP_H_ */
