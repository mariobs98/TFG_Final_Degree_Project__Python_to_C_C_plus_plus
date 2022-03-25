/*
 * MetodosDeCalculo.cpp
 *
 *  Created on: 10 ago 2021
 *      Author: mario
 */
#include "MetodosDeCalculo.h"



void UCTRNA(string &best_str, float &max_val, double &GCC){
	RNAestructura *state = new RNAestructura;

	cout<<"Search length:  "<< state->n <<endl;

	int aleatorio, k;
	vector<int> positions_ = state->GetPositions();
	aleatorio = sRNG.GetUint() % state->positionStructVector.size();
	k = positions_[aleatorio];

	MCTS(state, k, best_str, max_val, GCC);

	cout<<"Fin ejecucion MCTS - Soluciones: "<<endl;
	cout<<"best_str: "<<best_str<<endl;
	cout<<"GCC content: "<<GCC<<endl;
	cout<<"GCC distance(diferencia entre contenido GC propuesto y alcanzado): "<< abs(GCC-parametro_gc) <<endl;
	cout<<"max_val(Similitud): "<<max_val<<endl;

	delete state;
}

void UCTRNAnoGC(string &best_str, float &max_val, double &GCC){
	RNAestructura *state = new RNAestructura;
	int aleatorio, k;
	vector<int> positions_ = state->GetPositions();
	aleatorio = sRNG.GetUint() % state->positionStructVector.size();
	k = positions_[aleatorio];

	MCTSnoGC(state, k, best_str, max_val, GCC);

	cout<<"Fin ejecucion MCTSnoGC - Soluciones: "<<endl;
	cout<<"best_str: "<<best_str<<endl;
	cout<<"GCC content: "<<GCC<<endl;
	cout<<"GCC distance(diferencia entre contenido GC propuesto y alcanzado): "<< abs(GCC-parametro_gc) <<endl;
	cout<<"max_val(Similitud): "<<max_val<<endl;

	delete state;
}

