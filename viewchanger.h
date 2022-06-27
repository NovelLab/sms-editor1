#ifndef VIEWCHANGER_H
#define VIEWCHANGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTabWidget;

class QTextEdit;

enum class Category;

class ViewChanger
{
public:
    explicit ViewChanger(Ui::MainWindow *ui);
    ~ViewChanger();

    void Change(Category category);

private:
    enum class ViewDisp {
        OFF = 0,
        ON,
    };
    void ChangeBookInfo_();
    void ChangeDraft_();
    void ChangePlot_();
    void ChangePersons_();
    void ChangeWorlds_();
    void ChangeResearch_();
    void ChangeNotes_();
    void ChangeRubi_();
    void ChangeTrash_();

    void ShowHideViews_(ViewDisp outline, ViewDisp mtab, ViewDisp editor, ViewDisp side);

    QTabWidget *outline_tab_;
    QTabWidget *main_tab_;
    QTextEdit *main_editor_;
    QTabWidget *side_tab_;
};

#endif // VIEWCHANGER_H
