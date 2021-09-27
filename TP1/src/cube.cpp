/********************************************************/
/*                     cube.cpp                                                 */
/********************************************************/
/*                Affiche a l'ecran un cube en 3D                      */
/********************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#include <GL/glut.h>   /* Pour les autres systemes */
#include <cstdlib>

/*class Point*/
class Point{
    public :
	//coordonnées x, y et z du point
	double x;
	double y;
	double z;
	// couleur r, v et b du point
	float r;
	float g;
	float b;
};

//Tableau pour stocker les sommets du cube et leur couleur
Point pCube[8]={
    {-0.5,-0.5, 0.5,1.0,0.0,0.0},
    { 0.5, -0.5, 0.5,0.0,1.0,0.0},
    { 0.5, -0.5, -0.5,0.0,0.0,1.0},
    { -0.5, -0.5, -0.5,1.0,1.0,1.0},
    { -0.5,0.5, 0.5,1.0,0.0,0.0},
    { 0.5, 0.5, 0.5,0.0,1.0,0.0},
    { 0.5, 0.5, -0.5,0.0,0.0,1.0},
    { -0.5, 0.5, -0.5,1.0,1.0,1.0}};

//Tableau pour stocker les indices des sommets par face pour le cube
int fCube[6][4]={
  {0,1,2,3},//face envers endroit={0,3,2,1}
  {0,1,5,4},
  {1,2,6,5},
  {2,3,7,6},
  {0,4,7,3},
  {4,5,6,7}};

char presse;
int anglex,angley,x,y,xold,yold;

/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void NotreIsosaedre();
Point milieu(Point pa, Point pb, float r, float g, float b);

int main(int argc,char **argv)
{
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(500,500);
  glutCreateWindow("cube");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(NotreIsosaedre);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'a':
      glPolygonMode(GL_FRONT,GL_FILL);
      glPolygonMode(GL_FRONT,GL_LINE);
      glutPostRedisplay();
    break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}

void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }

Point milieu(Point pa, Point pb, float r, float g, float b){
    Point pc = Point();

    pc.x = (pa.x+pb.x)/2;
    pc.y = (pa.y+pb.y)/2;
    pc.z = (pa.z+pb.z)/2;


    pc.r = r;
    pc.g = g;
    pc.b = b;

    return pc;
}

void NotreIsosaedre(){
    Point pico[12]={
        {milieu(pCube[0],pCube[1],1.0,0.0,0.0)},
        {milieu(pCube[1],pCube[2],1.0,1.0,0.0)},
        {milieu(pCube[2],pCube[3],1.0,0.0,1.0)},
        {milieu(pCube[3],pCube[0],0.0,0.0,0.0)},
        {milieu(pCube[0],pCube[4],0.0,1.0,0.0)},
        {milieu(pCube[1],pCube[5],0.0,0.0,1.0)},
        {milieu(pCube[2],pCube[6],1.0,1.0,1.0)},
        {milieu(pCube[3],pCube[7],1.0,0.0,0.0)},
        {milieu(pCube[4],pCube[5],1.0,0.0,0.0)},
        {milieu(pCube[5],pCube[6],1.0,0.0,0.0)},
        {milieu(pCube[6],pCube[7],1.0,0.0,0.0)},
        {milieu(pCube[7],pCube[4],1.0,0.0,0.0)}
    };

    int fico[20][3]={
        {0,1,2},
        {0,2,3},
        {0,5,4},
        {4,5,8},
        {1,9,5},
        {1,6,9},
        {2,6,7},
        {10,7,6},
        {3,7,11},
        {3,11,4},
        {8,10,11},
        {8,9,10},
        {0,4,3},
        {0,1,5},
        {1,6,2},
        {3,2,7},
        {4,8,11},
        {5,9,8},
        {6,10,9},
        {7,10,11},
    };

   int i,j;
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);

  glLoadIdentity();
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);

for (i=0;i<20;i++){
    glBegin(GL_POLYGON);
        for (j=0;j<3;j++){
            glColor3f(pico[fico[i][j]].r,pico[fico[i][j]].g,pico[fico[i][j]].b);
            glVertex3f(pico[fico[i][j]].x,pico[fico[i][j]].y,pico[fico[i][j]].z);
        }
    glEnd();
}
//Repère
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    	glColor3f(0.0,1.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    	glColor3f(0.0,0.0,1.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 0,1.0);
    glEnd();

  glFlush();

  //On echange les buffers
  glutSwapBuffers();
}
