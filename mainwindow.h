#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSettings;
class QTreeWidgetItem;

class OutlineView;
class ViewChanger;

class GlobalSetting;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // menu - file
    void on_actionQuit_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionNew_triggered();
    void on_actionClose_triggered();
    // menu - edit
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionPreference_triggered();
    // menu - build
    void on_actionCompile_triggered();
    // category buttons
    void on_btnBookInfo_clicked();
    void on_btnDraft_clicked();
    void on_btnPlot_clicked();
    void on_btnPersons_clicked();
    void on_btnWorlds_clicked();
    void on_btnResearch_clicked();
    void on_btnNotes_clicked();
    void on_btnRubi_clicked();
    void on_btnTrash_clicked();
    // draft tree
    void on_btnFolderDraft_clicked();
    void on_btnAddDraft_clicked();
    void on_btnDelDraft_clicked();
    void on_draftTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    // plot tree
    void on_btnFolderPlot_clicked();
    void on_btnAddPlot_clicked();
    void on_btnDelPlot_clicked();
    void on_plotTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    // person tree
    void on_btnFolderPerson_clicked();
    void on_btnAddPerson_clicked();
    void on_btnDelPerson_clicked();
    void on_personTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    // world tree
    void on_btnFolderWorld_clicked();
    void on_btnAddWorld_clicked();
    void on_btnDelWorld_clicked();
    void on_worldTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    // research tree
    void on_researchTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_btnFolderResearch_clicked();
    void on_btnAddResearch_clicked();
    void on_btnDelResearch_clicked();
    // notes tree
    void on_notesTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_btnFolderNotes_clicked();
    void on_btnAddNotes_clicked();
    void on_btnDelNotes_clicked();
    // rubi tree
    void on_rubiTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_btnFolderRubi_clicked();
    void on_btnAddRubi_clicked();
    void on_btnDelRubi_clicked();
    // trash tree
    void on_trashTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_btnClearTrash_clicked();

private:
    Ui::MainWindow *ui;
    QSettings *settings_;

    ViewChanger *view_changer_;
    OutlineView *draft_tree_;
    OutlineView *plot_tree_;
    OutlineView *person_tree_;
    OutlineView *world_tree_;
    OutlineView *research_tree_;
    OutlineView *notes_tree_;
    OutlineView *rubi_tree_;
    OutlineView *trash_tree_;

    GlobalSetting *global_setting_;
};
#endif // MAINWINDOW_H
