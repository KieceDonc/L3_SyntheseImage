#ifndef BEZIERWING_H
#define BEZIERWING_H

#include "Object.h"
#include <cmath>

class BezierWing : public Object{
    public:
        BezierWing(float dimension, int precision, bool symmetricalCall, float translate[], float rota[], float colors[]);
        virtual ~BezierWing();

        bool getSymmetricalCall();
        float getScale();
        int getPrecision();

        static float getHauteur();
    protected:

    private:
        bool symmetricalCall;
        float scale;
        int precision;

        void draw();
};

#endif // BEZIERWING_H
