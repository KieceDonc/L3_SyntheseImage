#include "Box.h"

/**
 * @brief Construct a new Box:: Box object
 *
 * @param longeur
 * @param largeur
 * @param hauteur
 *
 *     +--------+             Hauteur
 *    /        /|               |
 *   /        / |               |
 *  +--------+  |               | largeur
 *  |        |  |               |    /
 *  |        |  +               |   /
 *  |        | /                |  /
 *  |        |/                 | /
 *  +--------+                  |/_____________ longeur
 *
 * @param translate is an array of 3 float which contains x,y,z translations
 * @param rota is an array of 3 float which contains x,y,z rotations
 * @param colors is an array of 3 float which contains red,green,blue values of colors
 * @param withTexture true = apply current texture, false = don't apply texture
 */
Box::Box(float longeur, float largeur, float hauteur, float translate[3], float rota[3],float colors[3], bool withTexture) : Object(translate,rota,colors,withTexture){
    this->longeur = longeur;
    this->largeur = largeur;
    this->hauteur = hauteur;
    this->draw();
}

/**
 * @brief return longeur
 *
 *     +--------+             Hauteur
 *    /        /|               |
 *   /        / |               |
 *  +--------+  |               | largeur
 *  |        |  |               |    /
 *  |        |  +               |   /
 *  |        | /                |  /
 *  |        |/                 | /
 *  +--------+                  |/_____________ longeur
 *
 * @return float
 */
float Box::getLongeur(){
    return this->longeur;
}

/**
 * @brief return largeur
 *
 *     +--------+             Hauteur
 *    /        /|               |
 *   /        / |               |
 *  +--------+  |               | largeur
 *  |        |  |               |    /
 *  |        |  +               |   /
 *  |        | /                |  /
 *  |        |/                 | /
 *  +--------+                  |/_____________ longeur
 *
 * @return float
 */
float Box::getLargeur(){
    return this->largeur;
}

/**
 * @brief return Hauteur
 *
 *     +--------+             Hauteur
 *    /        /|               |
 *   /        / |               |
 *  +--------+  |               | largeur
 *  |        |  |               |    /
 *  |        |  +               |   /
 *  |        | /                |  /
 *  |        |/                 | /
 *  +--------+                  |/_____________ longeur
 *
 * @return float
 */
float Box::getHauteur(){
    return this->hauteur;
}

/**
 * @brief
 *
 */
void Box::draw(){
    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )

    this->drawSquare(
        new float[3]{-1,1,1},
        new float[3]{-1,-1,1},
        new float[3]{1,-1,1},
        new float[3]{1,1,1}
    );

    this->drawSquare(
        new float[3]{1,1,1},
        new float[3]{1,-1,1},
        new float[3]{1,-1,-1},
        new float[3]{1,1,-1}
    );

    this->drawSquare(
        new float[3]{1,1,-1},
        new float[3]{1,-1,-1},
        new float[3]{-1,-1,-1},
        new float[3]{-1,1,-1}
    );

    this->drawSquare(
        new float[3]{-1,1,-1},
        new float[3]{-1,-1,-1},
        new float[3]{-1,-1,1},
        new float[3]{-1,1,1}
    );

    this->drawSquare(
        new float[3]{-1,1,-1},
        new float[3]{-1,1,1},
        new float[3]{1,1,1},
        new float[3]{1,1,-1}
    );

    this->drawSquare(
        new float[3]{-1,-1,-1},
        new float[3]{-1,-1,1},
        new float[3]{1,-1,1},
        new float[3]{1,-1,-1}
    );

    glPopMatrix();
}

/**
 * @brief use to draw one side of cube ( a square )
 *
 * @param coord0
 * @param coord1
 * @param coord2
 * @param coord3
 *
 *  coord1   coord2
 *    +--------+
 *    |        |
 *    |        |
 *    |        |
 *    |        |
 *    +--------+
 *  coord0   coord3
 */
void Box::drawSquare(float coord0[3],float coord1[3],float coord2[3],float coord3[3]){

    float halfLongeur = this->longeur/2;
    float halfLargeur = this->largeur/2;
    float halfHauteur = this->hauteur/2;

    glBegin(GL_POLYGON);
        if(this->isWithTexture()){
            glTexCoord2f(0.0f,0.0f);
        }
        glVertex3f(coord0[0]*halfLongeur, coord0[1]*halfLargeur, coord0[2]*halfHauteur);

        if(this->isWithTexture()){
            glTexCoord2f(0.0f,1.0f);
        }
        glVertex3f(coord1[0]*halfLongeur,coord1[1]*halfLargeur,coord1[2]*halfHauteur);

        if(this->isWithTexture()){
            glTexCoord2f(1.0f,1.0f);
        }
        glVertex3f(coord2[0]*halfLongeur,coord2[1]*halfLargeur,coord2[2]*halfHauteur);

        if(this->isWithTexture()){
            glTexCoord2f(1.0f,0.0);
        }
        glVertex3f(coord3[0]*halfLongeur,coord3[1]*halfLargeur,coord3[2]*halfHauteur);
    glEnd();
}
