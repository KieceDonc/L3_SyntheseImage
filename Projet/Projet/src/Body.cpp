#include "Body.h"

Body::Body(float rayon, float hauteur, int precision, float translate[3], float rota[3]) : Object(translate,rota){
    this->rayon = rayon;
    this->hauteur = hauteur;
    this->precision = precision;
    this->setColors(new float[3]{1.0f,1.0f,0.0f});
}

float Body::getRayon(){
    return this->rayon;
}

float Body::getHauteur(){
    return this->hauteur;
}

int Body::getPrecision(){
    return this->precision;
}

void Body::draw(){

    glPushMatrix();
    this->onDraw();

    glBegin(GL_POLYGON);

    //for(int h = 0;h<2;h++){
        for (int t = 1; t <= this->getPrecision(); t++) {
            float x0 = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
            float z0 = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());

            // can be optimize. We calculate almost each point 2 times
            float x1 = this->getRayon()*cos(2*this->getPi()*(t+1)/this->getPrecision());
            float z1 = this->getRayon()*sin(2*this->getPi()*(t+1)/this->getPrecision());
            glVertex3d(x0,0,z0);
            glVertex3d(x0,this->getHauteur(),z0);
            glVertex3d(x1,this->getHauteur(),z1);
            glVertex3d(x1,0,z1);
            /*
            glVertex3d(x1,y1,0);
            glVertex3d(x0,y0,0);
            glVertex3d(x0,y0,this->getHauteur());
            glVertex3d(x1,y1,this->getHauteur());
            */
        }
        /*for (int t = 0; t <= this->getPrecision(); t++) {
            float x = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
            float y = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());
            glVertex3d(x,y,this->getHauteur());
            //glVertex3d(x,y,this->getHauteur());
        }*/
    //}
    glEnd();
    glPopMatrix();


}
