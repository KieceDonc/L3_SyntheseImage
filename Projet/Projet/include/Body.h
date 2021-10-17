#ifndef BODY_H
#define BODY_H

#include <cmath>
#include "Object.h"


class Body : public Object {
    public:
        Body(float rayon, float hauteur, int precision, float translate[], float rota[]);

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

#endif // BODY_H
