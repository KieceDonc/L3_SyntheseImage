#include "Sphere.h"

/**
 * @brief Construct a new Sphere:: Sphere object
 *
 * @param rayon
 * @param translate is an array of 3 float which contains x,y,z translations
 * @param colors is an array of 3 float which contains red,green,blue values of colors
 */
Sphere::Sphere(float rayon, float translate[3],float colors[3]) : Object(translate,new float[3]{0.0f,0.0f,0.0f},colors,false){
    this->rayon = rayon;
    this->draw();
}

/**
 * @brief
 *
 * @return float
 */
float Sphere::getRayon(){
    return this->rayon;
}

/**
 * @brief will draw the sphere object
 *
 */
void Sphere::draw(){
    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )
    glutSolidSphere(this->rayon,20,20);
    glPopMatrix();
}
