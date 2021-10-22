#ifndef Cube_H
#define Cube_H

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Object.h"

class Cube : public Object {
    public:
        Cube(float dimension, float translate[], float rota[], float colors[], bool withTexture);

        float getDimension();
        void draw();

    protected:

    private:
        float dimension;
};

#endif // BOX_H
