#include "Isoedre.h"
#include "Point.h"
#include "Cube.h"

Point isoPoints[12]={
    Point::milieu(cPoints[0],cPoints[1],1.0,0.0,0.0),
    Point::milieu(cPoints[1],cPoints[2],1.0,1.0,0.0),
    Point::milieu(cPoints[2],cPoints[3],1.0,0.0,1.0),
    Point::milieu(cPoints[3],cPoints[0],0.0,0.0,0.0),
    Point::milieu(cPoints[0],cPoints[4],0.0,1.0,0.0),
    Point::milieu(cPoints[1],cPoints[5],0.0,0.0,1.0),
    Point::milieu(cPoints[2],cPoints[6],1.0,1.0,1.0),
    Point::milieu(cPoints[3],cPoints[7],1.0,0.0,0.0),
    Point::milieu(cPoints[4],cPoints[5],1.0,0.0,0.0),
    Point::milieu(cPoints[5],cPoints[6],1.0,0.0,0.0),
    Point::milieu(cPoints[6],cPoints[7],1.0,0.0,0.0),
    Point::milieu(cPoints[7],cPoints[4],1.0,0.0,0.0)
};

int isoFaces[20][3]={
    {0,1,2},
    {0,2,3},
    {0,5,4},
    {4,5,8},
    {1,9,5},
    {1,6,9},
    {2,6,7},
    {10,7,6},
    {3,7,11},
    {3,11,4},
    {8,10,11},
    {8,9,10},
    {0,4,3},
    {0,1,5},
    {1,6,2},
    {3,2,7},
    {4,8,11},
    {5,9,8},
    {6,10,9},
    {7,10,11},
};