void MCTS(RNAestructura *root, int k, string &best_str_solution, float &max_val_solution, double &GCC_solution){
    time_t tiempoActual = time(NULL);
    //time_t tiempoSalida= tiempoActual+(60*10);
    time_t tiempoSalida= tiempoActual+(600*10);
    cout<<endl;
    cout << "DENTRO DE MCTS" << endl;

	Nodo *rootNode = new Nodo(-1, -1, NULL, root), *Node, *Node2;
	RNAestructura *state = new RNAestructura();
	root->Clone(state);

	int aleatorio = -1;
	int new_count=0, need_GC=0, index_seq=0, contador=0, count_number=0, count_number1=0;
	//he cambiado de float a double
	double some_str_distance, new_str_distance, max_idx, GCnew, GCnum;
	double ggg=0, gggg=0;
	float some_str_mfe=0, notUsable;
	//double
	double re=0, max_val = 0;
	string some_str_value="", kkk, some_ini_seq, seq;
	vector<string> eposl;
	vector<string> eposl111;
	vector<int> y;
	vector<parParentesis> paired_pos;
	vector<parParentesis> dif_ini;

	bool puntoBool = false;
	bool parParentesis = false;

	while(tiempoActual <= tiempoSalida){
	//while(contador < MAX_IT){
		cout << endl;
	    tiempoActual = time(NULL);
		contador=contador+1;
	    cout << "EJECUCION DE MCTS NUMERO: "<< contador << endl;
	    cout << "Tiempo actual: "<< tiempoActual << " Tiempo salida: "<< tiempoSalida << endl;
		//cout << endl;

		Node = rootNode;
		root->Clone(state);
		count_number = 0;
		count_number1 = 0;

		re=0, max_val = 0;

		paired_pos.clear();
		vector<positionStruct> posi;
		vector<positionStruct> posl;
		vector<positionStruct> poslalpha;
		vector<positionStruct> need;
		vector<int> pa;
		vector<int> upa;

		while(Node->untriedUBPP.empty() || Node->untriedBPP.empty()){
			Node = Node->SeleccionarNodo();
			state->SelectPosition(Node->position, Node->pt);
		}

		if( !Node->untriedPositions.empty() ){
			if(k > (vectorPuntos.size()-1) ){
				if(Node->untriedBPP.size() == 6){
					aleatorio = sRNG.GetUint() % Node->untriedPositions.size();
					k = Node->untriedPositions[aleatorio];
				}
			}else{
				if(Node->untriedUBPP.size() == 4){
					aleatorio = sRNG.GetUint() % Node->untriedPositions.size();
					k = Node->untriedPositions[aleatorio];
				}
			}
			if(Node->untriedBPP.size() != 6 || Node->untriedUBPP.size() != 4){
				if(Node->NodoHijo != NULL){
					k = Node->NodoHijo->pt;
				}
			}
		}

		if(k > vectorPuntos.size()-1){
			if( !Node->untriedBPP.empty() ){
				aleatorio = sRNG.GetUint() % Node->untriedBPP.size();
				int m = Node->untriedBPP[aleatorio];
				Node->untriedBPP.erase(remove(Node->untriedBPP.begin(), Node->untriedBPP.end(), m), Node->untriedBPP.end());
				state->SelectPosition(m, k);
				Node2 = new Nodo(m,k,Node, state);
				Node->AnadirNodo(m, k, *Node2);
				Node = Node2;
			}
		}else{
			if( !Node->untriedUBPP.empty() ){
				aleatorio = sRNG.GetUint() % Node->untriedUBPP.size();
				int m = Node->untriedUBPP[aleatorio];
				Node->untriedUBPP.erase(remove(Node->untriedUBPP.begin(), Node->untriedUBPP.end(), m), Node->untriedUBPP.end());
				state->SelectPosition(m, k);
				Node2 = new Nodo(m,k,Node, state);
				Node->AnadirNodo(m, k, *Node2);
				Node = Node2;
			}
		}

		posi = state->positionStructVector;
		vector<positionStruct> goal = unirIndexYUindex();

		puntoBool = false;
		parParentesis = false;

		for(unsigned i=0; i<state->positionStructVector.size(); i++){
			if(esPunto(i, goal)){	//Si es != -1, es una posicion valida de punto. En la busqueda, goal[i] no valdrá -1 nunca.
				int id = goal[i].punto;
				auto pred = [id](const positionStruct & item) {
				    return item.punto == id;
				};
				 puntoBool = find_if(begin(posi), end(posi), pred) != end(posi);
				 if(!puntoBool){
					 posl.push_back(goal[i]);
				 }else{
					 need.push_back(goal[i]);
				 }
				 puntoBool=false;
			}else{
				if(esParParentesis(i, goal)){
					//Si no encuentro la apertura, no contraré su par de cierre. Solo compruebo apertura.
					int id = goal[i].apertura;
					auto pred = [id](const positionStruct & item) {
					    return item.apertura == id;
					};
					 parParentesis = find_if(begin(posi), end(posi), pred) != end(posi);
					 if(!parParentesis){
						 posl.push_back(goal[i]);
					 }else{
						 need.push_back(goal[i]);
					 }
					 parParentesis=false;
				}else{
					cout << "Fallo en MCTS, no es ni punto ni parParentesis" << endl;
				}
			}
			if(hayBase(i, posi)){
				poslalpha.push_back(posi[i]); //Meto la estructura que contiene una base, ergo "no estaria" en goal, al ser goal simplemente
											  //los enteros de las posiciones donde se encuentran los puntos y los pares de parentesis.
			}								//Con poslalpha solo quiero quedarme las bases
		}//for


		eposl.clear();
		eposl111.clear();
		if( poslalpha.size() <= vectorParentesis.size() ){
			//eposl- va a ser una lista de las bases
			for(auto elemento : poslalpha){
			    string s = elemento.base;
			    char arr[s.length()];
			    strcpy(arr,s.c_str());
			    for(unsigned i = 0; i < s.length(); i++){
			    	eposl.push_back(string(1,arr[i]));
			    }
			}
		}else{
			for(unsigned i = poslalpha.size()-vectorParentesis.size(); i<poslalpha.size(); i++){
			    string s = poslalpha[i].base;
			    char arr[s.length()];
			    strcpy(arr,s.c_str());
			    for(unsigned i = 0; i < s.length(); i++){
			    	eposl111.push_back(string(1,arr[i]));
			    }
			}

			//eposl1=list(itertools.chain(*eposl111)) esta linea en python seria eposl111, ya que ya es una lista con las bases

			for(unsigned i=0; i<(poslalpha.size()-vectorParentesis.size()); i++){
			    string s = poslalpha[i].base;
			    char arr[s.length()];
			    strcpy(arr,s.c_str());
			    for(unsigned i = 0; i < s.length(); i++){
			    	eposl.push_back(string(1,arr[i]));
			    }
			}
			//sumar eposl111 a eposl
			for(string elemento : eposl111){
				eposl.push_back(elemento);
			}
		}

		need_GC = calculate_GC_numbers(eposl, parametro_gc, need, poslalpha);
		y=state->GetPositions();
		//cout<<endl;
		//cout << "/////////////////////////// need_GC:  " << need_GC <<endl;

		for(unsigned i=0; i<y.size(); i++){
			if(y[i]>vectorPuntos.size()-1){
				pa.push_back(y[i]);
			}else{
				upa.push_back(y[i]);
			}
		}
		//cout << endl;
		while(!pa.empty()){
			aleatorio = sRNG.GetUint() % pa.size();
			int cpa = pa[aleatorio];

			if(count_number<=need_GC){
				state->SimulationGC(cpa);
				count_number = count_number+1;
				pa.erase(remove(pa.begin(), pa.end(), cpa), pa.end());
			}else{
				state->SimulationAU(cpa);
				pa.erase(remove(pa.begin(), pa.end(), cpa), pa.end());
			}
		}

		while(!upa.empty()){
			aleatorio = sRNG.GetUint() % upa.size();
			int ucpa = upa[aleatorio];

			if(count_number<=need_GC){
				new_count=need_GC-count_number;
				if(count_number1 <= (new_count*2)){
					state->SimulationUnpairedGC(ucpa);
					upa.erase(remove(upa.begin(), upa.end(), ucpa), upa.end());
					count_number1 = count_number1+1;
				}else{
					state->SimulationUnpairedAU(ucpa);
					upa.erase(remove(upa.begin(), upa.end(), ucpa), upa.end());
				}
			}else{
				state->SimulationUnpairedAU(ucpa);
				upa.erase(remove(upa.begin(), upa.end(), ucpa), upa.end());
			}
		}

		vector<positionStruct> posbasep;
		vector<positionStruct> posbase;

		for(int i=vectorPuntos.size(); i<state->n; i++){
			posbasep.push_back(state->positionStructVector[i]);
		}

		for(unsigned i=0; i<vectorPuntos.size(); i++){
			posbase.push_back(state->positionStructVector[i]);
		}
		//e=list(itertools.chain(*posbasep)) posbasep lo tengo ya como un vector, no hace falta transoformarlo a lista

	    vector<string> e;
	    for(positionStruct elemento : posbasep){
	    	for(unsigned i=0; i<elemento.base.size(); i++) {
	    		string str(1, elemento.base[i]);
	    		e.push_back(str);
	    	}
	    }

		//base en "e"(posbasep) en la posicion c[i], lo inserto en posbase en la posicion b[i]
		//Probado y corregido
		for(unsigned i=0; i<parentesisSeparados.size(); i++){
			auto it = posbase.begin() + b[i];
			positionStruct aux;
			aux.base = e[c[i]];
			posbase.insert(it, aux);
		}

		string mutated_s="";
		for(unsigned i=0; i<posbase.size(); i++){
			mutated_s = mutated_s + posbase[i].base;
		}
		//cout << " mutated_s: "  << mutated_s <<endl;
		vector<string> ini_seq_pool;
		vector<double> ini_str_pool;
		vector<double> GC_pool;
		index_seq=0;
		//TODO si introduzco corchetes, tengo que  escribir esta parte de codigo, si pk=1. De momento trabajo con pk=0
		if(parametro_pk == 1){

		}else{
			//cout<< "Mutated_s_1: "<<endl;// << mutated_s<<endl;
			calculate_mfe_and_str(mutated_s, some_str_mfe, some_str_value);
			some_str_distance=calculate_structure_distance(parametro_s, parametro_s.size(), some_str_value);
		}
		//cout<< "some_str_distance(Distancia): " << some_str_distance<<endl;
		ini_seq_pool.push_back(mutated_s);
		ini_str_pool.push_back(some_str_distance);
		GCnum=measureGC(mutated_s);
		GC_pool.push_back(GCnum);

		//cout<< "GCnum1: " << GCnum<<endl;
		//cout<<endl;

		//cout<<endl;
		//cout<< "//////////////////Bucle 50/////////////////////: "<<endl;
		//cout<<endl;
		for(int i=0; i<50; i++){
			//cout << "Ejecucion bucle: " << i << endl;

			paired_pos.clear();

			//devuelve paired_pos y dif_ini
			dif_str(some_str_value, paired_pos, dif_ini);
			//devuelve posbase cambiado(mutated_seq)
			GCcontent(parametro_gc, GCnum, paired_pos, posbase, posl);
			//devuelve posbase modificado
			check_GC_base3(dif_ini, posbase, posl);

			string mutated_seq="";
			for(positionStruct p : posbase){
				mutated_seq = mutated_seq+p.base;
			}
			GCnum = measureGC(mutated_seq);

			//cout<< "GCnum2: " << GCnum<<endl;

			GC_pool.push_back(GCnum);

			//TODO si introduzco corchetes, tengo que  escribir esta parte de codigo, si pk=1. De momento trabajo con pk=0
			if(parametro_pk == 1){

			}else{
				//kkk=some_str_value
				calculate_mfe_and_str(mutated_seq, notUsable, kkk);
				//TODO
				//cout<< "Mutated_seq2: " << mutated_seq<<endl;
				new_str_distance=calculate_structure_distance(parametro_s, parametro_s.size(), kkk);
			}
			some_str_value=kkk;
			some_ini_seq=mutated_seq;
			ini_seq_pool.push_back(mutated_seq);
			ini_str_pool.push_back(new_str_distance);
			index_seq = index_seq+1;
			ggg=abs(parametro_gc-GCnum);

			//cout<< "new_str_distance(Distancia)2: " << new_str_distance<<endl;
			//cout<< "ggg2: " << ggg<<endl;
			//cout<<endl;

			if(ini_str_pool[index_seq] == 1){
				break;
			}
		}
		//cout<<endl;
		//cout<< "//////////////////FIN DE BUCLE/////////////////////: "<<endl;
		//cout<<endl;

		int maxElementIndex = std::max_element(ini_str_pool.begin(),ini_str_pool.end()) - ini_str_pool.begin();

		GCnew=GC_pool[maxElementIndex];
		max_val=ini_str_pool[maxElementIndex];
		seq=ini_seq_pool[index_seq];
		ggg=abs(parametro_gc-GCnum);
		gggg=abs(parametro_gc-GCnew);

		best_str_solution=seq;
		max_val_solution=max_val;
		GCC_solution=GCnum;

		//cout<< "ggg3: " << ggg<<endl;
		//cout<< "gggg3: " << gggg<<endl;
		//cout<< "SEQ_MEJOR DEL BUCLE: " << seq <<endl;
		//cout<< "MAX_VAL_MEJOR DEL BUCLE: " << max_val_solution <<endl;
		//cout<< "GCNUM_MEJOR DEL BUCLE: " << GCC_solution <<endl;
		//cout<<endl;

		if((ini_str_pool[index_seq] == 1) && (ggg<=parametro_d)){
			break;
		}

		if(ini_str_pool[index_seq] == 1){
			if(ggg<=0.01){
				re=1+1;
			}else{
				re=1+0;
			}
		}

		if(max_val<1){
			if(gggg<=0.01){
				re=1+max_val;
			}else{
				re=0+max_val;
			}
		}

		bool salir = false;
		int j=0;
		//si nodopadre es null, estoy en el ultimo nodo(osea, el primero del arbol)
		while(!salir){
			if(Node->NodoPadre == NULL){
				salir = true;
			}
		    j++;
		    //cout << "---------WHILE--------- "<< j << endl;
			Node->ActualizarNodo(re);
			//cout << "%% Position : " << Node->position<<endl;
			//cout << "%% Pt : " << Node->pt<<endl;
			//cout << "%% Victorias : " << Node->victorias<<endl;
			//cout << "%% Visitas : " << Node->visitas<<endl;
			Node = Node->NodoPadre;
		}

	}//primer while - tiempo

	//delete rootNode;
	//delete Node;
	//delete Node2;

	//devolver seq, max_val y GCnum
}//MCTS()

