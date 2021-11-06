#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Object.h"

/**
 * @brief 
 * 
 */
class Sphere : public Object {
    public:
        Sphere(float rayon, float translate[], float colors[]);

        float getRayon();

    protected:

    private:
        float rayon;

        void draw();
};

#endif // SPHERE_H
