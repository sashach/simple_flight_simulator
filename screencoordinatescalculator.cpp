#include "screencoordinatescalculator.h"
#include "flightsmodel.h"
#include "constants.h"

ScreenCoordinatesCalculator::ScreenCoordinatesCalculator():
    scale(0.0),
    drawingWidth(0),
    drawingHeight(0)
{

}

int ScreenCoordinatesCalculator::getScreenX(const int relX) const
{
    return relX * scale;
}

int ScreenCoordinatesCalculator::getScreenY(const int relY) const
{
    return drawingHeight - relY * scale;
}

void ScreenCoordinatesCalculator::updateScale(const int width, const int height)
{
    drawingWidth = width;
    drawingHeight = height;

    scale = 1.0 * drawingWidth / WORLD_SIZE;
}