void MCTSnoGC(RNAestructura *root, int k, string &best_str_solution, float &max_val_solution, double &GCC_solution){
    time_t tiempoActual = time(NULL);
    time_t tiempoSalida= tiempoActual+(60*10);

    //Numero de iteraciones del bucle principal
    int itermax = 100000;

    cout << "DENTRO DE MCTSnoGC" << endl;

	Nodo *rootNode = new Nodo(-1, -1, NULL, root), *Node, *Node2;
	RNAestructura *state = new RNAestructura();
	root->Clone(state);

	int aleatorio = -1;

	vector<string> eposl;
	vector<string> eposl111;
	vector<int> y;
	vector<parParentesis> paired_pos;
	vector<parParentesis> dif_ini;

	int index_seq=0, contador=1;
	string some_str_value="", kkk, some_ini_seq, seq;
	double some_str_distance, re, new_str_distance, max_idx, GCnew, max_val, GCnum, GCnum2;
	float notUsable;
	bool puntoBool = false;
	bool parParentesis = false;

	for(int z=0; z<itermax; z++){
		cout << endl;
	    tiempoActual = time(NULL);
	    cout << "EJECUCION DE MCTS_NO_GC NUMERO: "<< contador << endl;
	    cout << "Tiempo actual: "<< tiempoActual << " Tiempo salida: "<< tiempoSalida << endl;
		contador=contador+1;

		if(tiempoActual >= tiempoSalida){
			break;
		}

		Node = rootNode;
		root->Clone(state);
		vector<positionStruct> posi;
		vector<positionStruct> posl;

		while(Node->untriedUBPP.empty() || Node->untriedBPP.empty()){
			Node = Node->SeleccionarNodo();
			state->SelectPosition(Node->position, Node->pt);
		}

		/*if(contador == 2){ //en la primera ejecucion
			cout << "k contador"<<endl;
			//k = vectorPuntos.size() + 1;
		}*/
		//cout << "k contador"<< k <<endl;

		if( !Node->untriedPositions.empty() ){
			if(k > (vectorPuntos.size()-1) ){
				if(Node->untriedBPP.size() == 6){
					aleatorio = sRNG.GetUint() % Node->untriedPositions.size();
					k = Node->untriedPositions[aleatorio];
				}
			}else{
				if(Node->untriedUBPP.size() == 4){
					aleatorio = sRNG.GetUint() % Node->untriedPositions.size();
					k = Node->untriedPositions[aleatorio];
				}
			}
		}

		if(k > vectorPuntos.size()-1){
			if( !Node->untriedBPP.empty() ){
				aleatorio = sRNG.GetUint() % Node->untriedBPP.size();
				int m = Node->untriedBPP[aleatorio];
				Node->untriedBPP.erase(remove(Node->untriedBPP.begin(), Node->untriedBPP.end(), m), Node->untriedBPP.end());
				state->SelectPosition(m, k);
				Node2 = new Nodo(m,k,Node, state);
				Node->AnadirNodo(m, k, *Node2);
				Node = Node2;
			}
		}else{
			if( !Node->untriedUBPP.empty() ){
				aleatorio = sRNG.GetUint() % Node->untriedUBPP.size();
				int m = Node->untriedUBPP[aleatorio];
				Node->untriedUBPP.erase(remove(Node->untriedUBPP.begin(), Node->untriedUBPP.end(), m), Node->untriedUBPP.end());
				state->SelectPosition(m, k);
				Node2 = new Nodo(m,k,Node, state);
				Node->AnadirNodo(m, k, *Node2);
				Node = Node2;
			}
		}

		posi = state->positionStructVector;
		vector<positionStruct> goal = unirIndexYUindex();

		puntoBool = false;
		parParentesis = false;

		for(unsigned i=0; i<state->positionStructVector.size(); i++){

			if(esPunto(i, goal)){
				int id = goal[i].punto;
				auto pred = [id](const positionStruct & item) {
				    return item.punto == id;
				};
				 puntoBool = find_if(begin(posi), end(posi), pred) != end(posi);
				 if(!puntoBool){
					 posl.push_back(goal[i]);
				 }
				 puntoBool=false;
			}else{
				if(esParParentesis(i, goal)){
					//Si no encuentro la apertura, no contraré su par de cierre. Solo compruebo apertura.
					int id = goal[i].apertura;
					auto pred = [id](const positionStruct & item) {
					    return item.apertura == id;
					};
					 parParentesis = find_if(begin(posi), end(posi), pred) != end(posi);
					 if(!parParentesis){
						 posl.push_back(goal[i]);
					 }
					 parParentesis=false;
				}else{
					cout << "Fallo en MCTS, no es ni punto ni parParentesis" << endl;
				}
			}
		}//for

		while (!state->GetPositions().empty()){
			aleatorio = sRNG.GetUint() % state->GetPositions().size();
			//cout << "seleccion while: "<< state->GetPositions()[aleatorio]<<endl;
			state->Simulation(state->GetPositions()[aleatorio]);
		}

		vector<positionStruct> posbasep;
		vector<positionStruct> posbase;

		for(unsigned i=vectorPuntos.size(); i<state->n; i++){
			posbasep.push_back(state->positionStructVector[i]);
		}

		for(unsigned i=0; i<vectorPuntos.size(); i++){
			posbase.push_back(state->positionStructVector[i]);
		}
		//e=list(itertools.chain(*posbasep)) posbasep lo tengo ya como un vector, no hace falta transoformarlo a lista

	    vector<string> e;
	    for(positionStruct elemento : posbasep){
	    	for(unsigned i=0; i<elemento.base.size(); i++) {
	    		string str(1, elemento.base[i]);
	    		e.push_back(str);
	    	}
	    }

		//base en "e"(posbasep) en la posicion c[i], lo inserto en posbase en la posicion b[i]
		//Probado y corregido
		for(unsigned i=0; i<parentesisSeparados.size(); i++){
			auto it = posbase.begin() + b[i];
			positionStruct aux;
			aux.base = e[c[i]];
			posbase.insert(it, aux);
		}

		string mutated_s="";
		for(unsigned i=0; i<posbase.size(); i++){
			mutated_s = mutated_s + posbase[i].base;
		}
		//cout << " mutated_s: "  << mutated_s <<endl;
		vector<string> ini_seq_pool;
		vector<double> ini_str_pool;
		vector<double> GC_pool;
		index_seq=0;
		//TODO si introduzco corchetes, tengo que  escribir esta parte de codigo, si pk=1. De momento trabajo con pk=0
		if(parametro_pk == 1){

		}else{
			float notUsable;
			calculate_mfe_and_str(mutated_s, notUsable, kkk);
		}

		some_str_value = kkk;
		some_str_distance=calculate_structure_distance(parametro_s, parametro_s.size(), some_str_value);
		//cout << " some_str_distance: "  << some_str_distance <<endl;
		ini_seq_pool.push_back(mutated_s);
		ini_str_pool.push_back(some_str_distance);
		GCnum=measureGC(mutated_s);
		//cout << " GCnum: "  << GCnum <<endl;
		GC_pool.push_back(GCnum);

		//cout<<endl;
		//cout<< "//////////////////Bucle 50/////////////////////: "<<endl;
		//cout<<endl;

		for(int i=0; i<50; i++){
			//cout << "Ejecucion bucle: " << i << endl;

			paired_pos.clear();

			//devuelve paired_pos y dif_ini
			dif_str(some_str_value, paired_pos, dif_ini);
			//devuelve posbase cambiado(mutated_seq)
			check_seq_base(parametro_gc, GCnum, paired_pos, posbase, posl);
			//devuelve posbase modificado
			check_GC_base(dif_ini, posbase, posl);

			string mutated_seq="";
			for(positionStruct p : posbase){
				mutated_seq = mutated_seq+p.base;
			}
			GCnum2 = measureGC(mutated_seq);
			//cout << " GCnum2: "  << GCnum2 <<endl;
			GC_pool.push_back(GCnum2);

			//TODO si introduzco corchetes, tengo que  escribir esta parte de codigo, si pk=1. De momento trabajo con pk=0
			if(parametro_pk == 1){

			}else{
				calculate_mfe_and_str(mutated_seq, notUsable, kkk);
			}
			new_str_distance=calculate_structure_distance(parametro_s, parametro_s.size(), kkk);
			//cout << " new_str_distance: "  << new_str_distance <<endl;
			some_str_value=kkk;
			some_ini_seq=mutated_seq;
			ini_seq_pool.push_back(mutated_seq);
			ini_str_pool.push_back(new_str_distance);
			index_seq = index_seq+1;
			if(ini_str_pool[index_seq] == 1){
				break;
			}
			//cout<<endl;
		}//for <50

		//cout<<endl;
		//cout<< "//////////////////FIN DE BUCLE/////////////////////: "<<endl;
		//cout<<endl;

		int maxElementIndex = std::max_element(ini_str_pool.begin(),ini_str_pool.end()) - ini_str_pool.begin();

		GCnew=GC_pool[maxElementIndex];
		max_val=ini_str_pool[maxElementIndex];
		seq=ini_seq_pool[index_seq];

		best_str_solution=seq;
		max_val_solution=max_val;
		GCC_solution=GCnew;

		if(ini_str_pool[index_seq] == 1){
			break;
		}

		if(max_val<1){
			re=max_val;
		}

		bool salir = false;
		int j=0;
		//si nodopadre es null, estoy en el ultimo nodo(osea, el primero del arbol)
		while(!salir){
			if(Node->NodoPadre == NULL){
				salir = true;
			}
		    j++;
		    //cout << "---------WHILE--------- "<< j << endl;
			Node->ActualizarNodo(re);
			//cout << "%% Position : " << Node->position<<endl;
			//cout << "%% Pt : " << Node->pt<<endl;
			//cout << "%% Victorias : " << Node->victorias<<endl;
			//cout << "%% Visitas : " << Node->visitas<<endl;
			Node = Node->NodoPadre;
		}

	}//primer while - tiempo

	//delete rootNode;

	//devolver seq, max_val y GCnum
}

