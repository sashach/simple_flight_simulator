#ifndef POINT3D_H
#define POINT3D_H


class Point3d
{
public:
    Point3d();
    explicit Point3d(const int _x, const int _y, const int _h);

    const Point3d & operator = (const Point3d & other);

    void update(const int _x, const int _y, const int _h);

    int getX() const;
    int getY() const;
    int getH() const;

private:
    int x;
    int y;
    int h;
};

#endif // POINT3D_H
