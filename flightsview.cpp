#include "flightsview.h"
#include "flightpo.h"
#include "constants.h"
#include "waypointpo.h"

#include <QPainter>

static const QBrush BACKGROUND_BRUSH = QBrush(QColor(200, 200, 200));
static const QPen PEN_PASSED_ROUTE = QPen(QColor(120, 120, 160), FlightsView::LINES_WIDTH);
static const QPen PEN_NON_PASSED_ROUTE = QPen(QColor(90, 90, 220), FlightsView::LINES_WIDTH);
static const QPen PEN_POINTS = QPen(QColor(240, 240, 70), FlightsView::POINTS_WIDTH);
static const QPen PEN_POINTS_NAMES = QPen(QColor(240, 240, 70));
static const QPen PEN_FLIGHT = QPen(QColor(20, 180, 40), FlightsView::LINES_WIDTH);
static const QFont WAYPOINTS_FONT = QFont("arial", 10);
static const QFont FLIGHT_LABEL_FONT = QFont("arial", 12);
static const QFontMetrics WAYPOINT_FONT_METRICS(WAYPOINTS_FONT);
static const QFontMetrics FLIGHT_FONT_METRICS(FLIGHT_LABEL_FONT);

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
            const Point3d & coordinates = pointIt->getCoordinates();
            points.push_back(QPoint(coordinates.getX(), coordinates.getY()));

            if(!firstPoint)
            {
                if(prevPointPassed)
                {
                    passedLines.push_back(QLine(prevX, prevY, coordinates.getX(), coordinates.getY()));
                }
                else
                {
                    nonPassedLines.push_back(QLine(prevX, prevY, coordinates.getX(), coordinates.getY()));
                }
            }
            prevX = coordinates.getX();
            prevY = coordinates.getY();
            prevPointPassed = pointIt->isPassed();
            firstPoint = false;
        }

        for(auto pointIt = wayPoints.begin(); pointIt != wayPoints.end(); ++pointIt)
        {
            if(!pointIt->isPassed())
            {
                nonPassedLines.push_back(QLine(flightIt->getX(), flightIt->getY(),
                         pointIt->getCoordinates().getX(), pointIt->getCoordinates().getY()));
                break;
            }
        }
    }

    painter.setPen(PEN_PASSED_ROUTE);
    painter.drawLines(passedLines);

    painter.setPen(PEN_NON_PASSED_ROUTE);
    painter.drawLines(nonPassedLines);

    painter.setPen(PEN_POINTS);
    painter.drawPoints(points.data(), points.size());
}

void FlightsView::drawPointsNames(QPainter & painter)
{
    painter.setFont(WAYPOINTS_FONT);
    painter.setPen(PEN_POINTS_NAMES);

    const QVector<FlightPO> & flights = flightsPO.getFlights();
    for(auto flightIt = flights.begin(); flightIt != flights.end(); ++flightIt)
    {
        const QVector<WayPointPO> & wayPoints = flightIt->getWayPoints();
        for(auto pointIt = wayPoints.begin(); pointIt != wayPoints.end(); ++pointIt)
        {
            const Point3d & coordinates = pointIt->getCoordinates();
            int x = POINT_NAMES_OFFSET + coordinates.getX();
            int y = POINT_NAMES_OFFSET + coordinates.getY();

            painter.drawText(x, y, pointIt->getName());
            painter.drawText(x, y + WAYPOINT_FONT_METRICS.height(), pointIt->getLabelString2());
        }
    }
}

void FlightsView::drawFlights(QPainter & painter)
{
    painter.setFont(FLIGHT_LABEL_FONT);
    painter.setPen(PEN_POINTS_NAMES);

    const QVector<FlightPO> & flights = flightsPO.getFlights();

    QVector <QLine> flightsSymbols;
    flightsSymbols.reserve(2 * flights.size());

    for(auto flightIt = flights.begin(); flightIt != flights.end(); ++flightIt)
    {
        int x = flightIt->getX();
        int y = flightIt->getY();

        flightsSymbols.push_back(QLine(x - FLIGHT_CROSS_SIZE, y, x + FLIGHT_CROSS_SIZE, y));
        flightsSymbols.push_back(QLine(x, y - FLIGHT_CROSS_SIZE, x, y + FLIGHT_CROSS_SIZE));

        x -= 10 + FLIGHT_FONT_METRICS.width(flightIt->getLabelCoordinates());
        int curY = y - 40;
        painter.drawText(x, curY, flightIt->getAircraftId());

        curY += FLIGHT_FONT_METRICS.height();
        painter.drawText(x, curY, flightIt->getLabelCoordinates());

        curY += FLIGHT_FONT_METRICS.height();
        painter.drawText(x, curY, flightIt->getSimulatorTimeDiff());
    }

    painter.setPen(PEN_FLIGHT);
    painter.drawLines(flightsSymbols);
}


