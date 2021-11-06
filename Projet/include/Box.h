#ifndef BOX_H
#define BOX_H

#include "Object.h"

/**
 * @brief
 *
 */
class Box : public Object {
    public:
        Box(float largeur, float longeur, float hauteur, float translate[], float rota[], float colors[],bool withTexture);

        float getLargeur();
        float getLongeur();
        float getHauteur();

    protected:

    private:
        float largeur;
        float longeur;
        float hauteur;

        void draw();
        void drawSquare(float coord0[3],float coord1[3],float coord2[3],float coord3[3]);
};

#endif // BOX_H