int calculate_GC_numbers(vector<string> eposl, float parametro_gc, vector<positionStruct> need, vector<positionStruct> poslalpha){
	int cunnt=0;
	int real = 0;
	for(unsigned i=0; i<eposl.size(); i++){
		if(eposl[i]=="G" || eposl[i]=="C"){
			cunnt=cunnt+1;
		}
	}//for

	int needGC = (parametro_s.size()*parametro_gc) - cunnt;

	if(needGC > 0){
		real = ceil((float)needGC/2);
	}else{
		real = 0;
	}
	return real;
}

void calculate_mfe_and_str(string sequence, float &mfe, string &str_v){

    char seq[sequence.size()];
    strcpy(seq,sequence.c_str());

    /* allocate memory for MFE structure (length + 1) */
    char  *structure = (char *)vrna_alloc(sizeof(char) * (strlen(seq) + 1));

    /* predict Minmum Free Energy and corresponding secondary structure */
    mfe = vrna_fold(seq, structure);
    string copia(structure);
    str_v = copia;

    /* print sequence, structure and MFE */
    //todo
    //cout<<"sequence(mutated_s): "<< sequence <<" MFE(some_str_mfe): "<<mfe<<" str_v(structure)(some_str_value): "<<str_v<<endl;

    /* cleanup memory */
    free(structure);
}

