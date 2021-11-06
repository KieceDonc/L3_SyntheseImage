#include "../include/Main.h"

bool withAnim,tailReverse;
char presse;
float anglex,angley,tailAngleX,tailAngleY;
int x,y,xold,yold,zoom;

float PI = 3.141592653589793;

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

Texture headT = Texture("./head.jpg");
Texture bodyT = Texture("./texturebody.jpg");

int main(int argc,char **argv)
{
    withAnim = false;
    zoom = 10;

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
    glEnable(GL_TEXTURE_2D);


    /* enregistrement des fonctions de rappel */
    if(withAnim)
    {
        glutIdleFunc(anim);
    }
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

void dessin()
{
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

    headT.enableTexture();

    Cube head = Cube(1.0f,new float[3] {0.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,0.0f},new float[3] {0.30f,0.30f,0.30f});

    Box eyesL = Box(0.2f,0.2f,0.4f,new float[3] {-head.getDimension()/2,head.getDimension()/6,-head.getDimension()/4},new float[3] {0.0f,0.0f,0.0f},new float[3] {0.5f,0.0f,0.30f},true);

    Box eyesR = Box(0.2f,0.2f,0.4f,new float[3] {-head.getDimension()/2,head.getDimension()/6, head.getDimension()/4},new float[3] {0.0f,0.0f,0.0f},new float[3] {0.5f,0.0f,0.30f},true);

    //bodyT.enableTexture();

    ParametricCylinder body = ParametricCylinder(1.0f,8.0f,30,new float[3] {head.getDimension()/2,0.0f,0.0f},new float[3] {0.0f,0.0f,-90.0f},new float[3] {0.15f,0.15f,0.15f},true);

    BezierWing wingR = BezierWing(3.0f,25,false,new float[3] {head.getDimension()/2+1.0f,-BezierWing::getHauteur()/2,body.getRayon()},new float[3] {0.0f,0.0f,0.0f},new float[3] {0.30f,0.30f,0.30f});
    BezierWing wingL = BezierWing(3.0f,25,true,new float[3] {head.getDimension()/2+1.0f,-BezierWing::getHauteur()/2,-body.getRayon()},new float[3] {0.0f,0.0f,0.0f},new float[3] {0.30f,0.30f,0.30f});
    BezierWing backwingR = BezierWing(5.0f,25,false,new float[3] {head.getDimension()/2+body.getHauteur()*0.5f,-BezierWing::getHauteur()/2,body.getRayon()},new float[3] {0.0f,0.0f,0.0f},new float[3] {0.30f,0.30f,0.30f});
    BezierWing backwingL = BezierWing(5.0f,25,true,new float[3] {head.getDimension()/2+body.getHauteur()*0.5f,-BezierWing::getHauteur()/2,-body.getRayon()},new float[3] {0.0f,0.0f,0.0f},new float[3] {0.30f,0.30f,0.30f});


    ParametricCylinder frontLegL = ParametricCylinder(0.45f,2.0f,3,new float[3] {head.getDimension()/2+body.getHauteur()*0.25,-sin(PI/4)*body.getRayon(),-cos(PI/4)*body.getRayon()},new float[3] {-90.0f-75.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,1.0f},false);
    ParametricCylinder frontLegR = ParametricCylinder(0.45f,2.0f,30,new float[3] {head.getDimension()/2+body.getHauteur()*0.25,-sin(PI/4)*body.getRayon(),cos(PI/4)*body.getRayon()},new float[3] {90.0f+75.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,1.0f},false);
    ParametricCylinder backLegL = ParametricCylinder(0.45f,2.0f,30,new float[3] {head.getDimension()/2+body.getHauteur()*0.75,-sin(PI/4)*body.getRayon(),-cos(PI/4)*body.getRayon()},new float[3] {-90.0f-75.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,1.0f},false);
    ParametricCylinder backLegR = ParametricCylinder(0.45f,2.0f,30,new float[3] {head.getDimension()/2+body.getHauteur()*0.75,-sin(PI/4)*body.getRayon(),cos(PI/4)*body.getRayon()},new float[3] {90.0f+75.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,1.0f},false);

    float feetRayon = 0.65f;
    Sphere frontfeetR = Sphere(feetRayon,new float[3] {frontLegR.getTranslate(0),frontLegR.getTranslate(1)-frontLegR.getHauteur(),frontLegR.getTranslate(2)+feetRayon/1.5},new float[3] {1.0f,0.0f,0.0f});
    Sphere frontfeetL = Sphere(feetRayon,new float[3] {frontLegL.getTranslate(0),frontLegL.getTranslate(1)-frontLegL.getHauteur(),frontLegL.getTranslate(2)-feetRayon/1.5},new float[3] {1.0f,0.0f,0.0f});
    Sphere backfeetR = Sphere(feetRayon,new float[3] {backLegR.getTranslate(0),backLegR.getTranslate(1)-backLegR.getHauteur(),backLegR.getTranslate(2)+feetRayon/1.5},new float[3] {1.0f,0.0f,0.0f});
    Sphere backfeetL = Sphere(feetRayon,new float[3] {backLegL.getTranslate(0),backLegL.getTranslate(1)-backLegL.getHauteur(),backLegL.getTranslate(2)-feetRayon/1.5},new float[3] {1.0f,0.0f,0.0f});

    Cone tail = Cone(1.0f,4.0f,new float[3] {head.getDimension()/2+body.getHauteur(),0.0f,0.0f},new float[3] {-90.0f+tailAngleX,tailAngleY+90,0.0f},new float[3] {0.30f,0.30f,0.30f});

    //On echange les buffers
    glutSwapBuffers();
}

void anim()
{
    anglex+=1.0f/50;
    glutPostRedisplay();
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
    case 'z':
        zoom-=1;
        if(zoom<0)
        {
            zoom=0;
        }
        glutPostRedisplay();
        break;
    case 'Z':
        zoom+=1;
        glutPostRedisplay();
        break;
    case 'h':
        if(tailAngleY>-50)
        {
            tailAngleY-=5.0f;
        }
        glutPostRedisplay();
        break;
    case 'n':
        if(tailAngleY<50)
        {
            tailAngleY+=5.0f;
        }
        glutPostRedisplay();
        break;
    case 'g':
        if(tailAngleX<100)
        {
            tailAngleX+=10.0f;
        }
        glutPostRedisplay();
        break;
    case 'j':
        if(tailAngleX>-100)
        {
            tailAngleX-=10.0f;
        }
        glutPostRedisplay();
        break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
        exit(0);
    }
}

void clavierSpecial(int touche,int x,int y)
{
    switch(touche)
    {
    case GLUT_KEY_LEFT:
    {
        anglex+=10;
        glutPostRedisplay();
        break;
    }
    case GLUT_KEY_UP:
    {
        angley-=10;
        glutPostRedisplay();
        break;
    }
    case GLUT_KEY_RIGHT:
    {
        anglex-=10;
        glutPostRedisplay();
        break;
    }
    case GLUT_KEY_DOWN:
    {
        angley+=10;
        glutPostRedisplay();
        break;
    }
    }
}

void reshape(int x,int y)
{
    if (x<y)
    {
        glViewport(0,(y-x)/2,x,x);
    }
    else
    {
        glViewport((x-y)/2,0,y,y);
    }
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
    {
        presse=0; /* le booleen presse passe a 0 (faux) */
    }
}

void mousemotion(int x,int y)
{
    if (presse)
    {
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

