/*
 * CodigoPruebas.cpp
 *
 *  Created on: 3 nov 2021
 *      Author: mario
 */







//PRUEBAS__#########-----------------------------------------------------------@@@@@@@@@@@@@@@_PRUEBAS_@@@@@@@@@@@@@@@@@@-------------------------------------------------------############

/*
    vector<float> prueba;
    for(int i=0; i<100; i++){
    	prueba.push_back(i/1.1);
    }
    prueba[6] = 207.69;
	float max_idx = *max_element(prueba.begin(), prueba.end());

	cout << "elemento mayor " << max_idx;

*/

/*
	cout.precision(15);
	int z = 0.948717948718;
    cout<< "int: " << z << endl;
	float x = 0.948717948718;
    cout<< "float: " << x << endl;
	double c = 0.948717948718;
    cout<< "double: " << c << endl;
	long double b = 0.948717948718;
    cout<< "long float: " << b << endl;
*/


    /*
    RNAestructura *strc = new RNAestructura();
    Nodo *nodo1 = new Nodo(99, 99, NULL, strc);
    Nodo *nod;

    for(int i=0; i<5; i++){
        nod = new Nodo(i,i,nodo1, strc);
    	nodo1->AnadirNodo(i, i, *nod);
    	nod->victorias = i;
    	nod->visitas = i;
    	cout<< nod->victorias<<" "<< nod->pt<<" "<<endl;
    	//cout<< nodo1->NodosHijos[i].victorias << " "<< nodo1->pt<<endl;
    	//nodo1->NodoHijo->victorias=50;
    	//nodo1->NodoHijo->visitas=i;
    }



	//cout << nodo1->NodosHijos.size() << " ";
	//cout<< nodo1->NodosHijos[2].victorias<<endl;
	//cout<<"fffffffffffffffffffffffff "<< endl;
    /*
    for(Nodo n : nodo1->NodosHijos){
    	cout << n.victorias << " "<<endl;
    }cout<<endl;
    */
/*
    nod = nodo1->NodosHijos[1];
    nod->victorias = 50;
    nod = nod->NodoPadre;
    nod->victorias = 32;
/*
	cout<<"direccion nodo1 "<< &nodo1<<endl;
    for (int i=0; i<nodo1->NodosHijos.size(); i++){
    	//int position = nodo1->NodosHijos[i].position;
    	//cout << i << "  " << endl;
    	cout<< nodo1->NodosHijos[i]->victorias<<endl;
    	cout<< &nodo1->NodosHijos[i]<<endl;
    	cout<< &nodo1->NodosHijos[i]->NodoPadre<<endl;
    }
*/



    /*
	cout<<"nodo1 pt -------- "<< nodo1->pt<< endl;
	if(nodo1->NodoPadre == NULL){
		cout<<"nodo1 NULL "<< endl;
		//cout<<"nodo1 pt nodopadre "<< nodo1->NodoPadre->pt<< endl;
	}else{
		cout<<"nodo1 NOT NULL "<< endl;
	}
	cout<<" direccion de memoria nodo1 "<< &nodo1<< endl;
	cout<<" direccion de memoria nodo1 padre "<< &nodo1->NodoPadre<< endl;

	if(nodo1->NodoPadre == NULL){
	cout<<"nodopadre es null "<< endl;
	}

	Nodo *nodo2=new Nodo();
    *nodo2 = nodo1->AnadirNodo(1, 1, strc);
	cout<<"nodo2 -------- "<< nodo2->pt<< endl;
	if(nodo2->NodoPadre == NULL){
		cout<<"nodo2 NULL "<< endl;
	}else{
		cout<<"nodo2 NOT NULL "<< endl;
		cout<<"nodo2 pt nodopadre "<< nodo2->NodoPadre->pt<< endl;
	}
	cout<<" direccion de memoria nodo2 "<< &nodo2<< endl;
	cout<<" direccion de memoria nodo2 padre "<< &nodo2->NodoPadre<< endl;
	//cout<<" nodo2 pt padre nodopadre "<< nodo2->NodoPadre->NodoPadre->pt<< endl;

	nodo1 = nodo2;
	cout<<"nodo1 pt -------- "<< nodo1->pt<< endl;
	if(nodo1->NodoPadre == NULL){
		cout<<"nodo1 NULL "<< endl;
		//cout<<"nodo1 pt nodopadre "<< nodo1->NodoPadre->pt<< endl;
	}else{
		cout<<"nodo1 NOT NULL "<< endl;
	}
	cout<<" direccion de memoria nodo1 "<< &nodo1<< endl;
	cout<<" direccion de memoria nodo1 padre "<< &nodo1->NodoPadre<< endl;

	if(nodo1->NodoPadre == NULL){
	cout<<"nodopadre es null "<< endl;
	}
*/
    //*nodo1 = nodo1->AnadirNodo(2, 2, strc);
    //*nodo1 = nodo1->AnadirNodo(3, 3, strc);
