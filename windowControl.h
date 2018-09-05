#define KEY_ESC 27
Camara CAMARA(850,850);

//Controlar la escena con el teclado
void keyPress(int key,int x,int y){
	if(key==KEY_ESC){//salir
		exit(0);
	} 
	CAMARA.transform=true;
	if(key==(int)'+'){//zoom in
		CAMARA.zoom(2);
	} else if(key==(int)'-'){//zoom out
		CAMARA.zoom(.5);
	} else if(key==GLUT_KEY_RIGHT){//mover derecha
		CAMARA.move(-15*1/CAMARA.rotate,0);
	} else if(key==GLUT_KEY_LEFT){//mover izquierda
		CAMARA.move(15*1/CAMARA.rotate,0);
	} else if(key==GLUT_KEY_UP){//mover arriba
		CAMARA.move(0,-15*1/CAMARA.rotate);
	} else if(key==GLUT_KEY_DOWN){//mover abajo
		CAMARA.move(0,15*1/CAMARA.rotate);
	} else {
		CAMARA.transform=false;
	}
	if(CAMARA.transform)
		glutPostRedisplay();
}

//Redimencionar escena de acuerdo a el tamaño de la ventana
void reshapeScene(GLint width, GLint height){
	CAMARA.transform=true;
	if (height < width){
		double w = (double)height;
		double left = (width - w) / 2;
		glViewport(left, 0, w, height);
	} else {
		double h=(double)width;
		double floor = (height-h)/2;
		glViewport(0,floor,width,h);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-CAMARA.WIDTH/2,CAMARA.WIDTH/2,-CAMARA.HEIGHT/2,CAMARA.HEIGHT/2);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}
