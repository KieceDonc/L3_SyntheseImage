#include "Point.h"

Point::Point(){
    this->x=0;
    this->y=0;
    this->z=0;

    this->r=0;
    this->g=0;
    this->b=0;
}

Point::Point(double x, double y, double z, float r, float g, float b){
    this->x=x;
    this->y=y;
    this->z=z;

    this->r=r;
    this->g=g;
    this->b=b;
}

Point Point::milieu(Point pa, Point pb, float r, float g, float b){
    Point pc = Point();

    pc.x = (pa.x+pb.x)/2;
    pc.y = (pa.y+pb.y)/2;
    pc.z = (pa.z+pb.z)/2;


    pc.r = r;
    pc.g = g;
    pc.b = b;

    return pc;
}
