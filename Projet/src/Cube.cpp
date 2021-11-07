#include "Cube.h"

/**
 * @brief Construct a new Cube:: Cube object
 *
 * @param dimension ( size of cube )
 * @param translate is an array of 3 float which contains x,y,z translations
 * @param rota is an array of 3 float which contains x,y,z rotations
 * @param colors is an array of 3 float which contains red,green,blue values of colors
 */
Cube::Cube(float dimension, float translate[3], float rota[3],float colors[3]) : Object(translate,rota,colors,false){
    this->dimension = dimension;
    this->draw();
}

/**
 * @brief return dimension ( size of cube )
 *
 * @return float
 */
float Cube::getDimension(){
    return this->dimension;
}

/**
 * @brief will draw the cube
 *
 */
void Cube::draw(){
    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )
    glutSolidCube(this->dimension);
    glPopMatrix();
}
