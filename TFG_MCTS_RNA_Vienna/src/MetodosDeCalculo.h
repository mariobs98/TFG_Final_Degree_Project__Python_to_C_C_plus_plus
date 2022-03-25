/*
 * MetodosDeCalculo.h
 *
 *  Created on: 10 ago 2021
 *      Author: mario
 */
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "RNAestructura.h"
#include "Nodo.h"
#include "SimpleRNG.h"

extern "C"
{
#include <ViennaRNA/fold.h>
#include <ViennaRNA/utils/basic.h>
}


#ifndef METODOSDECALCULO_H_
#define METODOSDECALCULO_H_

extern vector<int> parentesisSeparados;// -(a)
extern vector<int> b;
extern vector<int> c;
extern vector<string> d;

extern string parametro_s;
extern float parametro_gc;
extern float parametro_d;
extern int parametro_pk;

extern vector<int> vectorPuntos;//str_uindex
extern vector<parParentesis> vectorParentesis;//str_index

extern SimpleRNG sRNG;

//extern int MAX_IT;

void UCTRNA(string &best_str, float &max_val, double &GCC);

void UCTRNAnoGC(string &best_str, float &max_val, double &GCC);

void MCTS(RNAestructura *root, int k, string &best_str_solution, float &max_val_solution, double &GCC_solution);

void MCTSnoGC(RNAestructura *root, int k, string &best_str_solution, float &max_val_solution, double &GCC_solution);

int calculate_GC_numbers(vector<string> eposl, float parametro_gc, vector<positionStruct> need, vector<positionStruct> poslalpha);

void calculate_mfe_and_str(string sequence, float &mfe, string &str_v);

double calculate_structure_distance(string structure_s, float str_length, string some_str_value);

double measureGC(string generate_seq);

void check_GC_base3(vector<parParentesis> &some_dif_ini,vector<positionStruct> &predicted_seq, vector<positionStruct> &posl);

void check_GC_base(vector<parParentesis> &some_dif_ini,vector<positionStruct> &predicted_seq, vector<positionStruct> &posl);

void dif_str(string &some_str_value, vector<parParentesis> &paired_pos, vector<parParentesis> &dif_ini);

void calculate_sequence_position(string &seq, vector<parParentesis> &struc, vector<int> &ustruc);

void GCcontent(float parametro_gc, double getGC, vector<parParentesis> &some_paired_pos, vector<positionStruct> &predicted_seq, vector<positionStruct> &posl);

void check_seq_base(float parametro_gc, double getGC, vector<parParentesis> &some_paired_pos, vector<positionStruct> &predicted_seq, vector<positionStruct> &posl);


vector<positionStruct> unirIndexYUindex();
bool esPunto(int numPosition, vector<positionStruct> vector);
bool esParParentesis(int numPosition, vector<positionStruct> vector);
bool hayBase(int numPosition, vector<positionStruct> vector);


#endif /* METODOSDECALCULO_H_ */
