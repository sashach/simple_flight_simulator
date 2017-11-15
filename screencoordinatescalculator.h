#ifndef SCREENCOORDINATESCALCULATOR_H
#define SCREENCOORDINATESCALCULATOR_H


class ScreenCoordinatesCalculator
{
public:
    ScreenCoordinatesCalculator();

    void updateScale(const int width, const int height);

    int getScreenX(const int relX) const;
    int getScreenY(const int relY) const;

private:
    double scale;
    int drawingWidth;
    int drawingHeight;
};

#endif // SCREENCOORDINATESCALCULATOR_H
