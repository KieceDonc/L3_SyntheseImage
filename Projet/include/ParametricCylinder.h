#ifndef PARAMETRICCYLINDER_H
#define PARAMETRICCYLINDER_H

#include <cmath>
#include "Object.h"
#include "Texture.h"

class ParametricCylinder : public Object {
    public:
        ParametricCylinder(float rayon, float hauteur, int precision, float translate[], float rota[], bool withTexture);

        float getRayon();
        float getHauteur();
        int getPrecision();

        void draw();

    protected:

    private:
        float rayon;
        float hauteur;
        int precision;
};

#endif // PARAMETRICCYLINDER_H
