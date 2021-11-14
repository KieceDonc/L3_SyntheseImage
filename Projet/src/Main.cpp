#include "../include/Main.h"

bool withAnim,wingReverse;
char presse;
float anglex,angley,tailAngleY,wingAngleZ;
int x,y,xold,yold,zoom;
int lightOn = 0;

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

Texture headT = Texture("./assets/eyes.jpg");
Texture bodyT = Texture("./assets/body.jpg");

int main(int argc,char **argv){
    withAnim = true;
    wingReverse = true;
    zoom = 10;

    /* initialisation de glut et creation
     de la fenetre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(1000,750);
    glutCreateWindow("Le dragon abeille");

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
    glutIdleFunc(anim);
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

void manageLights(){
    if(lightOn == 1){

    // Enabling the lighting
    glEnable(GL_LIGHTING);
    // Enabling the lighting of every objects
    glEnable(GL_COLOR_MATERIAL);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

    //Positiong of light source
    GLfloat position_source0[] = {20,-10.0,0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION,position_source0);

    // Diffuse light
    GLfloat diffuseCol0[] = {0.5, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, diffuseCol0);

    // Ambiant light
    GLfloat ambiantCol0[] = {0.5, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ambiantCol0);

    // Specular light
    GLfloat specularCol0[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularCol0);

    GLfloat speculaire[] = {1.0, 1.0, 1.0, 1.0}; // blanc


    //Turning this light on
    glEnable(GL_LIGHT0);

    }

    if(lightOn == 2){
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    GLfloat couleur[] = {0.8, 0.8, 0.8, 1.0};//composante diffuse rouge
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, couleur);
    }

    if(lightOn == 0){
        glDisable(GL_LIGHTING);
    }
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
    manageLights();

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

    /* drawing head (cube) and eyes (box) */
    Cube head = Cube(1.0f,new float[3] {0.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,0.0f},new float[3] {0.30f,0.30f,0.30f});
    Box eyesL = Box(0.2f,0.2f,0.4f,new float[3] {-head.getDimension()/2,head.getDimension()/6,-head.getDimension()/4},new float[3] {0.0f,0.0f,0.0f},new float[3] {1.0f,1.0f,1.0f},true);
    Box eyesR = Box(0.2f,0.2f,0.4f,new float[3] {-head.getDimension()/2,head.getDimension()/6, head.getDimension()/4},new float[3] {0.0f,0.0f,0.0f},new float[3] {1.0f,1.0f,1.0f},true);

    bodyT.enableTexture();

    ParametricCylinder body = ParametricCylinder(1.0f,8.0f,30,new float[3] {head.getDimension()/2,0.0f,0.0f},new float[3] {0.0f,0.0f,-90.0f},new float[3] {0.75f,0.75f,0.75f},true);

    /* drawing wings */
    BezierWing wingR = BezierWing(3.0f,25,false,new float[3] {head.getDimension()/2+1.0f,-BezierWing::getHauteur()/2,body.getRayon()},new float[3] {0.0f,0.0f,wingAngleZ+45.0f},new float[3] {0.30f,0.30f,0.30f});
    BezierWing wingL = BezierWing(3.0f,25,true,new float[3] {head.getDimension()/2+1.0f,-BezierWing::getHauteur()/2,-body.getRayon()},new float[3] {0.0f,0.0f,wingAngleZ+45.0f},new float[3] {0.30f,0.30f,0.30f});
    BezierWing backwingR = BezierWing(5.0f,25,false,new float[3] {head.getDimension()/2+body.getHauteur()*0.5f,-BezierWing::getHauteur()/2,body.getRayon()},new float[3] {0.0f,0.0f,wingAngleZ+45.0f},new float[3] {0.30f,0.30f,0.30f});
    BezierWing backwingL = BezierWing(5.0f,25,true,new float[3] {head.getDimension()/2+body.getHauteur()*0.5f,-BezierWing::getHauteur()/2,-body.getRayon()},new float[3] {0.0f,0.0f,wingAngleZ+45.0f},new float[3] {0.30f,0.30f,0.30f});

    /* drawing legs */
    ParametricCylinder frontLegL = ParametricCylinder(0.45f,2.0f,30,new float[3] {head.getDimension()/2+body.getHauteur()*0.25,-sin(PI/4)*body.getRayon(),-cos(PI/4)*body.getRayon()},new float[3] {-90.0f-75.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,1.0f},false);
    ParametricCylinder frontLegR = ParametricCylinder(0.45f,2.0f,30,new float[3] {head.getDimension()/2+body.getHauteur()*0.25,-sin(PI/4)*body.getRayon(),cos(PI/4)*body.getRayon()},new float[3] {90.0f+75.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,1.0f},false);
    ParametricCylinder backLegL = ParametricCylinder(0.45f,2.0f,30,new float[3] {head.getDimension()/2+body.getHauteur()*0.75,-sin(PI/4)*body.getRayon(),-cos(PI/4)*body.getRayon()},new float[3] {-90.0f-75.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,1.0f},false);
    ParametricCylinder backLegR = ParametricCylinder(0.45f,2.0f,30,new float[3] {head.getDimension()/2+body.getHauteur()*0.75,-sin(PI/4)*body.getRayon(),cos(PI/4)*body.getRayon()},new float[3] {90.0f+75.0f,0.0f,0.0f},new float[3] {0.0f,0.0f,1.0f},false);

    /* drawing legs feet */
    float feetRayon = 0.65f;
    Sphere frontfeetR = Sphere(feetRayon,new float[3] {frontLegR.getTranslate(0),frontLegR.getTranslate(1)-frontLegR.getHauteur(),frontLegR.getTranslate(2)+feetRayon/1.5},new float[3] {1.0f,0.0f,0.0f});
    Sphere frontfeetL = Sphere(feetRayon,new float[3] {frontLegL.getTranslate(0),frontLegL.getTranslate(1)-frontLegL.getHauteur(),frontLegL.getTranslate(2)-feetRayon/1.5},new float[3] {1.0f,0.0f,0.0f});
    Sphere backfeetR = Sphere(feetRayon,new float[3] {backLegR.getTranslate(0),backLegR.getTranslate(1)-backLegR.getHauteur(),backLegR.getTranslate(2)+feetRayon/1.5},new float[3] {1.0f,0.0f,0.0f});
    Sphere backfeetL = Sphere(feetRayon,new float[3] {backLegL.getTranslate(0),backLegL.getTranslate(1)-backLegL.getHauteur(),backLegL.getTranslate(2)-feetRayon/1.5},new float[3] {1.0f,0.0f,0.0f});

    /* drawing tail */
    Cone tail = Cone(1.0f,4.0f,new float[3] {head.getDimension()/2+body.getHauteur(),0.0f,0.0f},new float[3] {-90.0f,tailAngleY+90,0.0f},new float[3] {0.30f,0.30f,0.30f});

    manageLights();


    //On echange les buffers
    glutSwapBuffers();
}

