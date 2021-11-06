#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>
#include <stdexcept>
#include <cmath>

/**
 * @brief 
 * 
 */
class Object{
    public:
        Object(float translate[], float rota[], float colors[], bool withTexture);
        ~Object();

        bool isWithTexture();
        float getTranslate(int index);
        float getRota(int index);
        float getColors(int index);
        float getPi();

    protected:
        void onDraw();

    private:
        bool withTexture;
        float * translate;
        float * rota;
        float * colors;
};

#endif // OBJECT_H
