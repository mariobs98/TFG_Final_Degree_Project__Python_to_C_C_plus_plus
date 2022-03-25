/*
 * MetodosCarga.h
 *
 *  Created on: 7 jul 2021
 *      Author: mario
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <list>
#include <vector>
#include <algorithm>
#include "SimpleRNG.h"
using namespace std;

#ifndef METODOSCARGA_H_
#define METODOSCARGA_H_

extern SimpleRNG sRNG;

struct parParentesis {
	int apertura = -1;
	int cierre = -1;
};

//todo -> revisar explicaciones

//Obtiene los parametros de entrada y realiza unas comprobaciones
int ObtenerParametros(int argc, char *argv[], string &parametro_s, float &parametro_gc, float &parametro_d, int &parametro_pk);

//Del parametro de entrada S, obtiene los indices de donde se situan los puntos
void ObtenerPuntos(vector<int> &vectorPuntos, string &parametro_s, int tamanoParametroS);

//Del parametro de entrada S, obtiene los indices de donde se situan los pares de parentesis apertura-cierre
void ObtenerListaParentesis(vector<parParentesis> &vectorParentesis, string &parametro_s, int tamanoParametroS);

//Muestra las listas de puntos y parentesis obtenidas al inicio
void MostrarListas(vector<int> &vectorPuntos, vector<parParentesis> &vectorParentesis);

//Obtiene una lista de BASEPAIRS aleatorios de longitud la lista de parentesis
void GetBasePairs(vector<parParentesis> &vectorParentesis, vector<string> &BASEPAIRS, vector<string> &mIdeaParentesis);

//Obtiene una lista de BASES aleatoriosde longitud la lista de puntos
void GetBaseUnpairs(vector<int> &vectorPuntos, vector<string> &BASES, vector<string> &mIdeaPuntos);

//Coge los pares de parentesis apertura-cierre, y los separa del struct metiendo los valores por separado en una lista de enteros
void SepararParentesis(vector<parParentesis> &vectorParentesis, vector<int> &parentesisSeparados);

void ce(vector<int> &parentesis, vector<int> &c);

//Bases de los pares de parentesis, separadas en caracteres individuales.
void SepararBasePairs(vector<string> &mIdeaParentesis, vector<string> &d);

//getWholeSequence
void getSecuenciaCompleta(vector<int> b, vector<int> c, vector<string> d, vector<string> mIdeaPuntos, string &ini_seq,vector<string> &ini_str_seq);

#endif /* METODOSCARGA_H_ */
