#include "Body.h"

Body::Body(float rayon, float hauteur, int precision, float translate[3], float rota[3], bool withTexture) : Object(translate,rota,withTexture){
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

    for (int t = 1; t <= this->getPrecision(); t++) {
        float x0 = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
        float z0 = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());

        // can be optimize. We calculate almost each point 2 times
        float x1 = this->getRayon()*cos(2*this->getPi()*(t+1)/this->getPrecision());
        float z1 = this->getRayon()*sin(2*this->getPi()*(t+1)/this->getPrecision());

        if(this->isWithTexture()){
            glTexCoord2f(0.0,0.0);
        }
        glVertex3d(x0,0,z0);

        if(this->isWithTexture()){
            glTexCoord2f(1.0,0.0);
        }
        glVertex3d(x0,this->getHauteur(),z0);

        if(this->isWithTexture()){
            glTexCoord2f(1.0,t/this->getPrecision());
        }
        glVertex3d(x1,this->getHauteur(),z1);

        if(this->isWithTexture()){
            glTexCoord2f(0.0,t/this->getPrecision());
        }
        glVertex3d(x1,0,z1);
    }
    glEnd();
    glPopMatrix();


}
