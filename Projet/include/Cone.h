#ifndef CONE_H
#define CONE_H

#include "Object.h"
class Cone : public Object {
    public:
        Cone(float base, float hauteur,float translate[3], float rota[3],float colors[3]);

        float getBase();
        float getHauteur();

    protected:

    private:
        float base;
        float hauteur;

        void draw();
};

#endif // CONE_H
