#include "Cone.h"

Cone::Cone(float base, float hauteur,float translate[3], float rota[3],float colors[3]) : Object(translate,rota,colors,false){
    this->base = base;
    this->hauteur = hauteur;
}

float Cone::getBase(){
    return this->base;
}

float Cone::getHauteur(){
    return this->hauteur;
}

void Cone::draw(){
    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )

    glutSolidCone(this->getBase(),this->getHauteur(),20,20);

    glPopMatrix();
}
