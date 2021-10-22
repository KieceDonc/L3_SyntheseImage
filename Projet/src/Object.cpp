#include "Object.h"

Object::Object(float translate[], float rota[], float colors[], bool withTexture){
    this->withTexture = withTexture;

    if(translate==nullptr){
        throw std::runtime_error("null pointer exception : translate is null. Did you forgot to set translation in constructor ?");
    }else if(std::isnan(translate[0])||std::isnan(translate[1])||std::isnan(translate[2])){
        throw std::runtime_error("translate contain a floating point number who's not a number");
    }

    this->translate = translate;

    if(rota==nullptr){
        throw std::runtime_error("null pointer exception : rota is null. Did you forgot to set translation in constructor ?");
    }else if(std::isnan(rota[0])||std::isnan(rota[1])||std::isnan(rota[2])){
        throw std::runtime_error("rota contain a floating point number who's not-a-number");
    }
    this->rota = rota;

    if(colors==nullptr){
        throw std::runtime_error("null pointer exception : colors is null. Did you forgot to set colors in constructor ?");
    }else if(std::isnan(colors[0])||std::isnan(colors[1])||std::isnan(colors[2])){
        throw std::runtime_error("colors contain a floating point number who's not-a-number");
    }

    this->colors = colors;
}

Object::~Object(){
    delete[] this->colors;
    delete[] this->translate;
    delete[] this->rota;
}

void Object::onDraw(){
    glTranslatef(this->getTranslate(0),this->getTranslate(1),this->getTranslate(2));
    glRotatef(this->getRota(0),1.0f,0.0f,0.0f);
    glRotatef(this->getRota(1),0.0f,1.0f,0.0f);
    glRotatef(this->getRota(2),0.0f,0.0f,1.0f);
    glColor3f(this->getColors(0),this->getColors(1),this->getColors(2));
}

bool Object::isWithTexture(){
    return this->withTexture;
}

float Object::getTranslate(int index){
    if(index>2 || index<0){
        throw std::runtime_error("out of bound in getTranslate");
    }
    return this->translate[index];
}

float Object::getRota(int index){
    if(index>2 || index<0){
        throw std::runtime_error("out of bound in getTranslate");
    }
    return this->rota[index];
}

float Object::getColors(int index){
    if(index>2 || index<0){
        throw std::runtime_error("out of bound in getTranslate");
    }
    return this->colors[index];
}

float Object::getPi(){
    return 3.141592653589793;
}
