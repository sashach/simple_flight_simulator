#include "flightsview.h"
#include "flightmodel.h"
#include "flight.h"

#include <QPainter>

static const int LINES_WIDTH = 2;
static const int POINTS_WIDTH = 5;
static const int FLIGHT_CROSS_SIZE = 5;
static const int POINT_NAMES_OFFSET = 10;
static const QBrush BACKGROUND_BRUSH = QBrush(QColor(200, 200, 200));
static const QPen PEN_PASSED_ROUTE = QPen(QColor(20, 20, 90), LINES_WIDTH);
static const QPen PEN_NON_PASSED_ROUTE = QPen(QColor(90, 90, 220), LINES_WIDTH);
static const QPen PEN_POINTS = QPen(QColor(240, 240, 70), POINTS_WIDTH);
static const QPen PEN_POINTS_NAMES = QPen(QColor(240, 240, 70));
static const QPen PEN_FLIGHT = QPen(QColor(20, 180, 40), LINES_WIDTH);

FlightsView::FlightsView(FlightModel &model, QWidget *parent) :
    QDialog(parent),
    flightsModel(model),
    drawingWidth(0),
    drawingHeight(0),
    scale(0.0)
{
    setWindowTitle("Flights View");
}

void FlightsView::onModelUpdated()
{
    flightsPO.clearFlights();

    const QVector<Flight> & flights = flightsModel.getFlights();
    for(auto it = flights.begin(); it != flights.end(); ++it)
    {
        flightsPO.addFlight(*it);
    }

    update();
}

void FlightsView::resizeEvent(QResizeEvent*)
{
    drawingWidth = width();
    drawingHeight = height();

    scale = 1.0 * drawingWidth / FlightModel::WORLD_SIZE;

    onModelUpdated();
}

void FlightsView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect base(0, 0, drawingWidth, drawingHeight);
    painter.fillRect(base, BACKGROUND_BRUSH);

    drawLinesPoints(painter);
    drawPointsNames(painter);
    drawFlights(painter);
}

void FlightsView::drawLinesPoints(QPainter & painter)
{
    const QVector<Flight> & flights = flightsModel.getFlights();

    QVector <QPoint> points;
    QVector <QLine> passedLines, nonPassedLines;

    points.reserve(Flight::MAX_FLIGHT_POINTS * flights.size());
    passedLines.reserve(points.capacity() / 2);
    nonPassedLines.reserve(points.capacity() / 2);

    for(auto flightIt = flights.begin(); flightIt != flights.end(); ++flightIt)
    {
        const QVector<WayPoint> & wayPoints = flightIt->getWayPoints();

        bool firstPoint = true;
        int prevX = 0, prevY = 0;
        bool prevPointPassed = false;

        for(auto pointIt = wayPoints.begin(); pointIt != wayPoints.end(); ++pointIt)
        {
            int x = getScreenX(pointIt->getX());
            int y = getScreenY(pointIt->getY());
            points.push_back(QPoint(x, y));

            if(!firstPoint)
            {
                if(prevPointPassed)
                {
                    passedLines.push_back(QLine(prevX, prevY, x, y));
                }
                else
                {
                    nonPassedLines.push_back(QLine(prevX, prevY, x, y));
                }
            }
            prevX = x;
            prevY = y;
            prevPointPassed = pointIt->isPassed();
            firstPoint = false;
        }
    }

    painter.setPen(PEN_NON_PASSED_ROUTE);
    painter.drawLines(nonPassedLines);

    painter.setPen(PEN_PASSED_ROUTE);
    painter.drawLines(passedLines);

    painter.setPen(PEN_POINTS);
    painter.drawPoints(points.data(), points.size());
}

void FlightsView::drawPointsNames(QPainter & painter)
{
    painter.setPen(PEN_POINTS_NAMES);

    const QVector<Flight> & flights = flightsModel.getFlights();
    for(auto flightIt = flights.begin(); flightIt != flights.end(); ++flightIt)
    {
        const QVector<WayPoint> & wayPoints = flightIt->getWayPoints();
        for(auto pointIt = wayPoints.begin(); pointIt != wayPoints.end(); ++pointIt)
        {
            int x = POINT_NAMES_OFFSET + getScreenX(pointIt->getX());
            int y = POINT_NAMES_OFFSET + getScreenY(pointIt->getY());

            painter.drawText(QPoint(x, y), pointIt->getName());
        }
    }
}

void FlightsView::drawFlights(QPainter & painter)
{
    const QVector<Flight> & flights = flightsModel.getFlights();

    QVector <QLine> flightsSymbols;
    flightsSymbols.reserve(2 * flights.size());

    for(auto flightIt = flights.begin(); flightIt != flights.end(); ++flightIt)
    {
        int x = flightIt->getX();
        int y = flightIt->getY();

        flightsSymbols.push_back(QLine(x - FLIGHT_CROSS_SIZE, y, x + FLIGHT_CROSS_SIZE, y));
        flightsSymbols.push_back(QLine(x, y - FLIGHT_CROSS_SIZE, x, y + FLIGHT_CROSS_SIZE));
    }

    painter.setPen(PEN_FLIGHT);
    painter.drawLines(flightsSymbols);
}


int FlightsView::getScreenX(const int relX)
{
    return relX * scale;
}

int FlightsView::getScreenY(const int relY)
{
    return drawingHeight - relY * scale;
}
