#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSettings;
class QTreeWidgetItem;

class DraftTree;
class NotesTree;
class PersonTree;
class PlotTree;
class ResearchTree;
class RubiTree;
class TrashTree;
class ViewChanger;
class WorldTree;

class ConfigItem;

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

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionPreference_triggered();

private:
    Ui::MainWindow *ui;
    QSettings *settings_;

    ViewChanger *view_changer_;
    DraftTree *draft_tree_;
    PlotTree *plot_tree_;
    PersonTree *person_tree_;
    WorldTree *world_tree_;
    ResearchTree *research_tree_;
    NotesTree *notes_tree_;
    RubiTree *rubi_tree_;
    TrashTree *trash_tree_;

    ConfigItem *config_;
};
#endif // MAINWINDOW_H
