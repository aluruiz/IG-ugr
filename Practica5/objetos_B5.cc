//**************************************************************************
// Práctica 5
//**************************************************************************

#include "objetos_B5.h"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size());

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
	/*vec_tri.resize(100);
	for (int i=0; i<vec_tri.size(); i++){
		vec_tri[i] = false;
	}*/

	seleccionado = false;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b, int nro)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);

//Para la seleccion de caras, si esta selecciona sale en amarillo
for (i=0;i<caras.size();i++){
	if (caras_selec[i]){
		glColor3f(0,0,255);
	} else 	glColor3f(r,g,b);

	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	glEnd();
	}

}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2, int nro)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0){
		if(caras_selec[i]){
			glColor3f(0, 0, 255);
		}
		else{
			glColor3f(r1,g1,b1);
		}
	}
	else{
		if(caras_selec[i]){
			glColor3f(0, 0, 255);
		}
		else{
			glColor3f(r2,g2,b2);
		}
	}

	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

void _triangulos3D::draw_seleccion_color(int r, int g, int b){
    unsigned i;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for(i = 0; i < caras.size(); i++){
        g = i / 255;
        b = i % 255;
        glColor3ub(r, g, b);
        glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }

    glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{

	if(seleccionado && (modo != SELECTION)){
        r1 = 255;   g1 = 255;   b1 = 0;
        r2 = 255;   g2 = 255;   b2 = 0;
    }

	switch (modo){
		case POINTS:draw_puntos(r1, g1, b1, grosor);break;
		case EDGES:draw_aristas(r1, g1, b1, grosor);break;
		case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2, nro);break;
		case SOLID:draw_solido(r1, g1, b1, nro);break;
		case SELECTION: draw_seleccion_color(r1, g1, b1); break;
		}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	//vertices
	vertices.resize(8);
	vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
	vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
	vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
	vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
	vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
	vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

	// triangulos
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
	caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
	caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
	caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
	caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
	caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
	caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
	caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
	caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
	caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
	caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
	caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;

	// vector para la selección de caras
    caras_selec.resize(caras.size());
    for(int i = 0; i < caras_selec.size(); i++){
        caras_selec[i] = false;
    }
}

/*void _cubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro ){
	switch (modo){
		case POINTS:draw_puntos(r1, g1, b1, grosor);break;
		case EDGES:draw_aristas(r1, g1, b1, grosor);break;
		default:
		int i;
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glPushMatrix();
		for (i=0;i<caras.size();i++){
			glLoadName(nro + i);
			glBegin(GL_TRIANGLES);
			std::cout << vec_tri[i];
			if (vec_tri[i]){
				std::cout << "Entro";
				glColor3f(255,255,0);
			} else{
				glColor3f(r1,g1,b1);
			}

			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
			glEnd();
			}
			glPopMatrix();
		break;
	}
}*/


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices
vertices.resize(5);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

// vector para la selección de caras
    caras_selec.resize(caras.size());
    for(int i = 0; i < caras_selec.size(); i++){
        caras_selec[i] = false;
    }
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices

}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;

_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

	// vector para la selección de caras
    caras_selec.resize(caras.size());
    for(int i = 0; i < caras_selec.size(); i++){
        caras_selec[i] = false;
    }

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }

	// tapa inferior
	if (fabs(perfil[0].x)>0.0)
	{
		vertice_aux.x=0.0;
		vertice_aux.y = perfil[0].y;
		vertice_aux.z=0.0;
		vertices.push_back(vertice_aux);

		for (j=0; j<num; j++){
			cara_aux._0=num_aux*num;
			cara_aux._1=j*num_aux;
			cara_aux._2=((j+1)%num)*num_aux;
			caras.push_back(cara_aux);
		}
	}

	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0)
	{
		vertice_aux.x=0.0;
		vertice_aux.y = perfil[num_aux-1].y;
		vertice_aux.z=0.0;
		vertices.push_back(vertice_aux);

		for (j=0; j<num; j++){
			cara_aux._0= num_aux*num+1;
			cara_aux._1=j*num_aux + num_aux-1;
			cara_aux._2=((j+1)%num)*num_aux + num_aux-1;
			caras.push_back(cara_aux);
		}
	}

	// vector para la selección de caras
    caras_selec.resize(caras.size());
    for(int i = 0; i < caras_selec.size(); i++){
        caras_selec[i] = false;
    }
};

