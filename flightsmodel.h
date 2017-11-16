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
    QVector<Flight> & getFlights();

    QMutex & getLock();

private:
    QVector<Flight> flights;
    QMutex flightsLock;

    void clearFlights();
    void generateFlights();

signals:
    void updated();
    void ready();
    void run();
    void pause();

public slots:
    void onGenerate();
    void onUpdate();
};

#endif // FLIGHTSMODEL_H
