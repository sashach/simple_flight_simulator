#ifndef FLIGHTVIEW_H
#define FLIGHTVIEW_H

#include <QDialog>

#include "flightsviewmodel.h"

class FlightsModel;

class FlightsView : public QDialog
{
    Q_OBJECT
public:
    explicit FlightsView(FlightsModel & model, QWidget *parent = nullptr);

    enum
    {
        LINES_WIDTH = 2,
        POINTS_WIDTH = 5,
        FLIGHT_CROSS_SIZE = 5,
        POINT_NAMES_OFFSET = 10
    };

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent*) override;
    void mousePressEvent(QMouseEvent * event) override;

private:
    FlightsViewModel flightsPO;
    int drawingWidth;
    int drawingHeight;

    void drawLinesPoints(QPainter & painter);
    void drawPointsNames(QPainter & painter);
    void drawFlights(QPainter & painter);
    void drawOptimisedFlight(QPainter & painter);

signals:
    void sizeChanged(const int width, const int height);
    void mousePress(const int x, const int y, const QPoint & global);

public slots:
    void onModelUpdated();
    void onShowMeterFeetMenu(const QPoint & global);
};

#endif // FLIGHTVIEW_H
