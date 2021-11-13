#include "../include/Main.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cmath>

char presse;
int anglex,angley,x,y,xold,yold,armAngle,firstAnimAngle;
float scale,armAngleRad,firstAnimAngleRad;

/* Prototype des fonctions */
void anim();
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void dessin();
void drawBase();
void drawRotule0();
void drawArm0();
void drawRotule1();
void drawArm1();
void drawHand();
void drawFinger0();
void drawFinger1();

void lights(){
        //coord homogènes : position
    GLfloat position_source0[] = {5.0, 5.0, 5.0, 1.0};
    //direction source à distance infinie
    GLfloat direction_source0[] = {1.0, 2.0, 3.0, 0.0};
    GLfloat dif_0[] = {1.0, 0.0, 0.0, 1.0};//composante diffuse rouge
    GLfloat amb_0[] = {1.0, 0.0, 0.0, 1.0}; //composante ambiante rouge
    GLfloat spec_0[] = {1.0, 1.0, 1.0, 1.0}; //composante spéculaire blanche
    //spécification des propriétés
    glLightfv(GL_LIGHT0, GL_POSITION,position_source0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec_0);
    //activation de la source GL_LIGHT0
    glEnable(GL_LIGHT0);
}

int main(int argc,char **argv){
    scale = 0.25;

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
    glutIdleFunc(anim);
    glutDisplayFunc(dessin);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    lights();

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}


void dessin(){
    int val = 6;
    int i,j;


    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();
    glOrtho(-val,val,-val,val,-val,val);
    glRotatef(angley,1.0,0.0,0.0);
    glRotatef(anglex,0.0,1.0,0.0);

    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(10, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 10,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 0,10.0);
    glEnd();

    glFlush();

    drawBase();
    drawRotule0();
    drawArm0();
    drawRotule1();
    glPushMatrix();
        glTranslatef(0,3.2f,0);
        glRotatef(armAngle,0,0,-1);
        glTranslatef(0,0.4f,0);

        drawArm1();
        glPushMatrix();
            glRotatef(firstAnimAngleRad,0,1,0);
            drawHand();
            drawFinger0();
            drawFinger1();

        glPopMatrix();

    glPopMatrix();

    //On echange les buffers
    glutSwapBuffers();
}



void clavier(unsigned char touche,int x,int y){
    switch (touche){
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
        case 'r':
            armAngle+=10;
            armAngleRad = armAngle*3.14159/180;
            glutPostRedisplay();
            break;
        case 'R':
            armAngle-=10;
            armAngleRad = armAngle*3.14159/180;
            glutPostRedisplay();
            break;
        case 'q' : /*la touche 'q' permet de quitter le programme */
            exit(0);
    }
}

void reshape(int x,int y){
    if (x<y){
        glViewport(0,(y-x)/2,x,x);
    }else{
        glViewport((x-y)/2,0,y,y);
    }
}

void mouse(int button, int state,int x,int y){
    /* si on appuie sur le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        presse = 1; /* le booleen presse passe a 1 (vrai) */
        xold = x; /* on sauvegarde la position de la souris */
        yold=y;
    }
    /* si on relache le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        presse=0; /* le booleen presse passe a 0 (faux) */
        presse=0; /* le booleen presse passe a 0 (faux) */
    }
}

void mousemotion(int x,int y){
    if (presse){ /* si le bouton gauche est presse */
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

void anim(){
    firstAnimAngle+=100;
    firstAnimAngleRad = firstAnimAngle*3.14159/180;
    glutPostRedisplay();
}

void drawBase(){
    glPushMatrix();
    glTranslatef(0.0f,0.25f,0.0f);
    glScalef(2.0f,0.5f,1.0f);
    glutSolidCube(1);
    glPopMatrix();
}

void drawRotule0(){
    glPushMatrix();
    glTranslatef(0.0f,0.9f,0.0f);
    glColor3f(1.0,1.0,0.0);
    glutSolidSphere(0.4,20,20);
    glPopMatrix();
}

void drawArm0(){
    glPushMatrix();
    glTranslatef(0.0f,1.3f,0.0f);
    glColor3f(0.0,1.0,1.0);
    glRotatef(90,-1,0,0);
    glutSolidCylinder(0.2,1.5,20,20);
    glPopMatrix();
}

void drawRotule1(){
    glPushMatrix();
    glTranslatef(0.0f,3.2f,0.0f);
    glColor3f(1.0,1.0,0.0);
    glutSolidSphere(0.4,20,20);
    glPopMatrix();
}
void drawArm1(){
    glPushMatrix();
    glColor3f(0.0,1.0,1.0);
    glRotatef(90,-1,0,0);
    glutSolidCylinder(0.2,1.5,20,20);
    glPopMatrix();
}

void drawHand(){
    glPushMatrix();
    glTranslatef(0,1.6f,0);
    glScalef(0.8f,0.2f,0.8f);
    glColor3f(0.5,0.8,0.7);
    glutSolidCube(1);
    glPopMatrix();
}

void drawFinger0(){
    glPushMatrix();
    glTranslatef(0.3f,2.2f,0.0f);
    glScalef(0.2f,1.0f,0.8f);
    glColor3f(0.7,1,0.4);
    glutSolidCube(1);
    glPopMatrix();
}

void drawFinger1(){
    glPushMatrix();
    glTranslatef(-0.3f,2.2f,0.0f);
    glScalef(0.2f,1.0f,0.8f);
    glColor3f(0.7,1,0.4);
    glutSolidCube(1);
    glPopMatrix();
}
