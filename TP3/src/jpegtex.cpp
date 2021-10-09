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
#include <iostream>

#ifdef __WIN32
#pragma comment (lib, "jpeg.lib")
#endif

char presse;
const unsigned int largimg = 256;
const unsigned int hautimg = 256;
const unsigned int textureWidth = largimg*2;
const unsigned int textureHeight = hautimg*2;
int anglex=30,angley=20,x, y, xold, yold;

unsigned char texture[largimg][hautimg][3]; // damier static GLubyte checkImage0[largimg][hautimg][4];
unsigned char texture2[largimg*2][hautimg*2][3];

void affichage();
void clavier(unsigned char touche,int x,int y);
void souris(int boutton, int etat,int x,int y);
void sourismouv(int x,int y);
void redim(int l,int h);
void loadJpegImage(char *fichier);

int main(int argc,char **argv){
    /* Chargement de la texture */
    loadJpegImage("./calimero.jpg");

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
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,textureWidth,textureHeight,0,
           GL_RGB,GL_UNSIGNED_BYTE,texture2);
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



void affichage(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0,0.0,2.5,0.0,0.0,0.0,0.0,1.0,0.0);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(0.0,0.5);   glVertex3f(-0.5,-0.5, 0.5);
    glTexCoord2f(0.5,0.5);   glVertex3f( 0.5,-0.5, 0.5);
    glTexCoord2f(0.5,0.0);   glVertex3f( 0.5, 0.5, 0.5);
    glEnd();


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f( 0.5, 0.5, 0.5);
    glTexCoord2f(0.0,1.0*3);   glVertex3f( 0.5,-0.5, 0.5);
    glTexCoord2f(1.0*3,1.0*3);   glVertex3f( 0.5,-0.5,-0.5);
    glTexCoord2f(1.0*3,0.0);   glVertex3f( 0.5, 0.5,-0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f( 0.5, 0.5,-0.5);
    glTexCoord2f(0.0,1.0);   glVertex3f( 0.5,-0.5,-0.5);
    glTexCoord2f(1.0*0.5,1.0);   glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(1.0*0.5,0.0);   glVertex3f(-0.5, 0.5,-0.5);
    glEnd();


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5,-0.5);
    glTexCoord2f(0.0,1.0*3);   glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(1.0*3,1.0*3);   glVertex3f(-0.5,-0.5, 0.5);
    glTexCoord2f(1.0*3,0.0);   glVertex3f(-0.5, 0.5, 0.5);
    glEnd();


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(-0.5, 0.5,-0.5);
    glTexCoord2f(0.0,1.0*3);   glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(1.0*3,1.0*3);   glVertex3f( 0.5, 0.5, 0.5);
    glTexCoord2f(1.0*3,0.0);   glVertex3f( 0.5, 0.5,-0.5);
    glEnd();


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);   glVertex3f(-0.5,-0.5,-0.5);
    glTexCoord2f(0.0,1.0*3);   glVertex3f(-0.5,-0.5, 0.5);
    glTexCoord2f(1.0*3,1.0*3);   glVertex3f( 0.5,-0.5, 0.5);
    glTexCoord2f(1.0*3,0.0);   glVertex3f( 0.5,-0.5,-0.5);
    glEnd();

    glutSwapBuffers();

}



void clavier(unsigned char touche,int x,int y){
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

void souris(int bouton, int etat,int x,int y){
  if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN){
    presse = 1;
    xold = x;
    yold=y;
  }
  if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
    presse=0;
}

void sourismouv(int x,int y){
    if (presse){
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay();
    }

    xold=x;
    yold=y;
  }

void redim(int l,int h){
  if (l<h)
    glViewport(0,(h-l)/2,l,l);
  else
    glViewport((l-h)/2,0,h,h);
}



void loadJpegImage(char *fichier){
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;
    unsigned char image[largimg*hautimg*3];


    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    #ifdef __WIN32
    if (fopen_s(&file,fichier,"rb") != 0){
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
    #elif __GNUC__
    if ((file = fopen(fichier,"rb")) == 0){
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
    #endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    if ((cinfo.image_width!=largimg)||(cinfo.image_height!=hautimg)){
        fprintf(stdout,"Erreur : l'image doit etre de taille 256x256\n");
        std::cout << largimg << " " << hautimg << " "<< cinfo.image_width << " " << cinfo.image_height;
        exit(1);
    }
    if (cinfo.jpeg_color_space==JCS_GRAYSCALE){
        fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne=image;
    while (cinfo.output_scanline<cinfo.output_height){
      ligne=image+3*hautimg*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    for(int x=0;x<256;x++){
        for(int y=0;y<256;y++){
            texture[x][y][0]=image[x*256*3+y*3];
            texture[x][y][1]=image[x*256*3+y*3+1];;
            texture[x][y][2]=image[x*256*3+y*3+2];;
        }
    }

    for(int x=0;x<512;x++){
        for(int y=0;y<512;y++){
            if((x<256 && y<256)){
                texture2[x][y][0]=texture[x][y][0];
                texture2[x][y][1]=texture[x][y][1];
                texture2[x][y][2]=texture[x][y][2];
            }else if(x>=256 && y>=256){
                texture2[x][y][0]=texture[x-256][y-256][0];
                texture2[x][y][1]=texture[x-256][y-256][1];
                texture2[x][y][2]=texture[x-256][y-256][2];
            }else{
                texture2[x][y][0]=255;
                texture2[x][y][1]=255;
                texture2[x][y][2]=255;
            }
        }
    }
}
