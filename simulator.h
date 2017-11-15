#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>

class Simulator : public QObject
{
    Q_OBJECT
public:
    explicit Simulator(QObject *parent = nullptr);

    void doSomeWork();

signals:
    void finished();
    void error(QString err);

public slots:
    void process();
    void onRun();
    void onPause();

};

#endif // SIMULATOR_H
