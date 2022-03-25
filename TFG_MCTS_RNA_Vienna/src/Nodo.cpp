/*
 * Nodo.cpp
 *
 *  Created on: 26 ago 2021
 *      Author: mario
 */

#include "Nodo.h"
#include "math.h"

Nodo::Nodo() {
this->position = -1;
this->pt = -1;
this->NodoPadre = NULL;
this->NodosHijos;
this->NodoHijo = NULL;
this->victorias = 0;
this->visitas = 0;
this->untriedSearches;
this->untriedUBPP;
this->untriedBPP;
this->untriedPositions;
this->RNA;
}

Nodo::Nodo(int position, int pt, Nodo *NodoPadre, RNAestructura *RNA) {
this->position = position;
this->pt = pt;
this->NodoPadre = NodoPadre;
this->NodoHijo = NULL;
this->victorias = 0;
this->visitas = 0;
this->RNA = *RNA;
this->untriedSearches = RNA->GetSearch();
this->untriedUBPP = RNA->Getubpp();
this->untriedBPP = RNA->Getbpp();
this->untriedPositions = RNA->GetPositions();
}

Nodo::~Nodo() {

}

//todo mirar funciones lambda en c++
Nodo* Nodo::SeleccionarNodo(){

	struct parNodo {
		double valor = 0;
		int index = 0;
	};

	//cout<<endl;
	vector<Nodo*> NodosHijos_copia = this->NodosHijos;
	vector<Nodo*> prueba;
	//vector<double> enterosPrueba;
	vector<parNodo> parPrueba;

	//cout<<endl;
	//cout << "Ordenacion prueba:"<<endl;
	for(unsigned i=0; i<NodosHijos.size(); i++){
		//cout<<"[position, pt]: " << this->NodosHijos[i]->position << " / " << this->NodosHijos[i]->pt <<endl;
		//cout<<"[victorias, visitas]: " << this->NodosHijos[i]->victorias << " / " << this->NodosHijos[i]->visitas<<endl;
		double sol = ( (this->NodosHijos[i]->victorias/this->NodosHijos[i]->visitas)+(0.1*sqrt(2*log(this->visitas)/this->NodosHijos[i]->visitas)) );
		//enterosPrueba.push_back(sol);
		parNodo pp;
		pp.valor = sol;
		pp.index = i;
		parPrueba.push_back(pp);
		//cout << "Ecuación: "<< pp.valor << endl;
	}

	//cout << "Vector double prueba - PRE sort:"<<endl;
	//for(unsigned i=0; i<parPrueba.size(); i++){
	//	cout << "Resultados / I: "<< parPrueba[i].valor<< " / "<< parPrueba[i].index << endl;
	//}
	//cout<<endl;

	sort(parPrueba.begin(), parPrueba.end(), [ ]( const auto& lhs, const auto& rhs )
	{
		return lhs.valor < rhs.valor;
	});

	//cout << "Vector double prueba - POST sort:"<<endl;
	//for(unsigned i=0; i<parPrueba.size(); i++){
	//	cout << "Resultados / I: "<< parPrueba[i].valor<< " / "<< parPrueba[i].index << endl;
	//}
	//cout<<endl;

	//int maxElementIndex = std::max_element(enterosPrueba.begin(),enterosPrueba.end()) - enterosPrueba.begin();
	//cout << "maxElementIndex: "<< maxElementIndex << endl;
/*
	for(unsigned i=maxElementIndex; i<enterosPrueba.size(); i++){
		if(enterosPrueba[maxElementIndex] == enterosPrueba[i]){
			maxElementIndex = i;
			cout << "NUEVO maxElementIndex: "<< maxElementIndex << endl;
		}
	}


	cout<<endl;
	cout<<"Seleccionar Nodo: "<<endl;
	cout<<"[position, pt]: " << NodosHijos_copia[maxElementIndex]->position << " / " << NodosHijos_copia[maxElementIndex]->pt <<endl;
	cout<<"[victorias, visitas]: " << NodosHijos_copia[maxElementIndex]->victorias << " / " << NodosHijos_copia[maxElementIndex]->visitas<<endl;

	return NodosHijos_copia[maxElementIndex];
	*/
	//cout<<endl;
	//cout<<"Seleccionar Nodo: "<<endl;
	//cout<<"[position, pt]: " << NodosHijos_copia[parPrueba.back().index]->position << " / " << NodosHijos_copia[parPrueba.back().index]->pt <<endl;
	//cout<<"[victorias, visitas]: " <<NodosHijos_copia[parPrueba.back().index]->victorias << " / " << NodosHijos_copia[parPrueba.back().index]->visitas<<endl;
	return NodosHijos_copia[parPrueba.back().index];
}

void Nodo::AnadirNodo(int m, int k, Nodo &n){
    if (find(this->untriedPositions.begin(), this->untriedPositions.end(), k) != this->untriedPositions.end()) {
	    vector<int>::iterator new_end;
	    //new_end = remove(this->untriedPositions.begin(), this->untriedPositions.end(), k);
	    this->untriedPositions.erase(remove(this->untriedPositions.begin(), this->untriedPositions.end(), k), this->untriedPositions.end());
    }
    this->NodosHijos.emplace_back(&n);
    this->NodoHijo = &n;

	//cout<<"Añadir Nodo: "<<endl;
	//cout<<"[position, pt]: " << n.position << " / " << n.pt <<endl;
	//cout<<"[victorias, visitas]: " << n.victorias << " / " << n.visitas <<endl;
}

void Nodo::ActualizarNodo(double resultado){
	this->visitas = this->visitas + 1;
	this->victorias = this->victorias + resultado;
}

void Nodo::MostrarUntriedPositions(){
	cout<< "UntriedPositions: "<< endl;
	for(int elemento : this->untriedPositions){
		cout << elemento << " " <<endl;
	}
}









