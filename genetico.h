#include "represent.h"

struct Individuo{
	Represent representacion;
	double aptitud;
	Individuo(){
	}
	Individuo(Represent rep){
		representacion=rep;
	}
	Individuo(Represent representacion,double aptitud){
		representacion=representacion;
		aptitud=aptitud;
	}
	Individuo operator=(const Individuo& B){
		representacion=B.representacion;
		aptitud=B.aptitud;
		return *(this);
	}
	bool operator ==(const Individuo B)const{
		return (representacion==B.representacion);
	}
	Individuo cruzamiento(const Individuo* B){
		int inicio=XorShift(representacion.tamano()-2);//
		int fin=inicio+XorShift((int)representacion.tamano()-inicio);//
		Represent nuevo(representacion.tamano());//
		set<int> cromosomas;//
		for (int i=inicio;i<=fin;i++){
			cromosomas.insert(representacion.ciudades[i]);//
		}
		int indice=0;
		for (int i=0;i<B->representacion.tamano();i++){
			if(!(indice>=inicio && indice<=fin)){
				if(cromosomas.find(B->representacion.ciudades[i])==cromosomas.end()){
					nuevo.ciudades[indice++]=B->representacion.ciudades[i];
				}
			} else {
				nuevo.ciudades[indice]=representacion.ciudades[indice];
				indice++;
			}
		}
		return Individuo(nuevo);
	}
	Individuo mutacion(){
		int findice_mutacion=XorShift(representacion.tamano());//
		int sindice_mutacion=XorShift(representacion.tamano()-1);//
		if(findice_mutacion==sindice_mutacion){
			sindice_mutacion=(sindice_mutacion+1)%representacion.tamano();
		}
		Represent nuevo=representacion;
		int ciudad_aleatoria=nuevo.ciudades[sindice_mutacion];
		nuevo.ciudades[sindice_mutacion]=nuevo.ciudades[findice_mutacion];
		nuevo.ciudades[findice_mutacion]=ciudad_aleatoria;
		return Individuo(nuevo);
	}
	bool operator <(const Individuo& B)const{
		return (aptitud==B.aptitud)?representacion<B.representacion:aptitud<B.aptitud;
	}
};

struct Problema{
	Grafo* grafo;
	int tamano_de_poblacion;
	int numero_de_generaciones;
	double distancia_total;
	Problema (Grafo* grafo, int tdp,int ndg){
		grafo= grafo;
		tamano_de_poblacion=tdp;
		numero_de_generaciones=ndg;
		distancia_total=0;
		for (auto fit=grafo->nodos.begin();fit!=grafo->nodos.end();fit++){
			for (auto sit=grafo->nodos.begin();sit!=grafo->nodos.end();sit++){
				distancia_total+=((fit->second)->punto-(sit->second)->punto).norm();
			}
		}
		distancia_total/=2;
	}
	void generar_nuevo_individuo(Individuo& B){
		Represent nuevo(grafo->nodos.size());
		set<int> cromosomas;
		for (int i=0;i<grafo->nodos.size();i++){
			cromosomas.insert(i);
		}
		int indice=0;
		while(indice<grafo->nodos.size()){
			auto it=cromosomas.lower_bound(XorShift(grafo->nodos.size()));
			if(it==cromosomas.end()){
				it=cromosomas.begin();
			}
			nuevo.ciudades[indice++]=*it;
			cromosomas.erase(it);
		}
		B.representacion=nuevo;
	}
	int valor_aleatorio(int max){
		return XorShift(max);
	}
	double valor_aleatorio(double max){
		long long aleatorio = XorShift(100000000);
		return (max*aleatorio)/double(100000000);
	}
	double aptitud(Individuo& individuo){
		double distancia;
		return distancia*(double)100/distancia_total;
	}
};

struct Genetico{
	set<Individuo>* poblacion;
	Problema* problema; 
	double probabilidad_de_cruzamiento;
	double probabilidad_de_mutacion;
	double aptitud_total;
	Genetico(Problema* p,double c, double m){
		aptitud_total=0;
		poblacion = new set<Individuo>();
		problema=p;
		probabilidad_de_cruzamiento=c;
		probabilidad_de_mutacion=m;
		crear_poblacion();
	}
	void crear_poblacion(){
		while(poblacion->size()<problema->tamano_de_poblacion){
			Individuo nuevo_individuo;
			problema->generar_nuevo_individuo(nuevo_individuo);
			nuevo_individuo.aptitud=problema->aptitud(nuevo_individuo);
			aptitud_total+=nuevo_individuo.aptitud;
			poblacion->insert(nuevo_individuo);
		}
	}
	bool seleccion_rueda_de_ruleta(double aptitud){
		double ruleta = problema->valor_aleatorio(aptitud_total);
		return ruleta<aptitud;
	}
	void seleccion_de_individuos(map<int,Individuo*>& individuos_a_cruzar){
		int i=0;
		for (auto it=poblacion->begin();it!=poblacion->end();it++){
			if(seleccion_rueda_de_ruleta(it->aptitud)){
				individuos_a_cruzar[i++]=new Individuo(*it);
			}
		}
	}
	Individuo* seleccionar_padre(map<int,Individuo*>& individuos_a_cruzar){
		int aleatorio=problema->valor_aleatorio((int)individuos_a_cruzar.size());
		auto it=individuos_a_cruzar.lower_bound(aleatorio);
		if(it==individuos_a_cruzar.end()){
			it=individuos_a_cruzar.lower_bound(0);
		}
		Individuo* padre = it->second;
		individuos_a_cruzar.erase(it);
		return padre;
	}
	void cruzar_individuos(){
		map<int,Individuo*> individuos_a_cruzar;
		seleccion_de_individuos(individuos_a_cruzar);
		while (individuos_a_cruzar.size()>1){
			Individuo* padre = seleccionar_padre(individuos_a_cruzar);
			Individuo hijo=padre->cruzamiento(seleccionar_padre(individuos_a_cruzar));//implementar cruzamiento
			hijo.aptitud=problema->aptitud(hijo);
			aptitud_total+=hijo.aptitud;
			poblacion->insert(hijo);
		}
	}
	void ajustar_poblacion(){
		while(poblacion->size()>problema->tamano_de_poblacion){
			aptitud_total-=(poblacion->begin())->aptitud;
			poblacion->erase(poblacion->begin());
		}
	}
	void mutar_individuos(){
		for(auto it=poblacion->begin();it!=poblacion->end();it++){
			double aleatorio=problema->valor_aleatorio(double(1));
			if(aleatorio<probabilidad_de_mutacion){
				Individuo mutacion=Individuo(*it).mutacion();
				mutacion.aptitud=problema->aptitud(mutacion);
				poblacion->insert(mutacion);//implementar mutación
			}
		}
	}
	void generar_nueva_poblacion(){
		cruzar_individuos();
		mutar_individuos();
		ajustar_poblacion();
	}
	Individuo iniciar(){
		for (int i=0;i<problema->numero_de_generaciones;i++){
			generar_nueva_poblacion();
		}
		return *(poblacion->rbegin());
	}
};
