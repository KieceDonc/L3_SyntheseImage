#include "point.h"

Point::milieu(Point pa, Point pb, float r, float g, float b){
    Point pc = Point();

    pc.x = (pa.x+pb.x)/2;
    pc.y = (pa.y+pb.y)/2;
    pc.z = (pa.z+pb.z)/2;


    pc.r = r;
    pc.g = g;
    pc.b = b;

    return pc;
}
