#include "ParametricCylinder.h"

ParametricCylinder::ParametricCylinder(float rayon, float hauteur, int precision, float translate[3], float rota[3], float colors[3], bool withTexture) : Object(translate,rota,colors,withTexture){
    this->rayon = rayon;
    this->hauteur = hauteur;
    this->precision = precision;
}

float ParametricCylinder::getRayon(){
    return this->rayon;
}

float ParametricCylinder::getHauteur(){
    return this->hauteur;
}

int ParametricCylinder::getPrecision(){
    return this->precision;
}

void ParametricCylinder::draw(){

    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )

    for (int t = 0; t <this->getPrecision(); t++) {
        glBegin(GL_POLYGON);

        float x0 = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
        float z0 = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());

        // can be optimize. We calculate almost each point 2 times
        float x1 = this->getRayon()*cos(2*this->getPi()*(t+1)/this->getPrecision());
        float z1 = this->getRayon()*sin(2*this->getPi()*(t+1)/this->getPrecision());


        float t0 = (float)t/this->getPrecision();
        float t1 = (t+1.0f)/this->getPrecision();

        if(this->isWithTexture()){
            glTexCoord2f(t0,0.0f);
        }
        glVertex3d(x0,0,z0);

        if(this->isWithTexture()){
            glTexCoord2f(t0,1.0f);
        }
        glVertex3d(x0,this->getHauteur(),z0);

        if(this->isWithTexture()){
            glTexCoord2f(t1,1.0f);
        }
        glVertex3d(x1,this->getHauteur(),z1);

        if(this->isWithTexture()){
            glTexCoord2f(t1,0.0f);
        }
        glVertex3d(x1,0,z1);
        glEnd();

    }

    glBegin(GL_POLYGON);
    for (int t = 0; t <this->getPrecision(); t++) {
        float x0 = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
        float z0 = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());
        glVertex3d(x0,0,z0);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int t = 0; t <this->getPrecision(); t++) {
        float x0 = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
        float z0 = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());
        glVertex3d(x0,this->getHauteur(),z0);
    }
    glEnd();

    glPopMatrix();


}
