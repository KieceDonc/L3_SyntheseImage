#include "Cone.h"

/**
 * @brief Construct a new Cone:: Cone object
 *
 * @param base
 * @param hauteur
 * @param translate is an array of 3 float which contains x,y,z translations
 * @param rota is an array of 3 float which contains x,y,z rotations
 * @param colors is an array of 3 float which contains red,green,blue values of colors
 */
Cone::Cone(float base, float hauteur,float translate[3], float rota[3],float colors[3]) : Object(translate,rota,colors,false){
    this->base = base;
    this->hauteur = hauteur;
    this->draw();
}

/**
 * @brief
 *
 * @return float
 */
float Cone::getBase(){
    return this->base;
}

/**
 * @brief
 *
 * @return float
 */
float Cone::getHauteur(){
    return this->hauteur;
}

/**
 * @brief will draw the cone
 *
 */
void Cone::draw(){
    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )

    glutSolidCone(this->getBase(),this->getHauteur(),20,20);

    glPopMatrix();
}
