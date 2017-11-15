#ifndef FLIGHTSVIEWMODEL_H
#define FLIGHTSVIEWMODEL_H

#include <QObject>
#include "flightpo.h"
#include "screencoordinatescalculator.h"

#include <QVector>

class FlightsModel;

class FlightsViewModel : public QObject
{
    Q_OBJECT
public:
    explicit FlightsViewModel(FlightsModel & model, QObject *parent = nullptr);

    const QVector<FlightPO> & getFlights() const;

private:
    FlightsModel & flightsModel;
    QVector<FlightPO> flights;

    ScreenCoordinatesCalculator coordinatesCalculator;

    void calculateScreenCoordinates();

signals:
    void flightsChanged();

public slots:
    void onFlightsUpdated();
    void onViewSizeChanged(const int width, const int height);
};

#endif // FLIGHTSVIEWMODEL_H
