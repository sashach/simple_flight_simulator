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
    void start();
    void pause();
    void update();

public slots:
    void onStart();
    void onPause();
    void onUpdate();
};

#endif // SIMULATORTHREAD_H
