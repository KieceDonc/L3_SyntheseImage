#ifndef CONE_H
#define CONE_H

#include "Object.h"
class Cone : public Object {
    public:
        Cone(float base, float hauteur,float translate[3], float rota[3],float colors[3]);

        float getBase();
        float getHauteur();
        void draw();

    protected:

    private:
        float base;
        float hauteur;
};

#endif // CONE_H
