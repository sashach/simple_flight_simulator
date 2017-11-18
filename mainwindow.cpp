#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flightsmodel.h"
#include "flightsview.h"

#include <QMessageBox>

MainWindow::MainWindow(FlightsModel &model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    flightsModel(model)
{
    ui->setupUi(this);

    connect(ui->generateButton, QPushButton::pressed, this, MainWindow::onGenerate);
    connect(ui->flightsViewButton, QPushButton::pressed, this, MainWindow::onFlightsView);
    connect(ui->alternativeButton, QPushButton::pressed, this, MainWindow::onAlternative);

    connect(ui->runButton, QPushButton::pressed, this, MainWindow::onRun);
    connect(ui->pauseButton, QPushButton::pressed, this, MainWindow::onPause);

    connect(ui->doubleSpeedButton, QRadioButton::pressed, this, MainWindow::onDoubleSpeed);
    connect(ui->halfSpeedButton, QRadioButton::pressed, this, MainWindow::onHalfSpeed);
    connect(ui->normalSpeedButton, QRadioButton::pressed, this, MainWindow::onNormalSpeed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFlightsView()
{
    FlightsView *flightsView = new FlightsView(flightsModel, this);

    flightsView->setGeometry(QRect(100, 100, 700, 700));
    flightsView->show();
}

void MainWindow::onGenerationReady()
{
    ui->runButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
    ui->speedGroupBox->setEnabled(true);
    ui->alternativeButton->setEnabled(true);
}

void MainWindow::onRun()
{
    ui->runButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    emit run();
}

void MainWindow::onPause()
{
    emit pause();
}

void MainWindow::onGenerate()
{
    emit generate();
}

void MainWindow::onDoubleSpeed()
{
    emit doubleSpeed();
}

void MainWindow::onHalfSpeed()
{
    emit halfSpeed();
}

void MainWindow::onNormalSpeed()
{
    emit normalSpeed();
}

void MainWindow::onAlternative()
{
    emit alternative();
}

void MainWindow::onAlternativeGenerated()
{
    QMessageBox msgBox;
    msgBox.setText("The alternative route was generated.");
    msgBox.setInformativeText("Do you want to apply it?");
    msgBox.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    switch(ret)
    {
    case QMessageBox::Apply:
        emit applyAlternative();
        break;

    default:
        emit cancelAlternative();
        break;
    }
}