//structure_s = parametro_s ---Secuencia original
double calculate_structure_distance(string structure_s, float str_length, string some_str_value){
	double sdt=0;
	int sd=0;

	//Todo
	//cout << "Original: " << structure_s<< endl;
	//cout << "Prueba:   " << some_str_value<< endl;

	for(unsigned i=0; i<structure_s.size(); i++){
		if(some_str_value[i]!=structure_s[i]){
			sd=sd+1;
		}
	}

	sdt=(str_length-(double)sd)/str_length;

	return sdt;
}

double measureGC(string generate_seq){
	int n=generate_seq.size();
	int cont=0;
	vector<int> indexGC;
	vector<int> indexnotGC;
	double getGC=0;

	for(unsigned i=0; i<generate_seq.size(); i++){
		if(generate_seq[i]=='C'){
			cont=cont+1;
			indexGC.push_back(i);
		}
		if(generate_seq[i]=='G'){
			cont=cont+1;
			indexGC.push_back(i);
		}
		if(generate_seq[i]!='C' && generate_seq[i]!='G'){
			indexnotGC.push_back(i);
		}
	}
	getGC=(double)cont/n;
	return getGC;
}


void dif_str(string &some_str_value, vector<parParentesis> &save_paired_pos, vector<parParentesis> &dif_pos_ini){
	vector<parParentesis> paired;
	vector<int> unpaired;
	bool seEncuentra = false;

	calculate_sequence_position(some_str_value, paired, unpaired);

	for(unsigned i=0; i<paired.size(); i++){
		for(parParentesis par : vectorParentesis){
			if( (par.apertura == paired[i].apertura) && (par.cierre == paired[i].cierre)){
				seEncuentra = true;
				break;
			}
		}
		if(!seEncuentra){
			save_paired_pos.push_back(paired[i]);
		}else{
			seEncuentra = false;
		}
	}

	dif_pos_ini.clear();

	seEncuentra = false;
	for(unsigned i=0; i<vectorParentesis.size(); i++){
		for(parParentesis par : paired){
			if( (par.apertura == vectorParentesis[i].apertura) && (par.cierre == vectorParentesis[i].cierre)){
				seEncuentra = true;
				break;
			}
		}
		if(!seEncuentra){
			dif_pos_ini.push_back(vectorParentesis[i]);
		}else{
			seEncuentra = false;
		}
	}
}

