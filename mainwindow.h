#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CardView;
class OutlineTree;
class QTabWidget;
class QTreeWidgetItem;
class QTextEdit;
class QLineEdit;
enum class CategoryType;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_btnFolder_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_outlineTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    void initOutline();
    void initMainTab();
    void initGeneral();
    void initDraft();

    void setDefaultOutlineTree();
    void setDefaultGeneralTab();

    void displayMainTab(CategoryType type);
    void displayCardView(QTreeWidgetItem *item);
    void displayEditor(QTreeWidgetItem *item);

    Ui::MainWindow *ui_;
    OutlineTree *outlineTree_;
    QTabWidget *mainTab_;
    // general
    QLineEdit *generalTitle_;
    QLineEdit *generalSubtitle_;
    QLineEdit *generalSeries_;
    QLineEdit *generalVolume_;
    QLineEdit *generalGenre_;
    QLineEdit *generalLicense_;
    QLineEdit *generalAuthorName_;
    QLineEdit *generalAuthorEmail_;
    // draft
    CardView *draftTable_;
    QTextEdit *draftEdit_;
};
#endif // MAINWINDOW_H
