#include "Cube.h"

Cube::Cube(float dimension, float translate[3], float rota[3],float colors[3]) : Object(translate,rota,colors,false){
    this->dimension = dimension;
    this->draw();
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
