/*
 * RNAestructura.cpp
 *
 *  Created on: 10 ago 2021
 *      Author: mario
 */

#include "RNAestructura.h"

RNAestructura::RNAestructura() {

	this->Search = {"", "", "", "", "", "", "", "", "", ""};
	this->BASEPAIRS_RNA = {"AU", "CG", "GC", "UA", "GU", "UG"};
	this->BASES_RNA = {"A", "C", "G", "U", "AU", "CG", "GC", "UA", "GU", "UG"};
	this->BASE_RNA = {"A", "C", "G", "U"};
	//this->position;     //vector en el que guardo los caracteres que va cambiando de la "positionStructVector"
	//this->positionStructVector;     //en python une puntos con lista parentesis en una misma variable.(este vector guarda eso en forma de struct de 3 variables)
	this->n = vectorPuntos.size() + vectorParentesis.size();
	this->number = 0;

	rellenarPositionStructVector();

    //MostrarPositionStructVector();
}

RNAestructura::~RNAestructura() {

}

//Relleno positionStructVector con la union de la posicion de los puntos y el parParentesis
void RNAestructura::rellenarPositionStructVector(){
	positionStruct posStruct;
	for(unsigned i=0; i<vectorPuntos.size(); i++){
		posStruct.punto = vectorPuntos[i];
		this->positionStructVector.push_back(posStruct);
		posStruct.punto = -1;
	}

    for (parParentesis par : vectorParentesis) {
        posStruct.apertura = par.apertura;
        posStruct.cierre = par.cierre;
		this->positionStructVector.push_back(posStruct);

        posStruct.apertura = -1;
        posStruct.cierre = -1;
    }
}

bool RNAestructura::esPunto(int numPosition){
	if(this->positionStructVector[numPosition].punto != -1){
		return true;
	}
	return false;
}

bool RNAestructura::esParParentesis(int numPosition){
	if( (this->positionStructVector[numPosition].apertura != -1) && (this->positionStructVector[numPosition].cierre != -1) ){
		return true;
	}
	return false;
}

bool RNAestructura::hayBase(int numPosition){
	if(this->positionStructVector[numPosition].base != ""){
		return true;
	}
	return false;
}

void RNAestructura::count(){
	this->number++;
}

//Clona los datos de la clase a la estructura que se pasa por parametro
void RNAestructura::Clone(RNAestructura *clon){
	clon->Search = this->Search;
	clon->BASEPAIRS_RNA = this->BASEPAIRS_RNA;
	//clon->position = this->position;
	clon->positionStructVector = this->positionStructVector;
}

//TODO ¿en python no entra en rewards en las ejecuciones??
void RNAestructura::Rewards(int k){
	//std::vector<parParentesis> a_(vectorParentesis.begin(), vectorParentesis.end());
	//std::vector<int> b_(b.begin(), b.end());
	//std::vector<int> c_(c.begin(), c.end());
	//std::vector<string> d_(d.begin(), d.end());

	vector<string> posBaseP;
	/*
	struct posBaseStruct {
		int entero = -1;
		string cadena = "";
	};*/
	vector<string> posBase;

	//Esto es comun a ambos if
	int contador = 0;
	for(unsigned i=vectorPuntos.size(); i < this->n; i++){
		//posBaseP[contador] = this->position[i];
		contador++;
	}
	contador=0;
	for(unsigned i=0; i < vectorPuntos.size(); i++){
		//posBase[contador] = this->position[i];
		contador++;
	}
	contador=0;
	//e=list(itertools.chain(*posbasep)) en python hace esto, ¿crea una lista de la variable posbasep?
									//yo ya tengo la lista e=posBaseP

	//for(int i=0; i<a_.size(); i++){
		//posBase[i] =
	//}
	/*
	if(k > puntos.size()-1){	}
	if(k <= puntos.size()-1){	}
	*/

}//

void RNAestructura::SelectBasePairs(int move){
	this->Search[move] = this->BASEPAIRS_RNA[move];
}

void RNAestructura::SelectStatePosition(int l){
	if(l > vectorPuntos.size()-1){
		this->positionStructVector[l].base = mIdeaParentesis[l - vectorPuntos.size()];
	}else{
		this->positionStructVector[l].base = mIdeaPuntos[l];
	}
}

void RNAestructura::Simulation(int l){
	int aleatorio;

	if(l > vectorPuntos.size()-1){
		aleatorio = sRNG.GetUint() % BASEPAIRS.size();
		this->positionStructVector[l].base =  BASEPAIRS[aleatorio];
	}else{
		aleatorio = sRNG.GetUint() % BASES.size();
		this->positionStructVector[l].base = BASES[aleatorio];
	}
}

