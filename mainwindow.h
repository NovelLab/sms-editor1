#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CardView;
class QTreeWidget;
class QTabWidget;
class QTextEdit;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

private:
    void initOutline();
    void initMainTab();
    void initGeneral();
    void initDraft();

    void setDefaultOutlineTree();
    void setDefaultGeneralTab();

    Ui::MainWindow *ui;
    QTreeWidget *outlineTree;
    QTabWidget *mainTab;
    // general
    QLineEdit *generalTitle;
    QLineEdit *generalSubtitle;
    QLineEdit *generalSeries;
    QLineEdit *generalVolume;
    QLineEdit *generalGenre;
    QLineEdit *generalLicense;
    QLineEdit *generalAuthorName;
    QLineEdit *generalAuthorEmail;
    // draft
    CardView *draftTable;
    QTextEdit *draftEdit;
};
#endif // MAINWINDOW_H
