#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CardView;
class OutlineTree;
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

    void on_btnFolder_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

private:
    void initOutline();
    void initMainTab();
    void initGeneral();
    void initDraft();

    void setDefaultOutlineTree();
    void setDefaultGeneralTab();

    Ui::MainWindow *ui;
    OutlineTree *outlineTree;
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
