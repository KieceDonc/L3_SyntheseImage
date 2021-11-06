#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdexcept>
#include <jpeglib.h>
#include <jerror.h>
#include <GL/freeglut.h>

/**
 * @brief 
 * 
 */
class Texture{
    public:
        Texture(char* path);

        int width;
        int height;

        int getWidth();
        int getHeight();
        void enableTexture();

    private:
        unsigned char texture[256][256][3];

};

#endif // TEXTURE_H