void calculate_sequence_position(string &seq, vector<parParentesis> &struc, vector<int> &ustruc){
	vector<int> stack;
	int ultimo;
	parParentesis par;

	for(unsigned i=0; i<seq.size(); i++){
		if(seq[i] == '('){ stack.push_back(i);}
		if(seq[i] == ')'){
			ultimo = stack.back();
			par.apertura = ultimo;
			stack.pop_back();
			par.cierre = i;
			struc.push_back(par);
		}else if(seq[i] == '.'){ ustruc.push_back(i); }
	}
}

void GCcontent(float parametro_gc, double getGC, vector<parParentesis> &some_paired_pos, vector<positionStruct> &predicted_seq, vector<positionStruct> &posl){
	vector<string> check_even;
	vector<string> check_odd;
	vector<string> A_change = {"G", "C"};
	vector<string> C_change = {"A", "U"};
	vector<string> U_change = {"U", "C"};
	vector<string> G_change = {"A", "G"};
	vector<int> parentesisSeparados;
	vector<int> Par;
	vector<int> imPar;
	vector<int> nuevo_Par;
	vector<int> nuevo_imPar;
	bool seEncuentraPar = false;
	bool seEncuentraImpar = false;
	int aleatorio;

	SepararParentesis(some_paired_pos, parentesisSeparados);

	//Coger pares e impares
	for(unsigned i=0; i<parentesisSeparados.size(); i++){
		if (i%2 == 0){
			Par.push_back(parentesisSeparados[i]);
	    }else{
			imPar.push_back(parentesisSeparados[i]);
	    }
	}

	if(!posl.empty()){

	for(unsigned i=0; i<Par.size(); i++){

		for(unsigned j=0; j<posl.size(); j++){
			if(Par[i] == posl[j].punto){
				seEncuentraPar = true;
			}
			if(imPar[i] == posl[j].punto){
				seEncuentraImpar = true;
			}
		}

		if(!seEncuentraPar){
			nuevo_Par.push_back(Par[i]);
			nuevo_imPar.push_back(imPar[i]);
		}else{
			seEncuentraPar = false;
		}
		if(!seEncuentraImpar){
			nuevo_Par.push_back(Par[i]);
			nuevo_imPar.push_back(imPar[i]);
		}else{
			seEncuentraImpar = false;
		}
	}//for len(par)
	}//posl.empty

	for(unsigned i=0; i<nuevo_imPar.size(); i++){
		check_even.push_back(predicted_seq[nuevo_Par[i]].base);
		check_odd.push_back(predicted_seq[nuevo_imPar[i]].base);
	}

	for (unsigned i = 0; i < nuevo_imPar.size(); i++) {
		if (getGC < parametro_gc) {
			if (predicted_seq[nuevo_imPar[i]].base == "A") {
				aleatorio = sRNG.GetUint() % A_change.size();
				predicted_seq[nuevo_Par[i]].base = A_change[aleatorio];
			} else if (predicted_seq[nuevo_imPar[i]].base == "U") {
				predicted_seq[nuevo_Par[i]].base = "C";
			} else if (predicted_seq[nuevo_imPar[i]].base == "C") {
				predicted_seq[nuevo_Par[i]].base = "C";
			} else if (predicted_seq[nuevo_imPar[i]].base == "G") {
				predicted_seq[nuevo_Par[i]].base = "G";
			}
		} else {
			if (predicted_seq[nuevo_imPar[i]].base == "A") {
				predicted_seq[nuevo_Par[i]].base = "A";
			} else if (predicted_seq[nuevo_imPar[i]].base == "U") {
				predicted_seq[nuevo_Par[i]].base = "U";
			} else if (predicted_seq[nuevo_imPar[i]].base == "C") {
				aleatorio = sRNG.GetUint() % C_change.size();
				predicted_seq[nuevo_Par[i]].base = C_change[aleatorio];
			} else if (predicted_seq[nuevo_imPar[i]].base == "G") {
				predicted_seq[nuevo_Par[i]].base = "A";
			}
		}
	}
}