/*
    for (int i=0; i<nodo1->NodosHijos.size(); i++){
    	//int position = nodo1->NodosHijos[i].position;
    	cout << i << "  " << endl;
    	cout<< nodo1->NodosHijos[i].victorias;
    }

*/

/*
string basura="0123456789";
string out(1, basura[2]);

cout<<"el string: -> " << out;
*/

//    /* The RNA sequence */
//    //char  *seq = "GAGUAGUGGAACCAGGCUAUGUUUGUGACUCGCAGACUAACA";
//
/*    string seqS = "GAGUAGUGGAACCAGGCUAUGUUUGUGACUCGCAGACUAACA";
    char seq[seqS.size()];
    strcpy(seq,seqS.c_str());*/
//
//    /* allocate memory for MFE structure (length + 1) */
//    char  *structure = (char *)vrna_alloc(sizeof(char) * (strlen(seq) + 1));
//
//    /* predict Minmum Free Energy and corresponding secondary structure */
//    float mfe = vrna_fold(seq, structure);
//
//    /* print sequence, structure and MFE */
//    printf("%s\n%s [ %6.2f ]\n", seq, structure, mfe);
//
//    string strin(structure);
//    cout<<strin;
//
//    /* cleanup memory */
//    free(structure);

    /*
    float mfe;
    string secuencia;
    calculate_mfe_and_str(seq, mfe, secuencia);
    cout<<"MFE : "<<mfe<<" str_v(structure): "<<secuencia<<endl;
	*/

    //RNAestructura *rna = new RNAestructura
	//MCTS(*rna, 5);


	//RNAestructura *state = new RNAestructura;

	//state->positionStructVector[1].base="A";
	//state->positionStructVector[1].punto=-1;
	//state->MostrarPositionStructVector();
/*
	std::vector<positionStruct> posi = state->positionStructVector;
	std::vector<positionStruct> goal = unirIndexYUindex();

	printf("GOAL_STRUCT_VECTOR:  ");
    for (positionStruct p : goal) {
        cout << p.punto << "/" << p.apertura << "/" << p.cierre << "/" << p.base << "  ";
    }
	cout << endl;

	printf("POSI_STRUCT_VECTOR:  ");
    for (positionStruct p : posi) {
        cout << p.punto << "/" << p.apertura << "/" << p.cierre << "/" << p.base << "  ";
    }
	cout << endl;

	bool puntoBool = false;
	bool parParentesis = false;

	if(!hayBase(2, goal)){

	if(esParParentesis(1, goal)){

	int id = goal[1].apertura;
	//cout << id << endl;
	auto pred = [id](const positionStruct & item) {
	    return item.apertura == id;
	};
	 puntoBool = std::find_if(std::begin(posi), std::end(posi), pred) != std::end(posi);
	 cout << puntoBool << endl;

	}else{
		cout << "esPunto" << endl;
	}

	}//if
*/
	 /*
	for(unsigned i=0; i<state->positionStructVector.size(); i++){

		int id = goal[i].punto;
		//cout << id << endl;
		auto pred = [id](const positionStruct & item) {
		    return item.punto == id;
		};
		 puntoBool = std::find_if(std::begin(posi), std::end(posi), pred) != std::end(posi);
		//puntoBool = std::find(posi.begin(), posi.end(), goal[i].punto) != posi.end();
		 cout << puntoBool << endl;
		 puntoBool = false;
	}*/

	/*
	if(state->hayBase(1)){
		cout<< " base encontrada "<< state->positionStructVector[1].base <<endl;
	}else{
		cout<< " base NO encontrada "<< state->positionStructVector[1].base << " <-deberia haber base "<<endl;
	}*/
	/*
	if(state->esPunto(2)){
		cout<< " punto encontrada "<< state->positionStructVector[2].punto <<endl;
	}else{
		cout<< " punto NO encontrada "<< state->positionStructVector[2].punto << " <-deberia haber -1 "<<endl;
	}
	*/
