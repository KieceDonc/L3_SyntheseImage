#include "../include/Main.h"

char presse;
int anglex,angley,x,y,xold,yold,zoom;

/* Prototype des fonctions */
void anim();
void affichage();
void clavier(unsigned char touche,int x,int y);
void clavierSpecial(int touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void dessin();

int main(int argc,char **argv){
    zoom = 5;
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
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    /* Parametrage du placage de textures */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    Texture headT = Texture("./headtest.jpg");
    glEnable(GL_TEXTURE_2D);


    /* enregistrement des fonctions de rappel */
    //glutIdleFunc(anim);
    glutDisplayFunc(dessin);
    glutKeyboardFunc(clavier);
    glutSpecialFunc(clavierSpecial);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}

void dessin(){
    int i,j;
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();
    glOrtho(-zoom,zoom,-zoom,zoom,-zoom,zoom);
    glRotatef(anglex,0.0f,1.0f,0.0f);
    glRotatef(angley,1.0f,0.0f,0.0f);

    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0,0,0.0);
        glVertex3f(10,0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(0,0,0.0);
        glVertex3f(0,10,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0,0,0.0);
        glVertex3f(0,0,10.0);
    glEnd();

    glFlush();

    Head head = Head(0.4f,new float[3]{0.0f,0.0f,0.0f},new float[3]{0.0f,0.0f,0.0f},false);
    head.draw();
    Body body = Body(0.8f,2.0f,30,new float[3]{head.getDimension(),0.0f,0.0f},new float[3]{0.0f,0.0f,-90.0f},true);
    body.draw();

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
        case 'z':
            zoom-=1;
            if(zoom<0){
                zoom=0;
            }
            glutPostRedisplay();
            break;
        case'Z':
            zoom+=1;
            glutPostRedisplay();
            break;
        case 'q' : /*la touche 'q' permet de quitter le programme */
            exit(0);
    }
}

void clavierSpecial(int touche,int x,int y){
    switch(touche){
        case GLUT_KEY_LEFT:{
            anglex+=10;
            glutPostRedisplay();
            break;
        }
        case GLUT_KEY_UP:{
            angley-=10;
            glutPostRedisplay();
            break;
        }
        case GLUT_KEY_RIGHT:{
            anglex-=10;
            glutPostRedisplay();
            break;
        }
        case GLUT_KEY_DOWN:{
            angley+=10;
            glutPostRedisplay();
            break;
        }
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
    }
}

void mousemotion(int x,int y){
    if (presse){
        /* si le bouton gauche est presse */
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
    glutPostRedisplay();
}

