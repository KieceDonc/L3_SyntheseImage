#ifndef POINT_H
#define POINT_H


class point
{
    public:
        point();
        virtual ~point();

        //coordonnées x, y et z du point
        double x;
        double y;
        double z;

        // couleur r, v et b du point
        float r;
        float g;
        float b;

        Point milieu(Point pa, Point pb, float r, float g, float b);
};

#endif // POINT_H
