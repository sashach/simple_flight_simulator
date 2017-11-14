#ifndef FLIGHTVIEW_H
#define FLIGHTVIEW_H

#include <QDialog>

#include "flightspomanager.h"

class FlightModel;

class FlightsView : public QDialog
{
    Q_OBJECT
public:
    explicit FlightsView(FlightModel & model, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent*) override;

private:
    FlightsPOManager flightsPO;
    FlightModel & flightsModel;
    int drawingWidth;
    int drawingHeight;
    double scale;

    int getScreenX(const int relX);
    int getScreenY(const int relY);

    void drawLinesPoints(QPainter & painter);
    void drawPointsNames(QPainter & painter);
    void drawFlights(QPainter & painter);

signals:

public slots:
    void onModelUpdated();
};

#endif // FLIGHTVIEW_H
