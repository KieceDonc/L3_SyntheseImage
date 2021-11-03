#include "Sphere.h"

Sphere::Sphere(float rayon, float translate[3],float colors[3]) : Object(translate,new float[3]{0.0f,0.0f,0.0f},colors,false){
    this->rayon = rayon;
    this->draw();
}

float Sphere::getRayon(){
    return this->rayon;
}

void Sphere::draw(){
    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )
    glutSolidSphere(this->rayon,20,20);
    glPopMatrix();
}