void anim(){
    /* Handle tail animation */
    if(!wingReverse){
        wingAngleZ+=1.0f/50;
    }else{
        wingAngleZ-=1.0f/50;
    }
    if(wingAngleZ>25){
        wingReverse = true;
    }else if(wingAngleZ<-25){
        wingReverse = false;
    }
    glutPostRedisplay();
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
        case 'z': /* Zoom in */
            zoom-=1;
            if(zoom<0){
                zoom=0;
            }
            glutPostRedisplay();
            break;
        case 'Z': /* Zoom out */
            zoom+=1;
            glutPostRedisplay();
            break;
        case 'h': /* raise the tail */
            if(tailAngleY>-50){
                tailAngleY-=5.0f;
            }
            glutPostRedisplay();
            break;
        case 'n': /* lower the tail */
            if(tailAngleY<50){
                tailAngleY+=5.0f;
            }
            glutPostRedisplay();
            break;
        case 'a': /* enable / disable automatic animation */
            if(withAnim){
                withAnim = false;
                glutIdleFunc(NULL);
            }else{
                withAnim = true;
                glutIdleFunc(anim);
            }
            break;
        case '3':
            lightOn = 3;
            break;
        case '2':
            lightOn = 2;
            break;
        case '1':
            lightOn = 1;
            break;
        case '0':
            lightOn = 0;
            break;
        case 'q' : /*la touche 'q' permet de quitter le programme */
            exit(0);
    }
}

void clavierSpecial(int touche,int x,int y){
    /* Handle camera mouvement with keyboard */
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



