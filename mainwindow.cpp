#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// menu
void MainWindow::on_actionCompile_triggered()
{
    qDebug() << "(unimp) menu - Compile";
}

void MainWindow::on_actionNew_triggered()
{
    qDebug() << "(unimp) menu - New";
}

void MainWindow::on_actionOpen_triggered()
{
    qDebug() << "(unimp) menu - Open";
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionSave_triggered()
{
    qDebug() << "(unimp) menu - Save";
}

void MainWindow::on_actionSave_As_triggered()
{
    qDebug() << "(unimp) menu - Save As";
}
