#include "Head.h"

Head::Head(float dimension, float translate[3], float rota[3]) : Object(translate,rota){
    this->dimension = dimension;
    this->setColors(new float[3]{1.0f,1.0f,1.0f});
}

float Head::getDimension(){
    return this->dimension;
}

void Head::draw(){
    glPushMatrix();
    this->onDraw();
    glutSolidSphere(this->dimension,20,20);
    glPopMatrix();
}
