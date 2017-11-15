#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class FlightsModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(FlightsModel & model, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FlightsModel & flightsModel;

public slots:
    void onFlightsView();

};

#endif // MAINWINDOW_H
