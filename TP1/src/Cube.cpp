#include "Cube.h"
#include "Point.h"
// Tableau pour stocker les sommets du cube et leur couleur
Point cPoints[8]={
    {-0.5,-0.5, 0.5,1.0,0.0,0.0},
    { 0.5, -0.5, 0.5,0.0,1.0,0.0},
    { 0.5, -0.5, -0.5,0.0,0.0,1.0},
    { -0.5, -0.5, -0.5,1.0,1.0,1.0},
    { -0.5,0.5, 0.5,1.0,0.0,0.0},
    { 0.5, 0.5, 0.5,0.0,1.0,0.0},
    { 0.5, 0.5, -0.5,0.0,0.0,1.0},
    { -0.5, 0.5, -0.5,1.0,1.0,1.0}
};

//Tableau pour stocker les indices des sommets par face pour le cube
int cFaces[6][4]={
  {0,1,2,3},//face envers endroit={0,3,2,1}
  {0,1,5,4},
  {1,2,6,5},
  {2,3,7,6},
  {0,4,7,3},
  {4,5,6,7}
};
