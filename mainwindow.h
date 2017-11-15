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

signals:

public slots:
    void onFlightsView();
    void onGenerationReady();
};

#endif // MAINWINDOW_H
