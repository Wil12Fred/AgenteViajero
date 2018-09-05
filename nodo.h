/***
* Nodo Básico
***/

struct Nodo{
	int ID;
	Punto punto;//coordenada
	map<int,Nodo*> aristas;//nodos vecinos
	//int obstaculos=0;
	Nodo (Punto B,int id=0){
		ID=id;
		punto=B;
	}
	bool operator <(const Nodo B)const{
		return punto<B.punto;
	}
	bool insertarArista(Nodo* B){
		if(B==NULL){
			return false;
		}
		auto it = aristas.find(B->ID);
		if(it==aristas.end()){
			aristas[B->ID]=B;
			return true;
		}
		return false;
	}
};