/*
	std::vector<int> vector = state->GetPositions();

	cout<< state->n << endl;
	cout<< " getpositions "<< endl;
	for(int elemento : vector){
		cout<< elemento << " ";
	}
*/

/*
    Nodo *nodo1 = new Nodo();
    Nodo *nodo2 = new Nodo(2, 2, nodo1, *state);
    Nodo *nodo3 = new Nodo(3, 3, nodo1, *state);
    Nodo *nodo4 = new Nodo(4, 4, nodo3, *state);

    //Nodo *nodo2 = nodo1->AnadirNodo(2, 2, *state);
    //Nodo *nodo3 = nodo1->AnadirNodo(3, 3, *state);
    //Nodo *nodo4 = nodo1->AnadirNodo(4, 4, *state);
    nodo1->NodosHijos.push_back(*nodo2);
    nodo1->NodosHijos.push_back(*nodo3);
    nodo1->NodosHijos.push_back(*nodo4);

/*    cout << nodo2->NodoPadre->position << "  " << endl;

    if(nodo1->NodoHijo != NULL){
    	cout << "entramos if" << endl;
    cout << nodo1->NodoHijo->position << "  " << endl;
    }
*/
//	printf("Nodos hijos nodo 1: ");cout << endl;
/*
    nodo2->victorias=50;
    nodo3->victorias=120;
    nodo4->victorias=65;
    Nodo node = nodo1->SeleccionarNodo();
	cout<< "peto aqui12";
	//cout<< node.victorias;
/*
    for (int i=0; i<node.NodosHijos.size(); i++){
    	//int position = nodo1->NodosHijos[i].position;
    	//cout << position << "  " << endl;
    	cout<< node.NodosHijos[i].victorias;
    }

/*
	printf("Nodos hijos nodo 3: ");cout << endl;
    for (int i=0; i<nodo3->NodosHijos.size(); i++){
    	int position = nodo3->NodosHijos[i].position;
    	cout << position << "  " << endl;
    }
*/
/*
    nodo1->RNA.n= 32;
	cout << nodo1->RNA.n << "  " << endl;
    nodo3->RNA.n= 44;
	cout << nodo3->RNA.n << "  " << endl;
*/

    /*
	std::vector<positionStruct> result;
	result = unirIndexYUindex();
	cout<< " unirIndexYUindex "<< endl;
    for (positionStruct p : result) {
        cout << p.punto << "/" << p.apertura << "/" << p.cierre << "/" << p.base << "  ";
    }
	cout << endl;
	*/

/*
    time_t ahora = time(NULL);

    printf ("Tiempo UNIX: %ld\n", ahora);

    ahora=ahora/100000;
    printf ("Tiempo UNIX: %ld\n", ahora);


    printf ("Tiempo humano: %s\n", ctime(&ahora));

    struct tm* ahoralocal = localtime(&ahora);

    printf ("Tiempo humano: %02d/%02d/%d %02d:%02d:%02d\n", ahoralocal->tm_mday,
        ahoralocal->tm_mon +1,    // Sumamos 1 al mes porque va desde 0 a 11
        ahoralocal->tm_year+1900,
        ahoralocal->tm_hour,
        ahoralocal->tm_min,
        ahoralocal->tm_sec);*/









