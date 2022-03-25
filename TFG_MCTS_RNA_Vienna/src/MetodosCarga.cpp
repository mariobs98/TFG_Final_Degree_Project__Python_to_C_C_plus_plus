
#include "MetodosCarga.h"



//Comprobacion de parametros, tienen que estar todos con el formato correcto. No se comprueba el "valor" puesto.
//Si uno de los parametros intermedios no esta, falla, no se hace esa comprobacion. Tienen que estar en orden o bien faltar
//parametros por el final y se escogen los valores default.
int ObtenerParametros(int argc, char *argv[], string &parametro_s, float &parametro_gc, float &parametro_d, int &parametro_pk) {
	int i;
	//nombre, -s + valor, -GC + valor, -d + valor, -pk + valor. (9 parametros)
	if (argc<2)	//Al menos tiene que estar el parametro -s, los otros tienen valores default
		return 0;

	for (i=1; i<argc; i = i+2) {
		switch(i)
		{
			case 1:
				if (strcmp(argv[i], "-s")!=0){
			        printf("Parametro argv[%d]: %s incorrecto \n", i, argv[i]);	return 0;
				}
				parametro_s = argv[2];
				break;

			case 3:
				if (strcmp(argv[i], "-GC")!=0){
			        printf("Parametro argv[%d]: %s incorrecto \n", i, argv[i]);	return 0;
				}
				if(argv[4] != NULL)
					parametro_gc = atof(argv[4]);
				break;

			case 5:
				if (strcmp(argv[i], "-d")!=0){
			        printf("Parametro argv[%d]: %s incorrecto \n", i, argv[i]);	return 0;
				}
				if(argv[6] != NULL)
					parametro_d = atof(argv[6]);
				break;

			case 7:
				if (strcmp(argv[i], "-pk")!=0){
			        printf("Parametro argv[%d]: %s incorrecto \n", i, argv[i]);	return 0;
				}
				if(argv[8] != NULL)
					parametro_pk = atoi(argv[8]);
				break;
		}
	}
	return 1;//lectura correcta
}

void ObtenerPuntos(vector<int> &vectorPuntos, string &parametro_s, int tamanoParametroS){
	for(int i = 0; i < tamanoParametroS; i++){
		if (parametro_s[i] == '.'){
			vectorPuntos.push_back(i);
		}
	}
}

void ObtenerListaParentesis(vector<parParentesis> &vectorParentesis, string &parametro_s, int tamanoParametroS){
	list<int> stack;
	parParentesis par;
	int ultimo;

	for(int i = 0; i < tamanoParametroS; i++){
		if (parametro_s[i] == '('){
			stack.push_back(i);
		}else if(parametro_s[i] == ')'){
			ultimo = stack.back();
			par.apertura = ultimo;
			stack.pop_back();
			par.cierre = i;
			vectorParentesis.push_back(par);
		}
	}
}

void MostrarListas(vector<int> &vectorPuntos, vector<parParentesis> &vectorParentesis){
	printf("Puntos: ");
    for (int punto : vectorPuntos) {
        cout << punto << "  ";
    }
	cout << endl;

	printf("Pares de Parentesis: ");
    for (parParentesis par : vectorParentesis) {
        cout << par.apertura << "/" << par.cierre << "  ";
    }
	cout << endl;
}

void GetBasePairs(vector<parParentesis> &vectorParentesis, vector<string> &BASEPAIRS, vector<string> &mIdeaParentesis){
	int aleatorio;

	for(unsigned i=0; i<vectorParentesis.size(); i++){
		aleatorio = sRNG.GetUint() % BASEPAIRS.size();
		mIdeaParentesis.push_back(BASEPAIRS[aleatorio]);
	}

}

void GetBaseUnpairs(vector<int> &vectorPuntos, vector<string> &BASES, vector<string> &mIdeaPuntos){
	int aleatorio;

	for(unsigned i=0; i<vectorPuntos.size(); i++){
		aleatorio = sRNG.GetUint() % BASES.size();
		mIdeaPuntos.push_back(BASES[aleatorio]);
	}
}

void SepararParentesis(vector<parParentesis> &vectorParentesis, vector<int> &parentesisSeparados){
    for (parParentesis par : vectorParentesis) {
    	parentesisSeparados.push_back(par.apertura);
    	parentesisSeparados.push_back(par.cierre);
    }
}

void ce(vector<int> &parentesisSeparados, vector<int> &c){
	//Parentesis separados es variable global, puedo no pasarla por parametro.
	vector<int> VCopiaParentesisSeparados(parentesisSeparados.begin(), parentesisSeparados.end());
	int minElementIndex;
	int maxElementIndex = max_element(VCopiaParentesisSeparados.begin(), VCopiaParentesisSeparados.end()) - VCopiaParentesisSeparados.begin();

	if(parentesisSeparados.size() % 2 == 0){	//si es par
		for( unsigned i=0; i<parentesisSeparados.size(); i++){	//Bucle de 0 al tamaño del vector aunque siempre acabe en el break la ejecución.
			minElementIndex = min_element(VCopiaParentesisSeparados.begin(), VCopiaParentesisSeparados.end()) - VCopiaParentesisSeparados.begin();
			c.push_back(minElementIndex);
			VCopiaParentesisSeparados[minElementIndex] = VCopiaParentesisSeparados[maxElementIndex]+1;
			if(minElementIndex == maxElementIndex){	//Ya he ordenado todos los valores y he llegado al último
				break;
			}
		}
	}else{	//si es impar
		printf("SECUENCIA INCORRECTA, YA QUE EL NUMERO DE PARENTESIS NO PUEDE SER IMPAR\n");
	}
}

void SepararBasePairs(vector<string> &mIdeaParentesis, vector<string> &d){
	string el;

    for (string elemento : mIdeaParentesis) {
    	for (unsigned i=0; i<elemento.length(); ++i)
    	  {
    		el = elemento.at(i);	//Extraigo cada caracter del string y lo introduzco por separado en d
    	    d.push_back(el);
    	  }
    }
}

void getSecuenciaCompleta(vector<int> b, vector<int> c, vector<string> d, vector<string> mIdeaPuntos, string &ini_seq,vector<string> &ini_str_seq){
	int num;
	string base;
	vector<string>::iterator it1 = mIdeaPuntos.begin();

	for(unsigned i=0; i< c.size(); i++){
		it1 = mIdeaPuntos.begin() + b[i];
		num = c[i];
		base = d[num];
		mIdeaPuntos.insert(it1, base);
	}

	//Secuencia completa en un vector de strings
	ini_str_seq.insert(ini_str_seq.begin(), mIdeaPuntos.begin(), mIdeaPuntos.end());

	//Secuencia completa en un string
	for(const auto &str : ini_str_seq) {
		ini_seq += str;
	}
}








