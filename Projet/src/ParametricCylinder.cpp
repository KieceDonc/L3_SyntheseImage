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
 * @brief will draw the parametric cylinder
 *
 */
void ParametricCylinder::draw(){

    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )

    float pointsX[this->getPrecision()+1];
    float pointsZ[this->getPrecision()+1];

    for (int t = 0; t < this->getPrecision()+1; t++) {
        pointsX[t] = this->getRayon()*cos(2*this->getPi()*t/this->getPrecision());
        pointsZ[t] = this->getRayon()*sin(2*this->getPi()*t/this->getPrecision());
    }

    for (int t = 0; t <this->getPrecision(); t++) {
        glBegin(GL_POLYGON);

        float t0 = (float)t/(this->getPrecision()+1);
        float t1 = (t+1.0f)/(this->getPrecision()+1);

        if(this->isWithTexture()){
            glTexCoord2f(t0,0.0f);
        }
        glVertex3d(pointsX[t],0,pointsZ[t]);

        if(this->isWithTexture()){
            glTexCoord2f(t0,1.0f);
        }
        glVertex3d(pointsX[t],this->getHauteur(),pointsZ[t]);

        if(this->isWithTexture()){
            glTexCoord2f(t1,1.0f);
        }
        glVertex3d(pointsX[t+1],this->getHauteur(),pointsZ[t+1]);

        if(this->isWithTexture()){
            glTexCoord2f(t1,0.0f);
        }
        glVertex3d(pointsX[t+1],0,pointsZ[t+1]);

        glEnd();
    }

    // drawing the lower part to close the cylinder
    glBegin(GL_POLYGON);
    for (int t = 0; t <this->getPrecision(); t++) {
        glVertex3d(pointsX[t],0,pointsZ[t]);
    }
    glEnd();

    // drawing the upper part to close the cylinder
    glBegin(GL_POLYGON);
    for (int t = 0; t <this->getPrecision(); t++) {
        glVertex3d(pointsX[t],this->getHauteur(),pointsZ[t]);
    }
    glEnd();

    glPopMatrix();


}