void check_seq_base(float parametro_gc, double getGC, vector<parParentesis> &some_paired_pos, vector<positionStruct> &predicted_seq, vector<positionStruct> &posl){
	vector<string> check_even;
	vector<string> check_odd;
	vector<string> A_change = {"G", "C"};
	vector<string> C_change = {"A", "U"};
	vector<string> U_change = {"U", "C"};
	vector<string> G_change = {"A", "G"};
	vector<int> parentesisSeparados;
	vector<int> Par;
	vector<int> imPar;
	vector<int> nuevo_Par;
	vector<int> nuevo_imPar;
	bool seEncuentraPar = false;
	bool seEncuentraImpar = false;
	int aleatorio;

	SepararParentesis(some_paired_pos, parentesisSeparados);

	//Coger pares e impares
	for(unsigned i=0; i<parentesisSeparados.size(); i++){
	    if (i%2 == 0){
			Par.push_back(parentesisSeparados[i]);
	    }else{
			imPar.push_back(parentesisSeparados[i]);
	    }
	}

	/*for(unsigned i=0; i<Par.size(); i++){
		if(!posl.empty()){
		//if even
		int id = posl[i].punto;
		auto pred = [id](const int & item) {
		    return item == id;
		};
		seEncuentraPar = find_if(begin(Par), end(Par), pred) != end(Par);
		 if(!seEncuentraPar){
				nuevo_Par.push_back(Par[i]);
				nuevo_imPar.push_back(imPar[i]);
		 }else{
				seEncuentraPar = false;
		 }

		//if odd
		int id2 = posl[i].punto;
		auto pred2 = [id2](const int & item) {
		    return item == id2;
		};
		seEncuentraImpar = find_if(begin(imPar), end(imPar), pred2) != end(imPar);
		 if(!seEncuentraImpar){
				nuevo_Par.push_back(Par[i]);
				nuevo_imPar.push_back(imPar[i]);
		 }else{
			 seEncuentraImpar = false;
		 }
		}//posl.empty
	}*/

	if(!posl.empty()){

	for(unsigned i=0; i<Par.size(); i++){

		for(unsigned j=0; j<posl.size(); j++){
			if(Par[i] == posl[j].punto){
				seEncuentraPar = true;
			}
			if(imPar[i] == posl[j].punto){
				seEncuentraImpar = true;
			}
		}

		if(!seEncuentraPar){
			nuevo_Par.push_back(Par[i]);
			nuevo_imPar.push_back(imPar[i]);
		}else{
			seEncuentraPar = false;
		}
		if(!seEncuentraImpar){
			nuevo_Par.push_back(Par[i]);
			nuevo_imPar.push_back(imPar[i]);
		}else{
			seEncuentraImpar = false;
		}
	}//for len(par)
	}//posl.empty


	for(unsigned i=0; i<nuevo_imPar.size(); i++){
		check_even.push_back(predicted_seq[nuevo_Par[i]].base);
		check_odd.push_back(predicted_seq[nuevo_imPar[i]].base);
	}

	for (unsigned i = 0; i < nuevo_imPar.size(); i++) {
		if (getGC < parametro_gc) {
			if (predicted_seq[nuevo_imPar[i]].base == "A") {
				aleatorio = sRNG.GetUint() % A_change.size();
				predicted_seq[nuevo_Par[i]].base = A_change[aleatorio];

			} else if (predicted_seq[nuevo_imPar[i]].base == "U") {
				aleatorio = sRNG.GetUint() % U_change.size();
				predicted_seq[nuevo_Par[i]].base = U_change[aleatorio];

			} else if (predicted_seq[nuevo_imPar[i]].base == "C") {
				aleatorio = sRNG.GetUint() % C_change.size();
				predicted_seq[nuevo_Par[i]].base = C_change[aleatorio];

			} else if (predicted_seq[nuevo_imPar[i]].base == "G") {
				aleatorio = sRNG.GetUint() % G_change.size();
				predicted_seq[nuevo_Par[i]].base = G_change[aleatorio];
			}
		}
	}

}


