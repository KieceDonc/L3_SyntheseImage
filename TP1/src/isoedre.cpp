#include "isoedre.h"
#include "cube.h"

Point pointsIsoedre[12]={
    {milieu(pCube[0],pCube[1],1.0,0.0,0.0)},
    {milieu(pCube[1],pCube[2],1.0,1.0,0.0)},
    {milieu(pCube[2],pCube[3],1.0,0.0,1.0)},
    {milieu(pCube[3],pCube[0],0.0,0.0,0.0)},
    {milieu(pCube[0],pCube[4],0.0,1.0,0.0)},
    {milieu(pCube[1],pCube[5],0.0,0.0,1.0)},
    {milieu(pCube[2],pCube[6],1.0,1.0,1.0)},
    {milieu(pCube[3],pCube[7],1.0,0.0,0.0)},
    {milieu(pCube[4],pCube[5],1.0,0.0,0.0)},
    {milieu(pCube[5],pCube[6],1.0,0.0,0.0)},
    {milieu(pCube[6],pCube[7],1.0,0.0,0.0)},
    {milieu(pCube[7],pCube[4],1.0,0.0,0.0)}
};

int facesIsoedre[20][3]={
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
