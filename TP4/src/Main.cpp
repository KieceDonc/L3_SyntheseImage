#include <cstdio>
#include <cstdlib>
/****************************************************************/
/* works on mac using freeglut and xquartz                      */
/* you can install freeglut using homebrew                      */
/* xquartz can be downloaded at http://xquartz.macosforge.org   */
/****************************************************************/
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <jerror.h>

#include <cmath>

#ifdef __WIN32
#pragma comment (lib, "jpeg.lib")
#endif

unsigned char image[256*256*3];
char presse;
int anglex=30,angley=20,x,y,xold,yold;
const float PI = 3.14159265359;

void affichage();
void clavier(unsigned char touche,int x,int y);
void souris(int boutton, int etat,int x,int y);
void sourismouv(int x,int y);
void redim(int l,int h);
void loadJpegImage(char *fichier);


void drawSphere(int NM, int NP, float r){
    float coord[NP*NM][3]; // Tableau des coordonnées des sommets
    float faces[NP*NM][4]; // Tableau des indices des points par faces np = 4  nm = 3

    // Définition des coordonnées
    for(int j = 0 ; j < NP ; j++)
        for(int i = 0 ; i < NM ; i++){
            float theta = (i*2.0*PI)/(NM*1.0);
            float phi = (j*PI)/(NP-1.0)-(PI/2.0);
            coord[i+j*NP][0] = r * std::cos(theta) * std::cos(phi) ;
            coord[i+j*NP][1] = r * std::sin(theta) * std::cos(phi) ;
            coord[i+j*NP][2] = r * std::sin(phi) ;
        }

    // Définition des faces
    for(int j = 0 ; j < NP ; j++)
        for(int i = 0 ; i < NM ; i++){
            faces[i+j*NP][0] = i + j * NM ;
            faces[i+j*NP][1] = ((i+1) % NM ) + j * NM ;
            faces[i+j*NP][2] = ((i+1) % NM ) + ( j + 1 ) * NM ;
            faces[i+j*NP][3] = i + ( j + 1 ) * NM ;
        }

    // Tracé de la sphere
    for(int j = 0 ; j < NP*NM ; j++){
        int face1 = faces[j][0];
        int face2 = faces[j][1];
        int face3 = faces[j][2];
        int face4 = faces[j][3];

        glBegin(GL_POLYGON);
        glVertex3f(coord[face1][0], coord[face1][1], coord[face1][2]);
        glVertex3f(coord[face2][0], coord[face2][1], coord[face2][2]);
        glVertex3f(coord[face3][0], coord[face3][1], coord[face3][2]);
        glVertex3f(coord[face4][0], coord[face4][1], coord[face4][2]);

        glEnd();
    }

}


int main(int argc,char **argv)

{
  /* Chargement de la texture */
  loadJpegImage("./texture.jpg");

  /* Creation de la fenetre OpenGL */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(200,200);
  glutCreateWindow("Texture JPEG");

  /* Initialisation de l'etat d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  /* Mise en place de la projection perspective */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,1,1.0,5.0);
  glMatrixMode(GL_MODELVIEW);

  /* Parametrage du placage de textures */
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,256,256,0,
	       GL_RGB,GL_UNSIGNED_BYTE,image);
  glEnable(GL_TEXTURE_2D);

  /* Mise en place des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutMouseFunc(souris);
  glutMotionFunc(sourismouv);
  glutReshapeFunc(redim);

  /* Entr�e dans la boucle principale glut */
  glutMainLoop();
  return 0;
}



void affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0,0.0,2.5,0.0,0.0,0.0,0.0,1.0,0.0);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    drawSphere(50,50,0.5);

    /*glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(0.0,1.0);   glVertex3f(-0.5,-0.5, 0.5);
    glTexCoord2f(1.0,1.0);   glVertex3f( 0.5,-0.5, 0.5);
    glTexCoord2f(1.0,0.0);   glVertex3f( 0.5, 0.5, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f( 0.5, 0.5, 0.5);
    glTexCoord2f(0.0,1.0);   glVertex3f( 0.5,-0.5, 0.5);
    glTexCoord2f(1.0,1.0);   glVertex3f( 0.5,-0.5,-0.5);
    glTexCoord2f(1.0,0.0);   glVertex3f( 0.5, 0.5,-0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f( 0.5, 0.5,-0.5);
    glTexCoord2f(0.0,1.0);   glVertex3f( 0.5,-0.5,-0.5);
    glTexCoord2f(1.0,1.0);   glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(1.0,0.0);   glVertex3f(-0.5, 0.5,-0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5,-0.5);
    glTexCoord2f(0.0,1.0);   glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(1.0,1.0);   glVertex3f(-0.5,-0.5, 0.5);
    glTexCoord2f(1.0,0.0);   glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5,-0.5);
    glTexCoord2f(0.0,1.0);   glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(1.0,1.0);   glVertex3f( 0.5, 0.5, 0.5);
    glTexCoord2f(1.0,0.0);   glVertex3f( 0.5, 0.5,-0.5);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(0.0,1.0);   glVertex3f(-0.5,-0.5, 0.5);
    glTexCoord2f(1.0,1.0);   glVertex3f( 0.5,-0.5, 0.5);
    glTexCoord2f(1.0,0.0);   glVertex3f( 0.5,-0.5,-0.5);
    glEnd();*/

    glutSwapBuffers();

}



void clavier(unsigned char touche,int x,int y)
{
  switch(touche) {
  case 'l':
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glutPostRedisplay();
    break;
  case 'n':
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glutPostRedisplay();
  break;

  case 27: /* touche ESC */
    exit(0);
  default:
	  break;
  }
}

void souris(int bouton, int etat,int x,int y)
{
  if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN)
  {
    presse = 1;
    xold = x;
    yold=y;
  }
  if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
    presse=0;
}

void sourismouv(int x,int y)
  {
    if (presse)
    {
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay();
    }

    xold=x;
    yold=y;
  }

void redim(int l,int h)
{
  if (l<h)
    glViewport(0,(h-l)/2,l,l);
  else
    glViewport((l-h)/2,0,h,h);
}



void loadJpegImage(char *fichier)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *file;
  unsigned char *ligne;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
#ifdef __WIN32
  if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#elif __GNUC__
  if ((file = fopen(fichier,"rb")) == 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#endif
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  if ((cinfo.image_width!=256)||(cinfo.image_height!=256)) {
    fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
    exit(1);
  }
  if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
    fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
    exit(1);
  }

  jpeg_start_decompress(&cinfo);
  ligne=image;
  while (cinfo.output_scanline<cinfo.output_height)
    {
      ligne=image+3*256*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
}

/*
GLfloat position_source0[] = {0.0, 10.0, 0.0, 0.0};
GLfloat direction_source0[] = {1.0, 2.0, 3.0, 0.0};
GLfloat dif_0[] = {1.0, 0.0, 0.0, 1.0};
GLfloat amb_0[] = {1.0, 0.0, 0.0, 1.0};
GLfloat spec_0[] = {1.0, 1.0, 1.0, 1.0};

glLightfv(GL_LIGHT0, GL_POSITION, position_source0);
glLightfv(GL_LIGHT0, GL_AMBIENT, amb_0);
glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_0);
glLightfv(GL_LIGHT0, GL_SPECULAR, spec_0);


glEnable(GL_LIGHT0);
*/

