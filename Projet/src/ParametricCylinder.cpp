#include "ParametricCylinder.h"

/**
 * @brief Construct a new Parametric Cylinder:: Parametric Cylinder object
 *
 * @param rayon
 * @param hauteur
 *
 *               rayon
 *           <---------->
 *    ^          888888888888888
 *    |       8888             8888
 *    |      8                     8
 *    |      88888             88888
 *    |      8   888888888888888   8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8   888888888888888   8
 *    |      8888               8888
 *    |      8                     8
 *    |       8888             8888
 *    |          888888888888888
 *  hauteur
 *
 * @param precision. Because we use parametric equation it describe the numbers of faces we will have. Use 30 if you want to have the illusion of a cylinder
 * @param translate is an array of 3 float which contains x,y,z translations
 * @param rota is an array of 3 float which contains x,y,z rotationss
 * @param colors is an array of 3 float which contains red,green,blue values of colors
 * @param withTexture true = apply current texture, false = don't apply texture
 */
ParametricCylinder::ParametricCylinder(float rayon, float hauteur, int precision, float translate[3], float rota[3], float colors[3], bool withTexture) : Object(translate,rota,colors,withTexture){
    this->rayon = rayon;
    this->hauteur = hauteur;
    this->precision = precision;
    this->draw();
}

/**
 * @brief return rayon
 *
 *               rayon
 *           <---------->
 *    ^          888888888888888
 *    |       8888             8888
 *    |      8                     8
 *    |      88888             88888
 *    |      8   888888888888888   8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8   888888888888888   8
 *    |      8888               8888
 *    |      8                     8
 *    |       8888             8888
 *    |          888888888888888
 *  hauteur
 *
 * @return float
 */

float ParametricCylinder::getRayon(){
    return this->rayon;
}

/**
 * @brief return hauteur
 *
 *               rayon
 *           <---------->
 *    ^          888888888888888
 *    |       8888             8888
 *    |      8                     8
 *    |      88888             88888
 *    |      8   888888888888888   8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8                     8
 *    |      8   888888888888888   8
 *    |      8888               8888
 *    |      8                     8
 *    |       8888             8888
 *    |          888888888888888
 *  hauteur
 *
 * @return float
 */
float ParametricCylinder::getHauteur(){
    return this->hauteur;
}

/**
 * @brief
 *
 * @return int
 */
int ParametricCylinder::getPrecision(){
    return this->precision;
}

/**
 * @brief
 *
 */
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

    // drawing the lower part to close the cylinder
    glBegin(GL_POLYGON);
    for (int t = 0; t <this->getPrecision(); t++) {
        float x0 = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
        float z0 = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());
        glVertex3d(x0,0,z0);
    }
    glEnd();

    // drawing the upper part to close the cylinder
    glBegin(GL_POLYGON);
    for (int t = 0; t <this->getPrecision(); t++) {
        float x0 = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
        float z0 = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());
        glVertex3d(x0,this->getHauteur(),z0);
    }
    glEnd();

    glPopMatrix();


}
