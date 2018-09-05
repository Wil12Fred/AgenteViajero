#include "nodo.h"

/***
* Grafo Básico (no dirigido)
***/

struct Grafo{
	int size=0;
	map <Punto,int> IDs;
	map<int,Nodo*>nodos;
	//set< pair<int,int> > Obstaculos;
	Grafo(){}
	Nodo* insertarNodo(Punto B){
		auto it = IDs.find(B);
		if(it!=IDs.end()){
			return nodos[it->second];
		}
		Nodo* nuevoNodo=new Nodo(B,size++);
		IDs[B]=size-1;
		nodos[size-1]=nuevoNodo;
		return nuevoNodo;
	}
	/*int aristasNodo(Punto A){
		if (IDs.find(A)==IDs.end()){
			return 0;
		}
		return nodos[IDs[A]]->aristas.size()-nodos[IDs[A]]->obstaculos;
	}*/
	bool insertarArista(Punto A,Punto B,bool obstaculo=0){
		Nodo* pNodo=insertarNodo(A);
		Nodo* sNodo=insertarNodo(B);
		/*if(obstaculo){
			Obstaculos.insert(make_pair(pNodo->ID,sNodo->ID));
			Obstaculos.insert(make_pair(sNodo->ID,pNodo->ID));
			nodos[IDs[A]]->obstaculos++;
			nodos[IDs[B]]->obstaculos++;
		}*/
		return ((*pNodo).insertarArista(sNodo) && (*sNodo).insertarArista(pNodo));
	}
};

