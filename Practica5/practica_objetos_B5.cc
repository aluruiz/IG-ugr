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

int estadoRaton[3], xc, yc, mode[5], cambio=0;
int tipo_camara = 0;
bool vista_multiple = false;
bool tipo_seleccion = true;

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
void projection_alzado(){
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0,Alto/2,Ancho/2,Alto/2);

  if (tipo_camara) { // Proyección en perspectiva con un punto de fuga
    glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
  }
  else {
    glOrtho(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
    glScalef(factor,factor,1);
  }
}

void projection_planta(){
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0,0,Ancho/2,Alto/2);

  glOrtho(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
  glRotatef(90,1,0,0);  // para verlo desde arriba
  glScalef(factor,1.0,factor);
}

void projection_perfil(){
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(Ancho/2,Alto/2,Ancho/2,Alto/2);

  // Cámara
  glOrtho(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
  glRotatef(90,0,1,0);
  glScalef(1.0,factor,factor);
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

void draw_objects(){
	switch (t_objeto){
		case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,1000);break;
		case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,1000);break;
	  case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2,1000);break;
	  case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,1000);break;
	  case ARTICULADO: tanque.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2,1000);break;
		case TRIPODE: tripode.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2,1000);break;
		}
}

void change_projection()
{
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
	//  plano_delantero>0  plano_trasero>PlanoDelantero)
	glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);*/
	glMatrixMode(GL_PROJECTION);

    if(tipo_camara== 0){
        //glLoadIdentity();
        glViewport(0, 0, Window_width, Window_high);
        //glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
				glMatrixMode(GL_MODELVIEW);
            draw_axis();
            draw_objects();
        glMatrixMode(GL_PROJECTION);
    }

    else if(tipo_camara == 1){
        glLoadIdentity();
        glViewport(0, 0, Window_width, Window_high);
        glOrtho(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
				glMatrixMode(GL_MODELVIEW);
            draw_axis();
            draw_objects();

        glMatrixMode(GL_PROJECTION);
    }

    else{
        // Alzado
        glLoadIdentity();
        glViewport(0, Window_high / 2, Window_width / 2, Window_high / 2);
        glOrtho(-Size_x * Observer_distance, Size_x * Observer_distance,
                -Size_y * Observer_distance, Size_y * Observer_distance,
                Front_plane, Back_plane);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glRotatef(-Observer_angle_y, 0, 1, 0);
        glRotatef(-Observer_angle_x, 1, 0, 0);
        glRotatef(Observer_angle_y, 0, 1, 0);
            draw_axis();
            draw_objects();
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);

        // Perfil
        glLoadIdentity();
        glViewport(Window_width / 2, Window_high / 2, Window_width / 2, Window_high / 2);
        glOrtho(-Size_x * Observer_distance, Size_x * Observer_distance,
                -Size_y * Observer_distance, Size_y * Observer_distance,
                Front_plane, Back_plane);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glRotatef(-Observer_angle_y, 0, 1, 0);
        glRotatef(-Observer_angle_x, 1, 0, 0);
        glRotatef(Observer_angle_y + 90, 0, 1, 0);
            draw_axis();
            draw_objects();
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);

        // Planta
        glLoadIdentity();
        glViewport(0, 0, Window_width / 2, Window_high / 2);
        glOrtho(-Size_x * Observer_distance, Size_x * Observer_distance,
                -Size_y * Observer_distance, Size_y * Observer_distance,
                Front_plane, Back_plane);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glRotatef(-Observer_angle_y, 0, 1, 0);
        glRotatef(-Observer_angle_x + 90, 1, 0, 0);
        glRotatef(Observer_angle_y, 0, 1, 0);
            draw_axis();
            draw_objects();
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);

        // Proyección en perspectiva
        glLoadIdentity();
        glViewport(Window_width / 2, 0, Window_width / 2, Window_high / 2);
        glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
				glMatrixMode(GL_MODELVIEW);
        draw_axis();
        draw_objects();

        glMatrixMode(GL_PROJECTION);
    }
    glMatrixMode(GL_MODELVIEW);
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

	change_projection();
}

void observer_alzado(){
	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance); // Hace el zoom
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

void observer_planta(){
	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,-Observer_distance,0); // Hace el zoom
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

void observer_perfil(){
	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(-Observer_distance,0,0); // Hace el zoom
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}

/*//**************************************************************************
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

void draw_objects(){
	switch (t_objeto){
		case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,1000);break;
		case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,1000);break;
	  case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2,1000);break;
	  case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,1000);break;
	  case ARTICULADO: tanque.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2,1000);break;
		case TRIPODE: tripode.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2,1000);break;
		}
}*/

