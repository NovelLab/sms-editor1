#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class OutlineView;
class GeneralView;
class PlotView;
class PersonView;
class DataView;
class MainTabView;
class TextEdit;

class QTreeWidgetItem;
class QSettings;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // menu
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionQuit_triggered();
    // buttons
    void on_btnFolder_clicked();
    void on_btnAdd_clicked();
    void on_btnDel_clicked();
    // tree views
    void on_outlineView_itemClicked(QTreeWidgetItem *item, int column);
    void OnTreeItemTitleChanged(QTreeWidgetItem *item, int column);
    void OnTreeItemChangedForSave(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    // general views
    void on_lineTitle_editingFinished();
    void on_lineSubtitle_editingFinished();
    void on_lineSeries_editingFinished();
    void on_lineVolume_editingFinished();
    void on_lineGenre_editingFinished();
    void on_lineLicense_editingFinished();
    void on_lineAuthorname_editingFinished();
    void on_lineEmail_editingFinished();

    void on_actionCompile_triggered();

private:
    void InitDefaultCategories_();
    bool IsValidatedTreeItem_(const QTreeWidgetItem *item);
    void DisplayFolderView_(const QTreeWidgetItem *item);
    void DisplayFileView_(const QTreeWidgetItem *item);
    void DisplayGeneralView_(const QTreeWidgetItem *item);

    void DisplayCharCounts(const QTreeWidgetItem *item);

    void UpdateGeneralData_();
    void SetupGeneralData_();

    void UpdateEditorData_(const QTreeWidgetItem *item);
    void SetupEditorData_(const QTreeWidgetItem *item);

    QString ValidatedFilename_(const QString &fname);
    void SaveFile_(const QString &fname);

    Ui::MainWindow *ui;

    OutlineView *outline_view_;
    GeneralView *general_view_;
    PlotView *plot_view_;
    PersonView *person_view_;
    DataView *data_view_;
    MainTabView *tab_view_;
    TextEdit *editor_;

    QSettings *settings_;
};
#endif // MAINWINDOW_H
