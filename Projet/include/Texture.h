#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdexcept>
#include <jpeglib.h>
#include <jerror.h>
#include <GL/freeglut.h>

class Texture{
    public:
        Texture(char* path);
        virtual ~Texture();

        int width;
        int height;

        int getWidth();
        int getHeight();
        void enableTexture();
    protected:

    private:

};

#endif // TEXTURE_H
