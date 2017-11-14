#include "mainwindow.h"
#include <QApplication>

#include "flightmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FlightModel flightsModel;

    MainWindow w(flightsModel);
    w.show();

    return a.exec();
}