/*void _rotacion::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro ){
	switch (modo){
		case POINTS:draw_puntos(r1, g1, b1, grosor);break;
		case EDGES:draw_aristas(r1, g1, b1, grosor);break;
		default:
		int i;
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glPushMatrix();
		for (i=0;i<caras.size();i++){
			glLoadName(nro + i);
			glBegin(GL_TRIANGLES);
			std::cout << vec_tri[i];
			if (vec_tri[i]){
				std::cout << "Entro";
				glColor3f(255,255,0);
			} else{
				glColor3f(r1,g1,b1);
			}

			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
			glEnd();
			}
			glPopMatrix();
		break;
	}
}*/

//************************************************************************
// objeto articulado: tripode
//************************************************************************
vector<vector<bool>> v;
vector<vector<bool>> _tripode::tripode_caras_selec = v;
int _tripode::n_objeto = 0;

_tripode::_tripode()
{
	MAX_zoom = 3;
	MIN_zoom = 1;
	MAX_alfa = 100;
	MIN_alfa = 0;
	altura_pata_max = 0;
	altura_pata_min = -0.5;

	objecto_selec.resize(5);
	for(int i = 0; i < 6; i++){
		objecto_selec[i]=false;
	}

	tripode_caras_selec.resize(14);

	//patas
	for (int i =0; i<9; i++){
		tripode_caras_selec[i].resize(pata.pata.caras.size());
		for (int j = 0; j<pata.pata.caras.size(); j++){
			tripode_caras_selec[i][j] = false;
		}
	}

	//cabeza
	for (int i =9; i<11; i++){
		tripode_caras_selec[i].resize(cabeza.base.caras.size());
		for (int j = 0; j<cabeza.base.caras.size(); j++){
			tripode_caras_selec[i][j] = false;
		}
	}

	//camara
	tripode_caras_selec[11].resize(camara.armazon.caras.size());
	for (int j = 0; j<camara.armazon.caras.size(); j++){
		tripode_caras_selec[11][j] = false;
	}

	tripode_caras_selec[12].resize(camara.click.caras.size());
	for (int j = 0; j<camara.click.caras.size(); j++){
		tripode_caras_selec[12][j] = false;
	}

	tripode_caras_selec[13].resize(camara.objetivo.caras.size());
	for (int j = 0; j<camara.objetivo.caras.size(); j++){
		tripode_caras_selec[13][j] = false;
	}
}

void _tripode::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{
camara.zoom = zoom;
camara.beta = beta;
bool modo_seleccion = (modo == SELECTION);

	glPushMatrix();
		glTranslatef(0,0,(cabeza.ancho_base/2));
		glLoadName(1);
		n_objeto = 0;
		if(objecto_selec[0] && !modo_seleccion){
			pata.draw(modo,255,255,0,255,255,0,2,altura_pata, 0, 0);
		} else {
			pata.draw(modo,r1,g1,b1,r2,g2,b2,2,altura_pata, 0, 0);
		}
		r1 += (modo_seleccion) ? 3:0;
	glPopMatrix();
	glPushMatrix();
		glTranslatef((cabeza.ancho_base/2), 0, -(cabeza.ancho_base/2));
		glLoadName(2);
		n_objeto = 1;
		if(objecto_selec[1] && !modo_seleccion){
			pata.draw(modo,255,255,0,255,255,0,2,altura_pata, 0, 0);
		} else {
			pata.draw(modo,r1,g1,b1,r2,g2,b2,2,altura_pata, 1, 0);
		}
		r1 += (modo_seleccion) ? 3:0;
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-(cabeza.ancho_base/2), 0,-(cabeza.ancho_base/2));
		glLoadName(3);
		n_objeto = 2;
		if(objecto_selec[2] && !modo_seleccion){
			pata.draw(modo,255,255,0,255,255,0,2,altura_pata, 0, 0);
		} else {
			pata.draw(modo,r1,g1,b1,r2,g2,b2,2,altura_pata, 2, 0);
		}
		r1 += (modo_seleccion) ? 3:0;
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, altura_pata*2, 0);
		glRotatef(alfa,0,1,0);
		glLoadName(4);
		if(objecto_selec[3] && !modo_seleccion){
			cabeza.draw(modo,255,255,0,255,255,0,2, 0);
		} else {
			cabeza.draw(modo,r1,g1,b1,r2,g2,b2,2, 0);
		}
		r1 += (modo_seleccion) ? 2:0;

		glLoadName(5);
		if(objecto_selec[4] && !modo_seleccion){
			camara.draw(modo,255,255,0,255,255,0,2, 0);
		} else {
			camara.draw(modo,r1,g1,b1,r2,g2,b2,2, 0);
		}
		r1 += (modo_seleccion) ? 3:0;
	glPopMatrix();
}

