//**************************************************************************
// Práctica 5
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B5.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, TRIPODE} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;
bool animando=false;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

int estadoRaton[3], xc, yc, mode[5], cambio=0, tipo_camara = 0;

int Ancho=450, Alto=450;
float factor=1.0;

void pick_color(int x, int y);

// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply;
_rotacion rotacion;
_tanque tanque;
_tripode tripode;

// _objeto_ply *ply1;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
//glMatrixMode(GL_PROJECTION);
//glLoadIdentity();
// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
//glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
/*if(modo_camara==1)
  glViewport(0,0,Ancho,Alto);
if(modo_camara==2)
  glViewport()*/

	if (tipo_camara==0 )
	  glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
	if (tipo_camara==1 )
		glOrtho(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
	//glScalef(factor,factor,1);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);

}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case ARTICULADO: tanque.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);break;
				case TRIPODE: tripode.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);break;
	}

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
	case '5': tipo_camara = 0; break;
	case '6': tipo_camara = 1; break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;
        case 'R':t_objeto=ROTACION;break;
        case 'A':t_objeto=ARTICULADO;break;
				case 'F':t_objeto=TRIPODE;break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
        case GLUT_KEY_F1:tanque.giro_tubo+=1;
                         if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_max;
                         break;
        case GLUT_KEY_F2:tanque.giro_tubo-=1;
                         if (tanque.giro_tubo<tanque.giro_tubo_min) tanque.giro_tubo=tanque.giro_tubo_min;
                         break;break;
        case GLUT_KEY_F3:tanque.giro_torreta+=5;tripode.alfa+=5; break;
        case GLUT_KEY_F4:tanque.giro_torreta-=5;tripode.alfa-=5; break;
        case GLUT_KEY_F5:if(tripode.zoom < tripode.MAX_zoom )tripode.zoom+=0.1; tripode.beta+=5;break;
				case GLUT_KEY_F6:if(tripode.zoom > tripode.MIN_zoom )tripode.zoom-=0.1; tripode.beta-=5;break;
				case GLUT_KEY_F7:animando = !animando;break;
				case GLUT_KEY_F8:tripode.altura_pata+=0.1;
                         if (tripode.altura_pata>tripode.altura_pata_max) tripode.altura_pata=tripode.altura_pata_max;break;
				case GLUT_KEY_F9:tripode.altura_pata-=0.1;
                         if (tripode.altura_pata<tripode.altura_pata_min) tripode.altura_pata=tripode.altura_pata_min;break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funciones para uso de buffer trasero
//***************************************************************************
/*void draw_objects_seleccion(){
    // Se muestran las caras solo por el lado frontal.
    glEnable(GL_CULL_FACE);

    // Para dibujar los objetos en el modo selección, las componentes r2, g2 y
    // b2 son irrelevantes, al igual que g1 y b1, pues solo se utilizarán tres
    // componentes r, g, b, de las cuales g y b se determinan por la cara a
    // dibujar. Así, solo queda la componente r, que será única para los objetos
    // simples, y se incrementará para cada objeto del modelo jerárquico, por lo
    // que nos sirve un valor que deje espacio para el número de objetos de
    // nuestro modelo jerárquico.
    switch(t_objeto){
				case CUBO: cubo.draw(COLOR_SELECTION, material, 100, 0, 0, 0, 0, 0, 2); break;
				case PIRAMIDE: piramide.draw(COLOR_SELECTION, material, 100, 0, 0, 0, 0, 0, 2); break;
			  case OBJETO_PLY: ply.draw(COLOR_SELECTION, material, 100, 0, 0, 0, 0, 0, 2); break;
			  case ROTACION: rotacion.draw(COLOR_SELECTION, material, 100, 0, 0, 0, 0, 0, 2); break;
			  case ARTICULADO: tanque.draw(COLOR_SELECTION, material, 100, 0, 0, 0, 0, 0, 2); break;
				case TRIPODE: tripode.draw(COLOR_SELECTION, material, 100, 0, 0, 0, 0, 0, 2); break;
	}
}*/

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     }
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      //pick_color(xc, yc);
    }
  }

	if(boton == 3){
        if(estado == GLUT_DOWN){
            Observer_distance /= 1.2;
						glutPostRedisplay();
        }
    }

    if(boton == 4){
        if(estado == GLUT_DOWN){
            Observer_distance *= 1.2;
						glutPostRedisplay();
        }
    }
}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}

/*************************************************************************/

