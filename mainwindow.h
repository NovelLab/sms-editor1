#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSettings;
class QTreeWidgetItem;

class DraftTree;
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
    void on_actionClose_triggered();
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
    void on_btnFolderDraft_clicked();
    void on_btnAddDraft_clicked();
    void on_btnDelDraft_clicked();

    void on_draftTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Ui::MainWindow *ui;
    QSettings *settings_;

    ViewChanger *view_changer_;
    DraftTree *draft_tree_;
};
#endif // MAINWINDOW_H
