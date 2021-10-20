#include "Cube.h"

Cube::Cube(float dimension, float translate[3], float rota[3], bool withTexture) : Object(translate,rota,withTexture){
    this->dimension = dimension;
    this->setColors(new float[3]{0.30f,0.30f,0.30f});
}

float Cube::getDimension(){
    return this->dimension;
}

void Cube::draw(){
    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )
    glutSolidCube(this->dimension);
    glPopMatrix();
}