void RNAestructura::Simulation1(int l, int needgc, int &count_number){
	int aleatorio;
	vector<string> BASES1 = {"CG", "GC"};
	vector<string> BASES2 = {"AU", "UA"};
	vector<string> BASES3 = {"A", "U"};

	if(l > (vectorPuntos.size()-1) && (count_number<=needgc) ){
		aleatorio = sRNG.GetUint() % BASES1.size();
		this->positionStructVector[l].base =  BASES1[aleatorio];
		count_number++;
	}
	if(l > (vectorPuntos.size()-1) && (count_number>needgc) ){
		aleatorio = sRNG.GetUint() % BASES2.size();
		this->positionStructVector[l].base =  BASES2[aleatorio];
	}
	if(l <= vectorPuntos.size()-1){
		aleatorio = sRNG.GetUint() % BASES3.size();
		this->positionStructVector[l].base =  BASES3[aleatorio];
	}

}

void RNAestructura::SimulationGC(int l){
	int aleatorio;
	vector<string> BASES = {"CG", "GC"};
	aleatorio = sRNG.GetUint() % BASES.size();
	this->positionStructVector[l].base = BASES[aleatorio];
}

void RNAestructura::SimulationAU(int l){
	int aleatorio;
	vector<string> BASES = {"AU", "UA"};
	aleatorio = sRNG.GetUint() % BASES.size();
	this->positionStructVector[l].base = BASES[aleatorio];
}

void RNAestructura::SimulationUnpairedAU(int l){
	int aleatorio;
	vector<string> BASES = {"A", "U"};
	aleatorio = sRNG.GetUint() % BASES.size();
	this->positionStructVector[l].base = BASES[aleatorio];
}

void RNAestructura::SimulationUnpairedGC(int l){
	int aleatorio;
	vector<string> BASES = {"G", "C"};
	aleatorio = sRNG.GetUint() % BASES.size();
	this->positionStructVector[l].base = BASES[aleatorio];
}

void RNAestructura::SelectPosition(int m, int k){
	this->positionStructVector[k].base = this->BASES_RNA[m];
	this->positionStructVector[k].punto = -1;
	this->positionStructVector[k].apertura = -1;
	this->positionStructVector[k].cierre = -1;
}

//todo habria que probar que el retorno no esté vacio donde se llame a las funciones.
vector<int> RNAestructura::Getubpp(){
	//std::vector<string> uBASES = {"A", "U", "C", "G"};
	vector<int> retorno;

		//for de 0 a 4
		for(unsigned j=0; j<4; j++){
		    if (find(this->BASE_RNA.begin(), this->BASE_RNA.end(), this->Search[j]) != this->BASE_RNA.end()) {

		    }else{
		        retorno.push_back(j);	//Devuelvo las posiciones en la que se ha encontrado.
		    }
		}
		return retorno;
}

vector<int> RNAestructura::Getbpp(){
	//std::vector<string> pBASES = {"AU", "CG", "GC", "UA", "GU", "UG"};
	vector<int> retorno;

	//for de 4 a 10
		for(unsigned j=4; j<10; j++){
		    if (find(this->BASEPAIRS_RNA.begin(), this->BASEPAIRS_RNA.end(), this->Search[j]) != this->BASEPAIRS_RNA.end()) {

		    }else{
		    	retorno.push_back(j);	//Devuelvo la posicion en la que se ha encontrado.
		    }
		}
		return retorno;
}

vector<int> RNAestructura::GetSearch(){
	//std::vector<string> BASES = {"A", "U", "C", "G","AU", "CG", "GC", "UA", "GU", "UG"};
	vector<int> retorno;

		for(unsigned j=0; j<this->Search.size(); j++){
		    if (find(this->BASES_RNA.begin(), this->BASES_RNA.end(), this->Search[j]) != this->BASES_RNA.end()) {

		    }else{
		    	retorno.push_back(j);	//Devuelvo la posicion en la que se ha encontrado
		    }
		}
		return retorno;
}

//Probado-Funcionamiento correcto
vector<int> RNAestructura::GetPositions(){
	//std::vector<string> BASES = {"A", "U", "C", "G","AU", "CG", "GC", "UA", "GU", "UG"};
	vector<int> retorno;

	for(unsigned j=0; j<this->positionStructVector.size(); j++){
	    if (find(this->BASES_RNA.begin(), this->BASES_RNA.end(), this->positionStructVector[j].base) != this->BASES_RNA.end()) {//si está el elemento...

	    }else{	//Si no está el elemento (Lo que buscamos)
	    	retorno.push_back(j);	//Devuelvo la posicion en la que se ha encontrado
	    }
	}
	return retorno;
}

void RNAestructura::MostrarPositionStructVector(){

	printf("POSITION_STRUCT_VECTOR:  ");
    for (positionStruct p : this->positionStructVector) {
        cout << p.punto << "/" << p.apertura << "/" << p.cierre << "/" << p.base << "  ";
    }
	cout << endl;
}





