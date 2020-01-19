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
	vec_tri.resize(100);
	for (int i=0; i<vec_tri.size(); i++){
		vec_tri[i] = false;
		cout << vec_tri[i];
	}
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
glBegin(GL_TRIANGLES);
glPushMatrix();
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//Para la seleccion de caras, si esta selecciona sale en amarillo
for (i=0;i<caras.size();i++){
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glPushMatrix();
	if (vec_tri[i]){
		glColor3f(255,255,0);
	} else 	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	//glLoadName(nro + i);
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
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	/*glLoadName(nro + i);*/
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
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2, nro);break;
	case SOLID:draw_solido(r1, g1, b1, nro);break;
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
}

void _cubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro ){
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
}


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
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
rodamiento.parametros(perfil,12,1);
altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();

glPushMatrix();
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
altura=0.18;
anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.04;aux.y=-0.4;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.04;aux.y=0.4;aux.z=0.0;
perfil.push_back(aux);
tubo_abierto.parametros(perfil,12,0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{

glPushMatrix();
glTranslatef(0.4,0,0);
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tubo=2.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{
glPushMatrix();
chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);

glRotatef(giro_torreta,0,1,0);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tubo,0,0,1);
tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 0);
glPopMatrix();
glPopMatrix();

};

//************************************************************************
// objeto articulado: tripode
//************************************************************************
_tripode::_tripode()
{
	MAX_zoom = 3;
	MIN_zoom = 1;
	MAX_alfa = 100;
	MIN_alfa = 0;
	altura_pata_max = 0;
	altura_pata_min = -0.5;
}

void _tripode::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, int nro)
{
camara.zoom = zoom;
camara.beta = beta;

	glPushMatrix();
		glTranslatef(0,0,(cabeza.ancho_base/2));
		glLoadName(1);
		pata.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2,altura_pata, 0, 0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef((cabeza.ancho_base/2), 0, -(cabeza.ancho_base/2));
		glLoadName(2);
		pata.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2,altura_pata, 1, 0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-(cabeza.ancho_base/2), 0,-(cabeza.ancho_base/2));
		glLoadName(3);
		pata.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2,altura_pata, 2, 0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, altura_pata*2, 0);
		glRotatef(alfa,0,1,0);
		glLoadName(4);
		cabeza.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2, 0);
		glLoadName(5);
		camara.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2, 0);
	glPopMatrix();
}

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
		armazon.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 100);
	glPopMatrix();

	//click
	glPushMatrix();
		glTranslatef((m_armazon*2)/4,alt_click,0);
		glScalef(m_click,m_click/2,m_click);
		click.draw(modo, r1, g1, b1, r2, g2, b2, grosor,200);
	glPopMatrix();

	//objetivo
	glPushMatrix();
		glTranslatef(0,alt_objetivo,(m_armazon/2)-0.1);
		glRotatef(90,1,0,0);
		glRotatef(beta,0,1,0);
		glScalef(m_objetivo*1.5,m_objetivo*0.15*zoom,m_objetivo*1.5);
		glTranslatef(0,0.5,0);
		objetivo.draw(modo, r1, g1, b1, r2, g2, b2, grosor,300);
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
		base.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 400);
	glPopMatrix();

	//cabeza pequeña
	glPushMatrix();
		glTranslatef(0,0.15,0);
		glScalef(0.25,0.15,0.25);
		base.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 500);
	glPopMatrix();
};

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
		pata.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 600);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-1+altura_patas,0);
		glScalef(0.5,1,0.5);
		pata.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 700);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-1.5,0);
		glScalef(0.25,1,0.25);
		pata.draw(modo, r1, g1, b1, r2, g2, b2, grosor, 800);
	glPopMatrix();
};
