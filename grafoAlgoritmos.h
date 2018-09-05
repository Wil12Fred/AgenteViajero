void generarPuntos(set<Punto>& P,int n){
	while(P.size()<n){
		double x=XorShift((long long)CAMARA.WIDTH);
		double y=XorShift((long long)CAMARA.HEIGHT);
		P.insert(Punto(x,y));
	}
}

void caminoEuleriano(Grafo* G, vector<pair<int,int> >& Camino){
	Problema problema(G,10,200);
	Genetico genetico(&problema,0.7,0.02);
	Individuo mejor=genetico.iniciar();
	vector<int> Orden=mejor.representacion.ciudades;
	for (int i=0;i<Orden.size()-1;i++){
		Camino.push_back(make_pair(Orden[i],Orden[i+1]));
	}
	Camino.push_back(make_pair(Orden[Orden.size()-1],Orden[0]));
}

void crearGrafo(int n, Grafo& G){
	set<Punto> P;
	generarPuntos(P,n);
	vector<Punto> V;
	for (auto it=P.begin();it!=P.end();it++){
		V.push_back(Punto(it->x-CAMARA.WIDTH/2,it->y-CAMARA.HEIGHT/2));
		G.insertarNodo(Punto(it->x-CAMARA.WIDTH/2,it->y-CAMARA.HEIGHT/2));
	}
}
