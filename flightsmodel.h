#ifndef FLIGHTSMODEL_H
#define FLIGHTSMODEL_H

#include <QObject>
#include <QVector>
#include <QMutex>

#include "flight.h"

class FlightsModel : public QObject
{
    Q_OBJECT
public:
    explicit FlightsModel(QObject *parent = nullptr);

    const QVector<Flight> & getFlights() const;

    QMutex & getLock();

private:
    QVector<Flight> flights;
    QMutex flightsLock;

    void clearFlights();
    void generateFlights();

signals:
    void updated();

public slots:
    void onGenerate();
};

#endif // FLIGHTSMODEL_H
