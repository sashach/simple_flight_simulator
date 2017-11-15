#include "flightsview.h"
#include "flightpo.h"
#include "constants.h"
#include "waypointpo.h"

#include <QPainter>

static const QBrush BACKGROUND_BRUSH = QBrush(QColor(200, 200, 200));
static const QPen PEN_PASSED_ROUTE = QPen(QColor(20, 20, 90), FlightsView::LINES_WIDTH);
static const QPen PEN_NON_PASSED_ROUTE = QPen(QColor(90, 90, 220), FlightsView::LINES_WIDTH);
static const QPen PEN_POINTS = QPen(QColor(240, 240, 70), FlightsView::POINTS_WIDTH);
static const QPen PEN_POINTS_NAMES = QPen(QColor(240, 240, 70));
static const QPen PEN_FLIGHT = QPen(QColor(20, 180, 40), FlightsView::LINES_WIDTH);

FlightsView::FlightsView(FlightsModel &model, QWidget *parent) :
    QDialog(parent),
    flightsPO(model),
    drawingWidth(0),
    drawingHeight(0)
{
    setWindowTitle("Flights View");
    flightsPO.onFlightsUpdated();

    connect(&flightsPO, FlightsViewModel::flightsChanged, this, onModelUpdated);
    connect(this, sizeChanged, &flightsPO, FlightsViewModel::onViewSizeChanged);
}

void FlightsView::resizeEvent(QResizeEvent*)
{
    drawingWidth = width();
    drawingHeight = height();

    emit sizeChanged(drawingWidth, drawingHeight);
}

void FlightsView::onModelUpdated()
{
    update();
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
    const QVector<FlightPO> & flights = flightsPO.getFlights();

    QVector <QPoint> points;
    QVector <QLine> passedLines, nonPassedLines;

    points.reserve(MAX_FLIGHT_POINTS * flights.size());
    passedLines.reserve(points.capacity() / 2);
    nonPassedLines.reserve(points.capacity() / 2);

    for(auto flightIt = flights.begin(); flightIt != flights.end(); ++flightIt)
    {
        const QVector<WayPointPO> & wayPoints = flightIt->getWayPoints();

        bool firstPoint = true;
        int prevX = 0, prevY = 0;
        bool prevPointPassed = false;

        for(auto pointIt = wayPoints.begin(); pointIt != wayPoints.end(); ++pointIt)
        {
            int x = pointIt->getX();
            int y = pointIt->getY();
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

    const QVector<FlightPO> & flights = flightsPO.getFlights();
    for(auto flightIt = flights.begin(); flightIt != flights.end(); ++flightIt)
    {
        const QVector<WayPointPO> & wayPoints = flightIt->getWayPoints();
        for(auto pointIt = wayPoints.begin(); pointIt != wayPoints.end(); ++pointIt)
        {
            int x = POINT_NAMES_OFFSET + pointIt->getX();
            int y = POINT_NAMES_OFFSET + pointIt->getY();

            painter.drawText(QPoint(x, y), pointIt->getName());
        }
    }
}

void FlightsView::drawFlights(QPainter & painter)
{
    const QVector<FlightPO> & flights = flightsPO.getFlights();

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


