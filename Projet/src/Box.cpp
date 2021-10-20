#include "Box.h"

Box::Box(float largeur, float longeur, float hauteur, float translate[3], float rota[3], bool withTexture) : Object(translate,rota,withTexture){
    this->largeur = largeur;
    this->longeur = longeur;
    this->hauteur = hauteur;
    this->setColors(new float[3]{0.30f,0.30f,0.30f});
}


float Box::getLargeur(){
    return this->largeur;
}

float Box::getLongeur(){
    return this->longeur;
}

float Box::getHauteur(){
    return this->hauteur;
}

void Box::draw(){
    glPushMatrix();
    this->onDraw(); // on draw must be call before drawing. ( contains translation / rotation / colors ... )

    float halfLargeur = this->largeur/2;
    float halfLongeur = this->longeur/2;
    float halfHauteur = this->hauteur/2;
    this->drawOneSide(
        new float[3]{-1*halfLargeur,halfLongeur,halfHauteur},
        new float[3]{-1*halfLargeur,-1*halfLongeur,halfHauteur},
        new float[3]{halfLargeur,-1*halfLongeur,halfHauteur},
        new float[3]{halfLargeur,halfLongeur,halfHauteur}
    );

    this->drawOneSide(
        new float[3]{halfLargeur,halfLongeur,halfHauteur},
        new float[3]{halfLargeur,-1*halfLongeur,halfHauteur},
        new float[3]{halfLargeur,-1*halfLongeur,-1*halfHauteur},
        new float[3]{halfLargeur,halfLongeur,-1*halfHauteur}
    );

    this->drawOneSide(
        new float[3]{halfLargeur,halfLongeur,-1*halfHauteur},
        new float[3]{halfLargeur,-1*halfLongeur,-1*halfHauteur},
        new float[3]{-1*halfLargeur,-1*halfLongeur,-1*halfHauteur},
        new float[3]{-1*halfLargeur,halfLongeur,-1*halfHauteur}
    );

    this->drawOneSide(
        new float[3]{-1*halfLargeur,halfLongeur,-1*halfHauteur},
        new float[3]{-1*halfLargeur,-1*halfLongeur,-1*halfHauteur},
        new float[3]{-1*halfLargeur,-1*halfLongeur,halfHauteur},
        new float[3]{-1*halfLargeur,halfLongeur,halfHauteur}
    );

    this->drawOneSide(
        new float[3]{-1*halfLargeur,halfLongeur,-1*halfHauteur},
        new float[3]{-1*halfLargeur,halfLongeur,halfHauteur},
        new float[3]{halfLargeur,halfLongeur,halfHauteur},
        new float[3]{halfLargeur,halfLongeur,-1*halfHauteur}
    );

    this->drawOneSide(
        new float[3]{-1*halfLargeur,-1*halfLongeur,-1*halfHauteur},
        new float[3]{-1*halfLargeur,-1*halfLongeur,halfHauteur},
        new float[3]{halfLargeur,-1*halfLongeur,halfHauteur},
        new float[3]{halfLargeur,-1*halfLongeur,-1*halfHauteur}
    );

    glPopMatrix();
}

void Box::drawOneSide(float coord0[3],float coord1[3],float coord2[3],float coord3[3]){
    glBegin(GL_POLYGON);
        if(this->isWithTexture()){
            glTexCoord2f(0.0f,0.0f);
        }
        glVertex3f(coord0[0], coord0[1], coord0[2]);

        if(this->isWithTexture()){
            glTexCoord2f(0.0f,1.0f);
        }
        glVertex3f(coord1[0],coord1[1],coord1[2]);

        if(this->isWithTexture()){
            glTexCoord2f(1.0f,1.0f);
        }
        glVertex3f(coord2[0],coord2[1],coord2[2]);

        if(this->isWithTexture()){
            glTexCoord2f(1.0f,0.0);
        }
        glVertex3f(coord3[0],coord3[1],coord3[2]);
    glEnd();
}
