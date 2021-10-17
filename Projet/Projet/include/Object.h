#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>
#include <stdexcept>
#include <cmath>

class Object{
    public:
        Object(float translate[], float rota[]);
        ~Object();

        float getTranslate(int index);
        float getRota(int index);
        float getColors(int index);
        float getPi();
        void setColors(float colors[]);

    protected:
        void onDraw();

    private:
        bool colorsHasBeenSet;
        float * translate;
        float * rota;
        float * colors;
};

#endif // OBJECT_H
