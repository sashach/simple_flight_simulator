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

    connect(ui->generateButton, SIGNAL(pressed()), this, SLOT(onGenerate()));
    connect(ui->flightsViewButton, SIGNAL(pressed()), this, SLOT(onFlightsView()));
    connect(ui->alternativeButton, SIGNAL(pressed()), this, SLOT(onAlternative()));

    connect(ui->runButton, SIGNAL(pressed()), this, SLOT(onRun()));
    connect(ui->pauseButton, SIGNAL(pressed()), this, SLOT(onPause()));

    connect(ui->doubleSpeedButton, SIGNAL(pressed()), this, SLOT(onDoubleSpeed()));
    connect(ui->halfSpeedButton, SIGNAL(pressed()), this, SLOT(onHalfSpeed()));
    connect(ui->normalSpeedButton, SIGNAL(pressed()), this, SLOT(onNormalSpeed()));
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

void MainWindow::onAlternativeNotGenerated()
{
    QMessageBox msgBox;
    msgBox.setText("Could not create alternative route.\nNo possible to bypass points");
    msgBox.exec();
}
