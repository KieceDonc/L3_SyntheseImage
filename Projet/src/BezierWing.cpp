#include "BezierWing.h"

/**
 * @brief Construct a new Bezier Wing:: Bezier Wing object
 *
 * @param scale
 * @param precision
 * @param symmetricalCall
 * @param translate is an array of 3 float which contains x,y,z translations
 * @param rota is an array of 3 float which contains x,y,z rotations
 * @param colors is an array of 3 float which contains red,green,blue values of colors
 */
BezierWing::BezierWing(float scale, int precision, bool symmetricalCall, float translate[], float rota[], float colors[]) : Object(translate,rota,colors,false){
    this->scale = scale;
    this->precision = precision;
    this->symmetricalCall = symmetricalCall;
    this->draw();
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool BezierWing::getSymmetricalCall(){
    return this->symmetricalCall;
}

/**
 * @brief
 *
 * @return float
 */
float BezierWing::getScale(){
    return this->scale;
}

/**
 * @brief
 *
 * @return int
 */
int BezierWing::getPrecision(){
    return this->precision;
}

/**
 * @brief
 *
 * @return float
 */
float BezierWing::getHauteur(){
    return 0.4f;
}

/**
 * @brief
 *
 */
void BezierWing::draw(){
    glPushMatrix();
    this->onDraw();

    // Bezier control points ( 0 = first curve, 1 = second curve )
    float courbeBezier0[4][2] = {{0.0f,0.0f},{2.5f,0.0f},{2.0f,1.0f},{3.0f,2.0f}};
    float courbeBezier1[4][2] = {{3.0f,2.0f},{0.5f,2.25f},{0.0f,2.0f},{0.0f,0.0f}};

    // points have been create with max x and y of 3.0. So we divide every bezier points by 3.0
    float constToMultiple = this->getScale()/3.0f;

    // we multiple every bezier points by the constante
    for(int x=0 ;x < 4;x++){
        for(int y = 0;y < 2;y++){
            if(this->getSymmetricalCall() && y==1){
                // If we want symetrical (if symmetricalCall is set to true) wings we will have to multiple by -1 y coordinate one of wings
                courbeBezier0[x][y]*=constToMultiple*-1;
                courbeBezier1[x][y]*=constToMultiple*-1;
            }else{
                courbeBezier0[x][y]*=constToMultiple;
                courbeBezier1[x][y]*=constToMultiple;
            }
        }
    }

    // We store points at T = const ( we do that because we use them at different places so we don't have to recalculate them )
    float points0Bezier[this->getPrecision()][2];
    float points1Bezier[this->getPrecision()][2];

    // We evaluate bezier points at a certain T
    for(int t = 0;t<this->getPrecision();t++){
        float currentT = (t+0.0f)/this->getPrecision();
        points0Bezier[t][0] = courbeBezier0[0][0]*std::pow((1-currentT),3)+3*courbeBezier0[1][0]*currentT*std::pow((1-currentT),2)+3*courbeBezier0[2][0]*std::pow(currentT,2)*(1-currentT)+courbeBezier0[3][0]*std::pow(currentT,3);
        points0Bezier[t][1] = courbeBezier0[0][1]*std::pow((1-currentT),3)+3*courbeBezier0[1][1]*currentT*std::pow((1-currentT),2)+3*courbeBezier0[2][1]*std::pow(currentT,2)*(1-currentT)+courbeBezier0[3][1]*std::pow(currentT,3);

        points1Bezier[t][0] = courbeBezier1[0][0]*std::pow((1-currentT),3)+3*courbeBezier1[1][0]*currentT*std::pow((1-currentT),2)+3*courbeBezier1[2][0]*std::pow(currentT,2)*(1-currentT)+courbeBezier1[3][0]*std::pow(currentT,3);
        points1Bezier[t][1] = courbeBezier1[0][1]*std::pow((1-currentT),3)+3*courbeBezier1[1][1]*currentT*std::pow((1-currentT),2)+3*courbeBezier1[2][1]*std::pow(currentT,2)*(1-currentT)+courbeBezier1[3][1]*std::pow(currentT,3);
    }

    glColor3f(0.5f,0.5f,0.5f);

    // drawing inferior part
    glBegin(GL_POLYGON);
        for(int t = 0;t<this->getPrecision();t++){
            glVertex3f(points0Bezier[t][0],0,points0Bezier[t][1]);
        }

        for(int t = 0;t<this->getPrecision();t++){
            glVertex3f(points1Bezier[t][0],0,points1Bezier[t][1]);
        }
    glEnd();

    glColor3f(1.0f,1.0f,1.0f);

    // drawing upper part
    glBegin(GL_POLYGON);
        for(int t = 0;t<this->getPrecision();t++){
            glVertex3f(points0Bezier[t][0],this->getHauteur(),points0Bezier[t][1]);
        }
        for(int t = 0;t<precision;t++){
            glVertex3f(points1Bezier[t][0],this->getHauteur()/3,points1Bezier[t][1]);
        }
    glEnd();


    glColor3f(1.0f,1.0f,0.0f);

    // drawing of the side of the second curve
    for(int t = 0;t<this->getPrecision()-1;t++){
        glBegin(GL_POLYGON);
            glVertex3f(points0Bezier[t][0],0,points0Bezier[t][1]);
            glVertex3f(points0Bezier[t][0],this->getHauteur(),points0Bezier[t][1]);
            glVertex3f(points0Bezier[t+1][0],this->getHauteur(),points0Bezier[t+1][1]);
            glVertex3f(points0Bezier[t+1][0],0,points0Bezier[t+1][1]);
        glEnd();
    }

    glColor3f(0.0f,1.0f,1.0f);

    // drawing of the side of the first curve
    for(int t = 0;t<precision-1;t++){
        glBegin(GL_POLYGON);
            glVertex3f(points1Bezier[t][0],0,points1Bezier[t][1]);
            glVertex3f(points1Bezier[t][0],this->getHauteur()/3,points1Bezier[t][1]);
            glVertex3f(points1Bezier[t+1][0],this->getHauteur()/3,points1Bezier[t+1][1]);
            glVertex3f(points1Bezier[t+1][0],0,points1Bezier[t+1][1]);
        glEnd();
    }
    glPopMatrix();
}
