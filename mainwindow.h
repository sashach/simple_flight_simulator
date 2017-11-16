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
    void generate();
    void run();
    void pause();
    void doubleSpeed();
    void halfSpeed();
    void normalSpeed();

public slots:
    void onFlightsView();
    void onGenerationReady();
    void onGenerate();
    void onRun();
    void onPause();
    void onDoubleSpeed();
    void onHalfSpeed();
    void onNormalSpeed();
};

#endif // MAINWINDOW_H
