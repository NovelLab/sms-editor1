#ifndef VIEWCHANGER_H
#define VIEWCHANGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTabWidget;

class BookInfoEditor;
class CorkboardView;
class DraftEditor;
class DraftTree;
class NotesTree;
class PersonEditor;
class PersonTree;
class PersonsTableView;
class PlotEditor;
class PlotTree;
class ResearchTree;
class RubiTree;
class RubiTableView;
class TextEdit;
class TrashTree;
class WorldTree;
class WorldsTableView;

namespace GeneralType {
enum class Category;
}

class ViewChanger
{
public:
    explicit ViewChanger(Ui::MainWindow *ui);
    ~ViewChanger();

    void Change(GeneralType::Category category);
    void Update(GeneralType::Category category);

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
        Rubi,
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
    void UpdatePlot_();
    void UpdatePersons_();
    void UpdateWorlds_();
    void UpdateResearch_();
    void UpdateNotes_();
    void UpdateRubi_();
    void UpdateTrash_();

    void ChangeOutlineTree_(OutlineCat cat);
    void ChangeMainTab_(MainTabCat cat);
    void ChangeSideTab_(SideTabCat cat);

    void ShowHideViews_(ViewDisp outline, ViewDisp mtab, ViewDisp editor, ViewDisp side);

    void UpdatePreviousPage_(GeneralType::Category category);
    void SavePreviousPageData_(GeneralType::Category category);

    QTabWidget *outline_tab_;
    QTabWidget *main_tab_;
    TextEdit *main_editor_;
    QTabWidget *side_tab_;

    BookInfoEditor *bookinfo_editor_;

    DraftTree *draft_tree_;
    PlotTree *plot_tree_;
    PersonTree *person_tree_;
    WorldTree *world_tree_;
    ResearchTree *research_tree_;
    NotesTree *notes_tree_;
    RubiTree *rubi_tree_;
    TrashTree *trash_tree_;

    CorkboardView *corkboard_;
    PersonsTableView *persons_table_;
    WorldsTableView *worlds_table_;
    RubiTableView *rubi_table_;

    DraftEditor *draft_editor_;
    PlotEditor *plot_editor_;
    PersonEditor *person_editor_;

    GeneralType::Category previous_cat_;
};

#endif // VIEWCHANGER_H
