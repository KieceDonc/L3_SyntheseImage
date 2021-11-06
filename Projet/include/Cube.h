#ifndef Cube_H
#define Cube_H

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Object.h"

/**
 * @brief 
 * 
 */
class Cube : public Object {
    public:
        Cube(float dimension, float translate[], float rota[], float colors[]);

        float getDimension();

    protected:

    private:
        float dimension;

            void draw();
};

#endif // BOX_H
