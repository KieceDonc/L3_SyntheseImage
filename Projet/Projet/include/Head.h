#ifndef HEAD_H
#define HEAD_H

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Object.h"

class Head : public Object {
    public:
        Head(float dimension, float translate[], float rota[]);

        float getDimension();
        void draw();

    protected:

    private:
        float dimension;
};

#endif // HEAD_H
