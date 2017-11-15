#ifndef SIMULATORTHREAD_H
#define SIMULATORTHREAD_H

#include <QObject>

class FlightsModel;

class SimulatorThread : public QObject
{
    Q_OBJECT
public:
    explicit SimulatorThread(FlightsModel & model, QObject *parent = nullptr);

    void run();

private:
    FlightsModel & flightsModel;

signals:

public slots:
};

#endif // SIMULATORTHREAD_H
