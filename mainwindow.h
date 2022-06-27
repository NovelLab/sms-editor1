#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ViewChanger;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionNew_triggered();
    void on_actionCompile_triggered();
    void on_btnBookInfo_clicked();
    void on_btnDraft_clicked();
    void on_btnPlot_clicked();
    void on_btnPersons_clicked();
    void on_btnWorlds_clicked();
    void on_btnResearch_clicked();
    void on_btnNotes_clicked();
    void on_btnRubi_clicked();
    void on_btnTrash_clicked();

private:
    Ui::MainWindow *ui;
    ViewChanger *view_changer_;
};
#endif // MAINWINDOW_H
