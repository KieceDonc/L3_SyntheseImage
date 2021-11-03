#ifndef PARAMETRICCYLINDER_H
#define PARAMETRICCYLINDER_H

#include <cmath>
#include "Object.h"
#include "Texture.h"

class ParametricCylinder : public Object {
    public:
        ParametricCylinder(float rayon, float hauteur, int precision, float translate[], float rota[], float colors[], bool withTexture);

        float getRayon();
        float getHauteur();
        int getPrecision();

    protected:

    private:
        float rayon;
        float hauteur;
        int precision;

        void draw();
};

#endif // PARAMETRICCYLINDER_H
