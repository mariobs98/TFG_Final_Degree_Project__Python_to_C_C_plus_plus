/*
 * Nodo.h
 *
 *  Created on: 26 ago 2021
 *      Author: mario
 */

#ifndef NODO_H_
#define NODO_H_

#include <vector>
#include <algorithm>
#include "RNAestructura.h"
#include "SimpleRNG.h"

extern int global;

extern SimpleRNG sRNG;

class Nodo {
public:

	int position;
	int pt;
	Nodo *NodoPadre;
	vector<Nodo*> NodosHijos;
	Nodo *NodoHijo;
	double victorias;
	int visitas;
	vector<int> untriedSearches;
	vector<int> untriedUBPP;
	vector<int> untriedBPP;
	vector<int> untriedPositions;
	RNAestructura RNA;


	Nodo();
	Nodo(int position, int pt, Nodo *NodoPadre, RNAestructura *RNA);	//state = RNAestructura
	virtual ~Nodo();

	//Devuelve el ultimo nodo, despues de hacer una ordenacion.
	Nodo* SeleccionarNodo();

	//Añade el nodo indicado por parameto al vector de nodos hijos.
	void AnadirNodo(int m, int k, Nodo &n);

	//Actualiza las victorias y visitas del nodo.
	void ActualizarNodo(double resultado);

	//Muestra el vector UntriedPositions.
	void MostrarUntriedPositions();

};

#endif /* NODO_H_ */
