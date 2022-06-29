#ifndef VIEWCHANGER_H
#define VIEWCHANGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTabWidget;

class BookInfoView;
class DraftTree;
class CorkboardView;
class TextEdit;

enum class Category;

class ViewChanger
{
public:
    explicit ViewChanger(Ui::MainWindow *ui);
    ~ViewChanger();

    void Change(Category category);
    void Update(Category category);

private:
    enum class ViewDisp {
        OFF = 0,
        ON,
    };
    enum class OutlineCat {
        Draft,
        Plot,
        Persons,
        Worlds,
        Research,
        Notes,
        Rubi,
        Trash,
    };
    enum class MainTabCat {
        BookInfo,
        Corkboard,
        PersonsTable,
        WorldsTable,
        RubiTable,
    };
    enum class SideTabCat {
        Draft,
        Plot,
        Persons,
        Worlds,
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

    void UpdateBookInfo_();
    void UpdateDraft_();

    void ChangeOutlineTree_(OutlineCat cat);
    void ChangeMainTab_(MainTabCat cat);
    void ChangeSideTab_(SideTabCat cat);

    void ShowHideViews_(ViewDisp outline, ViewDisp mtab, ViewDisp editor, ViewDisp side);

    void UpdatePreviousPage_(Category category);
    void SavePreviousPageData_(Category category);

    QTabWidget *outline_tab_;
    QTabWidget *main_tab_;
    TextEdit *main_editor_;
    QTabWidget *side_tab_;

    BookInfoView *bookinfo_view_;
    DraftTree *draft_tree_;
    CorkboardView *corkboard_;

    Category previous_cat_;
};

#endif // VIEWCHANGER_H
