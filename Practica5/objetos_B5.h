//**************************************************************************
// Práctica 5
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID, SELECTION} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void draw_aristas(float r, float g, float b, int grosor);
void draw_solido(float r, float g, float b, int nro);
void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2, int nro);
void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro);
void draw_solido_cara(float r1, float g1, float b1, float r2, float g2, float b2, int n);
void draw_seleccion_color(int r, int g, int b);
//draw_solido_seleccion_completa(float r, float g, float b);
//draw_solido_seleccion_cara(float r, float g, float b);

bool seleccionado;
vector<bool> caras_selec;

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:
	_cubo(float tam=0.5);
	//void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);
//void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro);
vector<_vertex3f> perfil;
int num;
};


//************************************************************************
// objeto articulado: tripode
//************************************************************************

class _pata: public _triangulos3D
{
public:
      _pata();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float altura_patas, int pos, int nro );
vector<bool> vec_tri;
float altura_pata;
vector<bool> seleccionado;

_rotacion pata;
};

class _camara: public _triangulos3D
{
public:
      _camara();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro );

float altura_camara;
float m_armazon;
float m_click;
float m_objetivo;
float alt_armazon;
float alt_click;
float alt_objetivo;
float zoom = 1;
float beta = 0;
bool seleccionado;

_rotacion objetivo;
_cubo armazon;
_cubo click;
};

class _cabeza: public _triangulos3D
{
public:
      _cabeza();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro );

float altura_cabeza;
float ancho_base;
bool seleccionado;

_rotacion base;
};

class _tripode: public _triangulos3D
{
public:
      _tripode();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro );

float altura;
float alfa = 0;
float zoom = 1;
float beta = 0;
float altura_pata = 0;
float MAX_zoom;
float MIN_zoom;
float MAX_alfa;
float MIN_alfa;
float altura_pata_max;
float altura_pata_min;

vector<bool> objecto_selec;
static int n_objeto;
static vector<vector<bool>> tripode_caras_selec;

_pata pata;
_cabeza cabeza;
_camara camara;
};
