#ifndef POINT_H
#define POINT_H

class Point
{
    public:
        Point();
        Point(double x, double y, double z, float r, float g, float b);

        //coordonnées x, y et z du point
        double x;
        double y;
        double z;

        // couleur r, v et b du point
        float r;
        float g;
        float b;

        static Point milieu(Point pa, Point pb, float r, float g, float b);
    protected:

    private:
};

#endif // POINT_H
