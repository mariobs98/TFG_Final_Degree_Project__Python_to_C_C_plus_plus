//============================================================================
// Name        : Prueba.cpp
// Author      : Mario
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
extern "C"
{
#include <ViennaRNA/fold.h>
#include <ViennaRNA/utils/basic.h>
}
#include <time.h>
#include "MetodosCarga.h"
#include "MetodosDeCalculo.h"
#include "Nodo.h"
#include "SimpleRNG.h"
using namespace std;

vector<int> vectorPuntos;//str_uindex
vector<parParentesis> vectorParentesis;//str_index
vector<string> mIdeaParentesis;
vector<string> mIdeaPuntos;

vector<int> parentesisSeparados;//  -(a)	//Indices de los pares de parentesis, por separado
list<int> b_;
vector<int> b;	//Vector parentesis separados, ordenado de menor a mayor.
vector<int> c;	//Ordenacion
vector<string> d;	//Bases de los pares de parentesis, separadas en caracteres individuales.

vector<string> BASEPAIRS = {"AU", "CG", "GC", "UA"};
vector<string> BASES = {"A", "G", "C", "U"};

string parametro_s;	//"input the dot-branket representation of the RNA secondary structure"
float parametro_gc = 0.5; //"input the target GC content,the default GC-content is 0.5"
float parametro_d = 0.01; //"input the GC content error range [0, 0.02],the default GC-content error is 0.01 for nested structures, 0.02 for pseudoknot structures"
int parametro_pk = 0; //"this is for handling pseduoknot structures, you can use different pseduoknot prediction software, value=1 means choose pKiss, value=0 means choose RNAfold"
						//todo uso 0 de momento en esta ejecucion, no contemplo corchetes.

string ini_seq;
vector<string> ini_str_seq;

string best_str = "";
float max_val = 0;
double GCC = 0;

SimpleRNG sRNG;

//int MAX_IT=0;

//-s "(.(.))" -GC 2 -d 3 -pk 0
//(((((.....))..((.........)))))
//((((....)).))
//..(((((..(((...)))..)))))...		funciona
//...(((((..........)))))........((((((((......))))))))(((((.......))))).............(((((..(((((..((..((.(((((.(((((.......))))).)))))...))....))))))))))))
//(((((((((....((.(((((...((..((((((.......))..))))..))....)))))..))(((.((..(.((....((....)).....)).).)).))).))))))))).
//argc- numero de parametros
//argv- parametros( el 0 es el nombre del ejecutable(./xyz) )
 int main(int argc,char *argv[]) {

	 int aleatorio = time(NULL);
	 //srand (aleatorio);

	 //srand (1639567733);
	 //1639567733
	 //cout<< " Semilla: " << aleatorio << endl;

	 int semillaParametro;
	 if(argc >= 10){
		 semillaParametro = atoi(argv[9]);
		 cout<<"Semilla por parametro: "<< semillaParametro <<endl;
	 }

	 /*if(argc >= 11){
		 MAX_IT = atoi(argv[10]);
		 cout<<"Maximas iteraciones: "<< MAX_IT <<endl;
	 }*/

	 //SimpleRNG sRNG;
	 //7,7
	 //123456,123456
	 //987654,987654
	 //117,771
	 //sRNG.SetState(987654,987654);

	 //nogc
	 //1234,1234
	 //987654,987654
	 //7,7
	 sRNG.SetState(semillaParametro, semillaParametro);

	 cout.precision(12);


	if (!ObtenerParametros(argc, argv, parametro_s, parametro_gc, parametro_d, parametro_pk)) {
		printf("Ejecución incorrecta\nEl formato correcto es %s"
				" [-s] target RNA secondary structure"
				" [-GC] target GC-content of the RNA sequence"
				" [-d] GC-content deviation of the solution"
				" [-pk] nested structure -pk 0 and pseudoknot structure -pk 1"
				"\n", argv[0]);
		return 0;
	}

	int tamanoParametroS = parametro_s.length();	//Tamaño de la cadena de entrada
    cout <<  "Tamaño parametro S(secuencia punto-parentesis): "<< tamanoParametroS << endl;

	//Obtengo en que posicion se encuentran los puntos en el parametro_s	(str_uindex)
	ObtenerPuntos(vectorPuntos, parametro_s, tamanoParametroS);
	//Obtengo el par correspondiente de parentesis de apertura y cierre		(str_index)
	ObtenerListaParentesis(vectorParentesis, parametro_s, tamanoParametroS);
	//Muestro las listas obtenidas
	MostrarListas(vectorPuntos, vectorParentesis);

	//mIdeaParentesis-(midea)
	GetBasePairs(vectorParentesis, BASEPAIRS, mIdeaParentesis);

	printf("mIdeaParentesis: ");
    for (string elemento : mIdeaParentesis) { cout << elemento << "  "; } cout << endl;

	//mIdeaPuntos-(copy_str_uindex)
	GetBaseUnpairs(vectorPuntos, BASES, mIdeaPuntos);

	printf("mIdeaPuntos: ");
    for (string elemento : mIdeaPuntos) { cout << elemento << "  "; } cout << endl;

//A = vectorParentesis
	SepararParentesis(vectorParentesis, parentesisSeparados);
	printf("A -> Parentesis Separados: ");
	for (int elemento : parentesisSeparados) { cout << elemento << "  "; } cout << endl;

//B = b
	//list<int> b_(parentesisSeparados.begin(), parentesisSeparados.end());	//esta linea si no se hace con el copy, el debugger no ejecuta, no entiendo el por qué
	copy( parentesisSeparados.begin(), parentesisSeparados.end(),back_inserter( b_ ) );
	b_.sort();
	copy(b_.begin(), b_.end(), back_inserter(b));
	printf("B -> Parentesis Ordenados: ");
    for (int elemento : b) { cout << elemento << "  "; } cout << endl;

//C = c
    //todo parentesis separados es variable global, se puede elminar el paso a la funcion
	ce(parentesisSeparados, c);
	printf("C -> Ordenacion : ");
    for (int elemento : c) { cout << elemento << "  "; } cout << endl;

//D = d Separar los pares de bases
	SepararBasePairs(mIdeaParentesis, d);
	printf("D -> Separacion de BasePairs(mIdeaParentesis): ");
    for (string elemento : d) { cout << elemento << "  "; } cout << endl;


//getWholeSequence
	getSecuenciaCompleta(b, c, d, mIdeaPuntos, ini_seq, ini_str_seq);
	printf("getWholeSequence -> ini_str_seq: ");
    for (string elemento : ini_str_seq) { cout << elemento << "  "; } cout << endl;
    //for(auto ele : ini_str_seq){cout << ele << "  ";}cout << endl;

	printf("getWholeSequence -> ini_seq: ");
    cout << ini_seq << endl;

//UCTRNA
    cout<< "Parametro_GC " << parametro_gc << endl;
    time_t tiempoInicial = time(NULL);

    if(parametro_gc>=0 && parametro_gc<=1){
    	UCTRNA(best_str, max_val, GCC);
    }else{
    	UCTRNAnoGC(best_str, max_val, GCC);
    }

    time_t tiempoSalida= time(NULL);

    cout << "Tiempo empleado: " << difftime(tiempoSalida, tiempoInicial) << " segundos\n" << endl;

	cout << " Exito. Fin de Ejecucion " << endl;

	return 0;
}