_pata::_pata()
{
  vector<_vertex3f> perfil;
  _vertex3f aux;
  aux.x=0.107;aux.y=-0.5;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.107;aux.y=0.5;aux.z=0.0;
  perfil.push_back(aux);
  pata.parametros(perfil, 12, 1);
  altura_pata=2.0;
	seleccionado.resize(3);
}

void _pata::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float altura_patas, int pos, int nro)
{
	int incremento = (modo == SELECTION)? 1:0;
	int inc_tres = _tripode::n_objeto * 3;
	if (seleccionado[pos]){
		r1 = 0;
		g1 = 0;
		b1 = 255;
		r2 = 255;
		g2 = 0;
		b2 = 0;
	}
	glPushMatrix();
		glTranslatef(0,-0.5+altura_patas*2,0);
		glScalef(0.75,1,0.75);
		pata.caras_selec = _tripode::tripode_caras_selec[0 + inc_tres];
		pata.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 600);
		r1 += incremento;
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-1+altura_patas,0);
		glScalef(0.5,1,0.5);
		pata.caras_selec = _tripode::tripode_caras_selec[1 + inc_tres];
		pata.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 700);
		r1 += incremento;
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-1.5,0);
		glScalef(0.25,1,0.25);
		pata.caras_selec = _tripode::tripode_caras_selec[2 + inc_tres];
		pata.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 800);
		r1 += incremento;
	glPopMatrix();
};

_cabeza::_cabeza()
{
	vector<_vertex3f> perfil;
  _vertex3f aux;
  aux.x=0.107;aux.y=-0.5;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.107;aux.y=0.5;aux.z=0.0;
  perfil.push_back(aux);
  base.parametros(perfil, 12, 1);
  altura_cabeza=0.3;
	ancho_base=0.107*3;
}

void _cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{
	int incremento = (modo == SELECTION)? 1:0;
	if (seleccionado){
		r1 = 0;
		g1 = 0;
		b1 = 255;
		r2 = 255;
		g2 = 0;
		b2 = 0;
	}
	//cabeza grande
	glPushMatrix();
		glScalef(3,0.15,3);
		base.caras_selec = _tripode::tripode_caras_selec[9];
		base.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 400);
		r1 += incremento;
	glPopMatrix();

	//cabeza pequeña
	glPushMatrix();
		glTranslatef(0,0.15,0);
		glScalef(0.25,0.15,0.25);
		base.caras_selec = _tripode::tripode_caras_selec[10];
		base.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 500);
		r1 += incremento;
	glPopMatrix();
};

_camara::_camara()
{
	vector<_vertex3f> perfil;
  _vertex3f aux;
  aux.x=0.107;aux.y=-0.5;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.107;aux.y=0.5;aux.z=0.0;
  perfil.push_back(aux);
  objetivo.parametros(perfil, 12, 1);
  altura_camara=0.30;
	m_armazon = 0.325;
	m_click = m_armazon/3;
	m_objetivo = m_armazon+(m_armazon/2);
	alt_armazon = m_armazon+(m_armazon/2);
	alt_click = altura_camara+alt_armazon/3+0.02;
	alt_objetivo = m_armazon - 0.05;
	armazon = _cubo(m_armazon);
}

void _camara::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{
	int incremento = (modo == SELECTION)? 1:0;
	if (seleccionado){
		r1 = 0;
		g1 = 0;
		b1 = 255;
		r2 = 255;
		g2 = 0;
		b2 = 0;
	}
	//armazon
	glPushMatrix();
		glTranslatef(0,altura_camara,0);
		glScalef(m_armazon*2,m_armazon+(m_armazon/2),m_armazon);
		armazon.caras_selec = _tripode::tripode_caras_selec[11];
		armazon.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 100);
		r1 += incremento;
	glPopMatrix();

	//click
	glPushMatrix();
		glTranslatef((m_armazon*2)/4,alt_click,0);
		glScalef(m_click,m_click/2,m_click);
		click.caras_selec = _tripode::tripode_caras_selec[12];
		click.draw(modo, r1, g1, b1, r2, g2, b2, grosor,200);
		r1 += incremento;
	glPopMatrix();

	//objetivo
	glPushMatrix();
		glTranslatef(0,alt_objetivo,(m_armazon/2)-0.1);
		glRotatef(90,1,0,0);
		glRotatef(beta,0,1,0);
		glScalef(m_objetivo*1.5,m_objetivo*0.15*zoom,m_objetivo*1.5);
		glTranslatef(0,0.5,0);
		objetivo.caras_selec = _tripode::tripode_caras_selec[13];
		objetivo.draw(modo, r1, g1, b1, r2, g2, b2, grosor,300);
		r1 += incremento;
	glPopMatrix();

};
