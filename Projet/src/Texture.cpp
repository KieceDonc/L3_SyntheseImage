#include "Texture.h"
#include <iostream>

/**
 * @brief Construct a new Texture:: Texture object. It will load and store texture but not use them. Call enableTexture() to use it
 *
 * @param path to jpg texture
 */
Texture::Texture(char* path){
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    #ifdef __WIN32
    if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
    #elif __GNUC__
    if ((file = fopen(path,"rb")) == 0){
      throw std::runtime_error("Erreur : impossible d'ouvrir le fichier texture.jpg\n");
    }
    #endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);
    this->width = cinfo.image_width;
    this->height = cinfo.image_height;
    if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
        throw std::runtime_error("Erreur : l'image doit etre de type RGB\n");
    }

    jpeg_start_decompress(&cinfo);
    unsigned char image[this->height*this->width*3];

    unsigned char * ligne = image;
    while (cinfo.output_scanline<cinfo.output_height){
      ligne=image+3*this->getWidth()*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    for(int x=0;x<this->getWidth();x++){
        for(int y=0;y<this->getHeight();y++){
            this->texture[x][y][0]=image[x*this->getWidth()*3+y*3];
            this->texture[x][y][1]=image[x*this->getWidth()*3+y*3+1];;
            this->texture[x][y][2]=image[x*this->getWidth()*3+y*3+2];;
        }
    }
}

/**
 * @brief use to set the current texture in general to this stored texture
 *
 */
void Texture::enableTexture(){
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,this->getWidth(),this->getHeight(),0, GL_RGB,GL_UNSIGNED_BYTE,this->texture);
}

/**
 * @brief return height of loaded texture
 *
 * @return int
 */
int Texture::getHeight(){
    return this->height;
}

/**
 * @brief return width of loaded texture
 *
 * @return int
 */
int Texture::getWidth(){
    return this->width;
}
