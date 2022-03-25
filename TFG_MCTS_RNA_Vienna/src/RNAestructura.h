/*
 * RNAestructura.h
 *
 *  Created on: 10 ago 2021
 *      Author: mario
 */

#ifndef RNAESTRUCTURA_H_
#define RNAESTRUCTURA_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <list>
#include <vector>
#include <algorithm>
#include "MetodosCarga.h"
#include "SimpleRNG.h"
using namespace std;

extern vector<string> BASEPAIRS;
extern vector<string> BASES;

extern vector<int> vectorPuntos;//uindex
extern vector<parParentesis> vectorParentesis;//index
extern vector<string> mIdeaParentesis;
extern vector<string> mIdeaPuntos;

extern vector<int> parentesisSeparados;	//a
extern vector<int> b;
extern vector<int> c;
extern vector<string> d;

struct positionStruct {
	int punto = -1;
	int apertura = -1;
	int cierre = -1;
	string base = "";
};

extern SimpleRNG sRNG;

//TODO no muy seguro del funcionamiento de position y positionStructVector
class RNAestructura {
public:

	vector<string> Search;
	vector<string> BASEPAIRS_RNA;
	vector<string> BASES_RNA;
	vector<string> BASE_RNA;
	//CAMBIO-> QUITO VECTOR POSITION Y METO EL "STRING" BASE EN LA ESTRUCTURA PARA TRABAJAR MEJOR.
	//std::vector<string> position;      //vector en el que guardo los caracteres que va cambiando de la "positionStructVector"
	vector<positionStruct> positionStructVector;     //en python une puntos con lista parentesis en una misma variable.(este vector guarda eso en forma
														  //de struct de 3 variables)
	int n;
	int number;


	RNAestructura();
	virtual ~RNAestructura();

	//Relleno positionStructVector con la union de la posicion de los puntos y el parParentesis
	void rellenarPositionStructVector();

	//Devuelve true si la posicion indicada por parametro del vector, se trata de un punto. Es decir que punto!=-1
	bool esPunto(int numPosition);

	//Devuelve true si la posicion indicada por parametro del vector, se trata de un par de ParParentesis. Es decir que apertura!=-1 y cierre !=-1
	bool esParParentesis(int numPosition);

	//Devuelve true si en la posicion indicada existe una base, es decir que base != "". Que no este vacio.
	bool hayBase(int numPosition);

	//Suma 1 a number
	void count();

	//Clona los datos de la clase a la estructura que se pasa por parametro
	void Clone(RNAestructura *clon);

	//¿no se usa en el codigo de python?
	void Rewards(int k);

	//Copia de Basepairs_RNA a Search la posicion indicada por parametro.
	void SelectBasePairs(int move);

	void SelectStatePosition(int l);

	void Simulation(int l);

	void Simulation1(int l, int needgc, int &count_number);

	void SimulationGC(int l);

	void SimulationAU(int l);

	void SimulationUnpairedAU(int l);

	void SimulationUnpairedGC(int l);

	void SelectPosition(int m, int k);

	vector<int> Getubpp();

	vector<int> Getbpp();

	vector<int> GetSearch();

	vector<int> GetPositions();

	void MostrarPositionStructVector();
};

#endif /* RNAESTRUCTURA_H_ */
