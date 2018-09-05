/**
* Camara básica en 2 dimensiones
**/
struct Camara{
	bool opcionHeuristica=false;
	double WIDTH = 850;
	double HEIGHT = 850;
	double rotate = 1;
	Punto CENTER;
	bool transform=true;
	Camara(){};
	Camara(double w,double h){
		WIDTH=w;
		HEIGHT=h;
	}
	double ASPECT(){
		return WIDTH/HEIGHT;
	}
	void zoom(double Scale){
		rotate*=Scale;
		transform=true;
	}
	void move(double inX,double inY){
		CENTER+=Punto(inX,inY);
	}
};