void check_GC_base3(vector<parParentesis> &some_dif_ini,vector<positionStruct> &predicted_seq, vector<positionStruct> &posl){
	vector<string> GC = {"G", "C"};
	vector<string> AU = {"A", "U"};

	string aux="";
	for(positionStruct p : predicted_seq){
		aux = aux+p.base;
	}
	double newGC = measureGC(aux);
	vector<parParentesis> new_dif_ini;
	bool parParentesis = false;
	vector<int> parentesisSeparados_;//a1
	vector<int> Par;
	vector<int> imPar;
	int aleatorio;

	for(unsigned i=0; i<some_dif_ini.size(); i++){
		//Si no encuentro la apertura, no contraré su par de cierre. Solo compruebo apertura.
		int id = some_dif_ini[i].apertura;
		auto pred = [id](const positionStruct & item) {
		    return item.apertura == id;
		};
		 parParentesis = find_if(begin(posl), end(posl), pred) != end(posl);
		 if(!parParentesis){
			 new_dif_ini.push_back(some_dif_ini[i]);
		 }
	}

	SepararParentesis(new_dif_ini, parentesisSeparados_);

	//Coger pares e impares
	for(unsigned i=0; i<parentesisSeparados_.size(); i++){
	    if (i%2 == 0){
			Par.push_back(parentesisSeparados_[i]);
	    }else{
			imPar.push_back(parentesisSeparados_[i]);
	    }
	}

	for (unsigned i = 0; i < imPar.size(); i++) {
		if (parametro_gc>=newGC) {
			aleatorio = sRNG.GetUint() % GC.size();
			predicted_seq[imPar[i]].base = GC[aleatorio];
			if (predicted_seq[imPar[i]].base == "G") {
				predicted_seq[Par[i]].base = "C";
			} else if (predicted_seq[imPar[i]].base == "C") {
				predicted_seq[Par[i]].base = "G";
			}
		} else {
			aleatorio = sRNG.GetUint() % AU.size();
			predicted_seq[imPar[i]].base = AU[aleatorio];
			if (predicted_seq[imPar[i]].base == "A") {
				predicted_seq[Par[i]].base = "U";
			} else if (predicted_seq[imPar[i]].base == "U") {
				predicted_seq[Par[i]].base = "A";
			}
		}
	}

}

void check_GC_base(vector<parParentesis> &some_dif_ini,vector<positionStruct> &predicted_seq, vector<positionStruct> &posl){
	vector<string> GC = {"G", "C"};

	vector<parParentesis> new_dif_ini;
	bool parParentesis = false;
	vector<int> parentesisSeparados;//a1
	vector<int> Par;
	vector<int> imPar;
	int aleatorio;

	for(unsigned i=0; i<some_dif_ini.size(); i++){
		//Si no encuentro la apertura, no contraré su par de cierre. Solo compruebo apertura.
		int id = some_dif_ini[i].apertura;
		auto pred = [id](const positionStruct & item) {
		    return item.apertura == id;
		};
		 parParentesis = find_if(begin(posl), end(posl), pred) != end(posl);
		 if(!parParentesis){
			 new_dif_ini.push_back(some_dif_ini[i]);
		 }
	}
	SepararParentesis(new_dif_ini, parentesisSeparados);
	//Coger pares e impares
	for(unsigned i=0; i<parentesisSeparados.size(); i++){
	    if (i%2 == 0){
			Par.push_back(parentesisSeparados[i]);
	    }else{
			imPar.push_back(parentesisSeparados[i]);
	    }
	}

	for (unsigned i = 0; i < imPar.size(); i++) {
			aleatorio = sRNG.GetUint() % GC.size();
			predicted_seq[imPar[i]].base = GC[aleatorio];
			if (predicted_seq[imPar[i]].base == "G") {
				predicted_seq[Par[i]].base = "C";
			} else if (predicted_seq[imPar[i]].base == "C") {
				predicted_seq[Par[i]].base = "G";
			}
	}
}


vector<positionStruct> unirIndexYUindex(){
	positionStruct posStruct;
	vector<positionStruct> Union;

    for (parParentesis par : vectorParentesis) {
        posStruct.apertura = par.apertura;
        posStruct.cierre = par.cierre;
		Union.push_back(posStruct);

        posStruct.apertura = -1;
        posStruct.cierre = -1;
    }

	for(unsigned i=0; i<vectorPuntos.size(); i++){
		posStruct.punto = vectorPuntos[i];
		Union.push_back(posStruct);

		posStruct.punto = -1;
	}

    return Union;
}

bool esPunto(int numPosition, vector<positionStruct> vector){
	if(vector[numPosition].punto != -1){
		return true;
	}
	return false;
}

bool esParParentesis(int numPosition, vector<positionStruct> vector){
	if( (vector[numPosition].apertura != -1) && (vector[numPosition].cierre != -1) ){
		return true;
	}
	return false;
}

bool hayBase(int numPosition, vector<positionStruct> vector){
	if(vector[numPosition].base != ""){
		return true;
	}
	return false;
}






