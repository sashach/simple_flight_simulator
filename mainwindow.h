#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class FlightModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(FlightModel & model, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FlightModel & flightsModel;

public slots:
    void onFlightsView();

};

#endif // MAINWINDOW_H