void RatonMovido( int x, int y )
{
float x0, y0, xn, yn;
if(estadoRaton[2]==1)
    {getCamara(&x0,&y0);
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}

//***************************************************************************
// Funciones para la seleccion
//************************************************************************
/*

void procesar_color(unsigned char color[3])
{
	cout << "Color pinchado: (" << (int) color[0] << ", " << (int) color[1] <<
             ", " << (int) color[2] << ")" << endl;

     if(selec_cara){
         int num_cara = color[1] * 255 + color[2];

         switch(t_objeto){
             case PIRAMIDE:      if(color[0] == 100 && num_cara < piramide.caras_selec.size()){
                                     piramide.caras_selec[num_cara] = !piramide.caras_selec[num_cara];
                                 }
                                 break;
             case CUBO:          if(color[0] == 100 && num_cara < cubo.caras_selec.size()){
                                     cubo.caras_selec[num_cara] = !cubo.caras_selec[num_cara];
                                 }
                                 break;
             case CONO:          if(color[0] == 100 && num_cara < cono.caras_selec.size()){
                                     cono.caras_selec[num_cara] = !cono.caras_selec[num_cara];
                                 }
                                 break;
             case CILINDRO:      if(color[0] == 100 && num_cara < cilindro.caras_selec.size()){
                                     cilindro.caras_selec[num_cara] = !cilindro.caras_selec[num_cara];
                                 }
                                 break;
             case ESFERA:        if(color[0] == 100 && num_cara < esfera.caras_selec.size()){
                                     esfera.caras_selec[num_cara] = !esfera.caras_selec[num_cara];
                                 }
                                 break;
             case OBJETO_PLY:    if(color[0] == 100 && num_cara < ply.caras_selec.size()){
                                     ply.caras_selec[num_cara] = !ply.caras_selec[num_cara];
                                 }
                                 break;
             case ARTICULADO:    if(100 <= color[0] && color[0] <= 124){
                                     robot.robot_caras_selec[color[0] % 100][num_cara] =
                                     !robot.robot_caras_selec[color[0] % 100][num_cara];
                                 }
                                 break;
 	    }
     }
     else{
         switch(t_objeto){
             case PIRAMIDE:      if(color[0] == 100){
                                     piramide.seleccionado = !piramide.seleccionado;
                                 }
                                 break;
             case CUBO:          if(color[0] == 100){
                                     cubo.seleccionado = !cubo.seleccionado;
                                 }
                                 break;
             case CONO:          if(color[0] == 100){
                                     cono.seleccionado = !cono.seleccionado;
                                 }
                                 break;
             case CILINDRO:      if(color[0] == 100){
                                     cilindro.seleccionado = !cilindro.seleccionado;
                                 }
                                 break;
             case ESFERA:        if(color[0] == 100){
                                     esfera.seleccionado = !esfera.seleccionado;
                                 }
                                 break;
             case OBJETO_PLY:    if(color[0] == 100){
                                     ply.seleccionado = !ply.seleccionado;
                                 }
                                 break;
             case ARTICULADO:    if(100 <= color[0] && color[0] < 109){
                                     robot.objeto_selec[0] = !robot.objeto_selec[0];
                                 }
                                 else if(109 <= color[0] && color[0] < 113){
                                     robot.objeto_selec[1] = !robot.objeto_selec[1];
                                 }
                                 else if(113 <= color[0] && color[0] < 117){
                                     robot.objeto_selec[2] = !robot.objeto_selec[2];
                                 }
                                 else if(117 <= color[0] && color[0] < 121){
                                     robot.objeto_selec[3] = !robot.objeto_selec[3];
                                 }
                                 else if(121 <= color[0] && color[0] < 123){
                                     robot.objeto_selec[4] = !robot.objeto_selec[4];
                                 }
                                 else if(123 <= color[0] && color[0] < 125){
                                     robot.objeto_selec[5] = !robot.objeto_selec[5];
                                 }
                                 break;
         }
     }
 }



void pick_color(int x, int y)
{
/*GLint viewport[4];
unsigned char pixel[3];

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
glutPostRedisplay();*/

	/*	GLuint selectBuf[100]={0};
		GLint viewport[4], hits=0;
		// Declarar buffer de selección
		glSelectBuffer(100, selectBuf);
		// Obtener los parámetros del viewport
		glGetIntegerv (GL_VIEWPORT, viewport);
		// Pasar OpenGL a modo selección
		glRenderMode (GL_SELECT);
		glInitNames();
		glPushName(0);
		// Fijar la transformación de proyección para la selección
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluPickMatrix (x,(viewport[3] - y),5.0, 5.0, viewport);
		glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
		// Dibujar la escena
		draw();
		// Pasar OpenGL a modo render
		hits = glRenderMode (GL_RENDER);
		// Restablecer la transformación de proyección
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
		// Procesar el contenido del buffer de selección
		procesar_color(hits, selectBuf);
		// Dibujar la escena para actualizar cambios
		draw();
}*/

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);

}

//***************************************************************************
// Funcion de animación
//***************************************************************************

bool creciendo = true;
void animacion(){
	if(animando){
		if((tripode.zoom < tripode.MAX_zoom) && creciendo){
			tripode.zoom += 0.01;
			tripode.beta+=0.5;
			if (tripode.zoom >= tripode.MAX_zoom){
				tripode.zoom = tripode.MAX_zoom;
				creciendo = false;
			}
		}
		if((tripode.zoom > tripode.MIN_zoom) && !creciendo){
			tripode.zoom -= 0.01;
			tripode.beta-=0.5;
			if (tripode.zoom <= tripode.MIN_zoom){
				tripode.zoom = tripode.MIN_zoom;
				creciendo = true;
			}
		}
		glutPostRedisplay();
	}
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv)
{
// creación del objeto ply
ply.parametros(argv[1]);


// perfil
vector<_vertex3f> perfil2;
_vertex3f aux;
aux.x=1.0;aux.y=-1.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=-1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=-0.7;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=-0.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=0.5;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.8;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.55;aux.y=1.0;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=1.2;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=1.4;aux.z=0.0;
perfil2.push_back(aux);
rotacion.parametros(perfil2,6,1);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

//funcion de la animacion
glutIdleFunc(animacion);

//eventos de raton
glutMouseFunc(clickRaton);
glutMotionFunc(RatonMovido);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
