#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "enums/generaltypes.h"

#include "viewchanger.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view_changer_ = new ViewChanger();

}

MainWindow::~MainWindow()
{
    delete view_changer_;
    delete ui;
}

// slots (menu)
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

// slots (changer buttons)
void MainWindow::on_btnBookInfo_clicked()
{
    view_changer_->Change(Category::BookInfo);
}

void MainWindow::on_btnDraft_clicked()
{
    view_changer_->Change(Category::Draft);
}

void MainWindow::on_btnNotes_clicked()
{
    view_changer_->Change(Category::Notes);
}

void MainWindow::on_btnPersons_clicked()
{
    view_changer_->Change(Category::Persons);
}

void MainWindow::on_btnPlot_clicked()
{
    view_changer_->Change(Category::Plot);
}

void MainWindow::on_btnResearch_clicked()
{
    view_changer_->Change(Category::Research);
}

void MainWindow::on_btnRubi_clicked()
{
    view_changer_->Change(Category::Rubi);
}

void MainWindow::on_btnTrash_clicked()
{
    view_changer_->Change(Category::Trash);
}

void MainWindow::on_btnWorlds_clicked()
{
    view_changer_->Change(Category::Worlds);
}