//**************************************************************************
//
//***************************************************************************
void scene(void){
	glDrawBuffer(GL_FRONT);
  clean_window();

  // Alzado
  projection_alzado();
  observer_alzado();
  draw_axis();
  draw_objects();

  // Planta
  projection_planta();
  observer_planta();
  draw_axis();
  draw_objects();

  // Perfil
  projection_perfil();
  observer_perfil();
	draw_axis();
  draw_objects();

	glFlush();
}

void draw(void){
	clean_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
	/*clean_window();

	if (tipo_camara == 0){
		change_observer();

	} else if (tipo_camara == 1) {
		glOrtho(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
		glScalef(factor,factor,1);

	} else if (tipo_camara == 2) {
		scene();
	}
	draw_axis();
	draw_objects();
	glutSwapBuffers();*/

	/*glDrawBuffer(GL_FRONT);
    clean_window();
    change_observer();
    glutSwapBuffers();

		glDrawBuffer(GL_BACK);
    clean_window();
    change_observer();
    glutSwapBuffers();*/
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
	case '6': vista_multiple = !vista_multiple; break;
	case '7': tipo_seleccion = !tipo_seleccion; break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;
        case 'R':t_objeto=ROTACION;break;
        case 'A':t_objeto=ARTICULADO;break;
				case 'F':t_objeto=TRIPODE;break;
				case 'N': tipo_camara = 0; break;
				case 'V': tipo_camara = 1; break;
				case 'B': tipo_camara = 2; break;
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
      pick_color(xc, yc);
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

void procesar_hits(GLint hits, GLuint *names)
{

	// mostrar contenido de la pila
	printf("%d hits:\n", hits);
	for (int i = 0; i < hits; i++)
		printf("Número: %d\n Min Z: %d\n Max Z: %d\n Nombre en la pila: %d\n",
			(GLubyte)names[i * 4],
			(GLubyte)names[i * 4 + 1],
			(GLubyte)names[i * 4 + 2],
			(GLubyte)names[i * 4 + 3]);
	printf("\n");

	if(tipo_seleccion){
		switch (names[3]) {
			case 1: tripode.pata.seleccionado[0] = !tripode.pata.seleccionado[0]; break;
			case 2: tripode.pata.seleccionado[1] = !tripode.pata.seleccionado[1]; break;
			case 3: tripode.pata.seleccionado[2] = !tripode.pata.seleccionado[2]; break;
			case 4: tripode.cabeza.seleccionado = !tripode.cabeza.seleccionado; break;
			case 5: tripode.camara.seleccionado = !tripode.camara.seleccionado;break;
		}
	} else {
		if((names[3]>=100)&&(names[3]<200)){
 		 	tripode.camara.armazon.vec_tri[names[3]-100] = !tripode.camara.armazon.vec_tri[names[3]-100];
		} else if((names[3]>=200)&&(names[3]<300)){
 		 	tripode.camara.click.vec_tri[names[3]-200] = !tripode.camara.click.vec_tri[names[3]-200];
		} else if((names[3]>=300)&&(names[3]<400)) {
	 		 tripode.camara.objetivo.vec_tri[names[3]-300] = !tripode.camara.objetivo.vec_tri[names[3]-300];
	 	 } else if((names[3]>=400)&&(names[3]<500)) {
	 		 tripode.cabeza.base.vec_tri[names[3]-400] = !tripode.cabeza.base.vec_tri[names[3]-400];
	 	 } else if((names[3]>=500)&&(names[3]<600)){
 		 	tripode.cabeza.base.vec_tri[names[3]-500] = !tripode.cabeza.base.vec_tri[names[3]-500];
	 	 } else if((names[3]>=600)&&(names[3]<700)){
 		 	tripode.pata.pata.vec_tri[names[3]-600] = !tripode.pata.pata.vec_tri[names[3]-600];
	 	 } else if((names[3]>=700)&&(names[3]<800)) {
	 		 tripode.pata.pata.vec_tri[names[3]-700] = !tripode.pata.pata.vec_tri[names[3]-700];
	 	 } else if((names[3]>=800)&&(names[3]<900)) {
	 		 tripode.pata.pata.vec_tri[names[3]-800] = !tripode.pata.pata.vec_tri[names[3]-800];
		 }
	}
}

void pick_color(int x, int y)
{
		GLuint selectBuf[100]={0};
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
		procesar_hits(hits, selectBuf);
		// Dibujar la escena para actualizar cambios
		draw();
}

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
