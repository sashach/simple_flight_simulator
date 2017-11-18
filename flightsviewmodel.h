#ifndef FLIGHTSVIEWMODEL_H
#define FLIGHTSVIEWMODEL_H

#include <QObject>
#include "flightpo.h"
#include "screencoordinatescalculator.h"

#include <QMap>

class FlightsModel;

class FlightsViewModel : public QObject
{
    Q_OBJECT
public:
    explicit FlightsViewModel(FlightsModel & model, QObject *parent = nullptr);

    const QMap<int, FlightPO> & getFlights() const;

    bool isOptimisedFlightExists() const;
    const FlightPO & getOptimisedFlight() const;

private:
    FlightsModel & flightsModel;
    QMap<int, FlightPO> flights;

    FlightPO optimisedFlight;
    bool optimisedFlightExists;

    ScreenCoordinatesCalculator coordinatesCalculator;
    int menuFlightId;

    void calculateScreenCoordinates();

    enum
    {
        MOUSE_CLICK_SENSITIVITY_SQRT = 100
    };

    void setAltitudeInFeet(const bool val);

signals:
    void flightsChanged();
    void showMetersFeetMenu(const QPoint & global);

public slots:
    void onFlightsUpdated();
    void onViewSizeChanged(const int width, const int height);
    void onMousePressed(const int x, const int y, const QPoint & global);
    void onMetersSelected();
    void onFeetSelected();
    void clearFlights();
};

#endif // FLIGHTSVIEWMODEL_H
