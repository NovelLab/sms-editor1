#include "viewchanger.h"

#include "ui_mainwindow.h"

#include "common/generalenums.h"
#include "editor/bookinfoeditor.h"
#include "editor/drafteditor.h"
#include "editor/personeditor.h"
#include "editor/ploteditor.h"
#include "editor/rubieditor.h"
#include "editor/worldeditor.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QTreeWidgetItem>

#include <QDebug>

ViewChanger::ViewChanger(Ui::MainWindow *ui)
    :previous_cat_{GeneralType::Category::None}
{
    // set ui widgets
    outline_tab_ = ui->outlineTab;
    main_tab_ = ui->mainViewTab;
    main_editor_ = ui->mainEditor;
    side_tab_ = ui->sideTab;

    bookinfo_editor_ = new BookInfoEditor(ui);

    draft_tree_ = ui->draftTreeView;
    plot_tree_ = ui->plotTreeView;
    person_tree_ = ui->personTreeView;
    world_tree_ = ui->worldTreeView;
    research_tree_ = ui->researchTreeView;
    notes_tree_ = ui->notesTreeView;
    rubi_tree_ = ui->rubiTreeView;
    trash_tree_ = ui->trashTreeView;

    corkboard_ = ui->corkboardView;
    persons_table_ = ui->personsTableView;
    worlds_table_ = ui->worldsTableView;
    rubi_table_ = ui->rubiTableView;

    draft_editor_ = new DraftEditor(ui);
    plot_editor_ = new PlotEditor(ui);
    person_editor_ = new PersonEditor(ui);
    world_editor_ = new WorldEditor(ui);
    rubi_editor_ = new RubiEditor(ui);
}

ViewChanger::~ViewChanger()
{
    // TODO: 自身でnewしたものはここで解放
    delete bookinfo_editor_;
    delete draft_editor_;
    delete plot_editor_;
    delete person_editor_;
    delete world_editor_;
    delete rubi_editor_;
}

// methods
void ViewChanger::Change(GeneralType::Category category)
{
    SavePreviousPageData_();

    switch (category) {
      case GeneralType::Category::BookInfo:
        ChangeBookInfo_();
        break;
      case GeneralType::Category::Draft:
        ChangeDraft_();
        break;
      case GeneralType::Category::Plot:
        ChangePlot_();
        break;
      case GeneralType::Category::Persons:
        ChangePersons_();
        break;
      case GeneralType::Category::Worlds:
        ChangeWorlds_();
        break;
      case GeneralType::Category::Research:
        ChangeResearch_();
        break;
      case GeneralType::Category::Notes:
        ChangeNotes_();
        break;
      case GeneralType::Category::Rubi:
        ChangeRubi_();
        break;
      case GeneralType::Category::Trash:
        ChangeTrash_();
        break;
      default:
        qWarning() << "unreachable in change view: Category is: " << static_cast<int>(category);
        break;
    }
}

BookInfoEditor* ViewChanger::GetBookInfo() const
{
    return bookinfo_editor_;
}

/*
 * NOTE: ここではdata→viewという反映のみ行うこと
 * */
void ViewChanger::Update(GeneralType::Category category)
{
    SavePreviousPageData_();
    switch (category) {
      case GeneralType::Category::BookInfo:
        UpdateBookInfo_();
        break;
      case GeneralType::Category::Draft:
        UpdateDraft_();
        break;
      case GeneralType::Category::Plot:
        UpdatePlot_();
        break;
      case GeneralType::Category::Persons:
        UpdatePersons_();
        break;
      case GeneralType::Category::Worlds:
        UpdateWorlds_();
        break;
      case GeneralType::Category::Research:
        UpdateResearch_();
        break;
      case GeneralType::Category::Notes:
        UpdateNotes_();
        break;
      case GeneralType::Category::Rubi:
        UpdateRubi_();
        break;
      case GeneralType::Category::Trash:
        UpdateTrash_();
        break;
      default:
        qWarning() << "unreachable in change view: Category is: " << static_cast<int>(category);
        break;
    }
}

// methods (private)
void ViewChanger::ChangeBookInfo_()
{
    ShowHideViews_(ViewDisp::OFF, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeMainTab_(MainTabCat::BookInfo);
    UpdatePreviousPage_(GeneralType::Category::BookInfo);
}

void ViewChanger::ChangeDraft_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Draft);
    ChangeMainTab_(MainTabCat::Corkboard);
    ChangeSideTab_(SideTabCat::Draft);
    UpdatePreviousPage_(GeneralType::Category::Draft);
}

void ViewChanger::ChangePlot_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Plot);
    ChangeMainTab_(MainTabCat::Corkboard);
    ChangeSideTab_(SideTabCat::Plot);
    UpdatePreviousPage_(GeneralType::Category::Plot);
}

void ViewChanger::ChangePersons_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Persons);
    ChangeMainTab_(MainTabCat::PersonsTable);
    ChangeSideTab_(SideTabCat::Persons);
    UpdatePreviousPage_(GeneralType::Category::Persons);
}

void ViewChanger::ChangeWorlds_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Worlds);
    ChangeMainTab_(MainTabCat::WorldsTable);
    ChangeSideTab_(SideTabCat::Worlds);
    UpdatePreviousPage_(GeneralType::Category::Worlds);
}

void ViewChanger::ChangeResearch_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Research);
    ChangeMainTab_(MainTabCat::Corkboard);
    UpdatePreviousPage_(GeneralType::Category::Research);
}

void ViewChanger::ChangeNotes_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Notes);
    ChangeMainTab_(MainTabCat::Corkboard);
    UpdatePreviousPage_(GeneralType::Category::Notes);
}

void ViewChanger::ChangeRubi_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Rubi);
    ChangeMainTab_(MainTabCat::RubiTable);
    ChangeSideTab_(SideTabCat::Rubi);
    UpdatePreviousPage_(GeneralType::Category::Rubi);
}

void ViewChanger::ChangeTrash_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Trash);
    ChangeMainTab_(MainTabCat::Corkboard);
    UpdatePreviousPage_(GeneralType::Category::Trash);
}

void ViewChanger::ChangeOutlineTree_(OutlineCat cat)
{
    outline_tab_->setCurrentIndex(static_cast<int>(cat));
}

void ViewChanger::ChangeMainTab_(MainTabCat cat)
{
    main_tab_->setCurrentIndex(static_cast<int>(cat));
}

void ViewChanger::ChangeSideTab_(SideTabCat cat)
{
    side_tab_->setCurrentIndex(static_cast<int>(cat));
}

void ViewChanger::SavePreviousPageData_()
{
    switch (previous_cat_) {
      case GeneralType::Category::BookInfo:
        bookinfo_editor_->SaveCurrentItem();
        break;
      case GeneralType::Category::Draft:
        main_editor_->SaveCurrentItem();
        draft_editor_->SaveCurrentItem();
        break;
      case GeneralType::Category::Plot:
        main_editor_->SaveCurrentItem();
        plot_editor_->SaveCurrentItem();
        break;
      case GeneralType::Category::Persons:
        main_editor_->SaveCurrentItem();
        person_editor_->SaveCurrentItem();
        break;
      case GeneralType::Category::Worlds:
        main_editor_->SaveCurrentItem();
        world_editor_->SaveCurrentItem();
        break;
      case GeneralType::Category::Research:
        main_editor_->SaveCurrentItem();
        break;
      case GeneralType::Category::Notes:
        main_editor_->SaveCurrentItem();
        break;
      case GeneralType::Category::Rubi:
        rubi_editor_->SaveCurrentItem();
        break;
      case GeneralType::Category::Trash:
        break;
      default:
        break;
    }
}

void ViewChanger::ShowHideViews_(ViewDisp outline, ViewDisp mtab, ViewDisp editor, ViewDisp side)
{
    outline_tab_->setVisible(static_cast<bool>(outline));
    main_tab_->setVisible(static_cast<bool>(mtab));
    main_editor_->setVisible(static_cast<bool>(editor));
    side_tab_->setVisible(static_cast<bool>(side));
}

void ViewChanger::UpdateBookInfo_()
{
    bookinfo_editor_->UpdateView();
}

void ViewChanger::UpdateDraft_()
{
    QTreeWidgetItem *cur = draft_tree_->currentItem();
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(cur))
        return;
    if (util.IsFolder(cur)) {
        corkboard_->UpdateView(cur);
        main_tab_->show();
        main_editor_->hide();
        side_tab_->hide();
    } else if (util.IsFile(cur)) {
        main_editor_->UpdateView(cur);
        draft_editor_->UpdateView(cur);
        main_tab_->hide();
        main_editor_->show();
        side_tab_->show();
    }
}

void ViewChanger::UpdateNotes_()
{
    QTreeWidgetItem *cur = notes_tree_->currentItem();
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(cur))
        return;
    if (util.IsFolder(cur)) {
        corkboard_->UpdateView(cur);
        main_tab_->show();
        main_editor_->hide();
    } else if (util.IsFile(cur)) {
        main_editor_->UpdateView(cur);
        main_tab_->hide();
        main_editor_->show();
    }
}

void ViewChanger::UpdatePersons_()
{
    QTreeWidgetItem *cur = person_tree_->currentItem();
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(cur))
        return;

    if (util.IsFolder(cur)) {
        persons_table_->UpdateView(cur);
        main_tab_->show();
        main_editor_->hide();
        side_tab_->hide();
    } else if (util.IsFile(cur)) {
        main_editor_->UpdateView(cur);
        person_editor_->UpdateView(cur);
        main_tab_->hide();
        main_editor_->show();
        side_tab_->show();
    }
}

void ViewChanger::UpdatePlot_()
{
    QTreeWidgetItem *cur = plot_tree_->currentItem();
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(cur))
        return;
    if (util.IsFolder(cur)) {
        corkboard_->UpdateView(cur);
        main_tab_->show();
        main_editor_->hide();
        side_tab_->hide();
    } else if (util.IsFile(cur)) {
        main_editor_->UpdateView(cur);
        plot_editor_->UpdateView(cur);
        main_tab_->hide();
        main_editor_->show();
        side_tab_->show();
    }
}

void ViewChanger::UpdateResearch_()
{
    QTreeWidgetItem *cur = research_tree_->currentItem();
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(cur))
        return;
    if (util.IsFolder(cur)) {
        corkboard_->UpdateView(cur);
        main_tab_->show();
        main_editor_->hide();
    } else if (util.IsFile(cur)) {
        main_editor_->UpdateView(cur);
        main_tab_->hide();
        main_editor_->show();
    }
}

void ViewChanger::UpdateRubi_()
{
    QTreeWidgetItem *cur = rubi_tree_->currentItem();
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(cur))
        return;

    if (util.IsFolder(cur)) {
        rubi_table_->UpdateView(cur);
        main_tab_->show();
        side_tab_->hide();
    } else if (util.IsFile(cur)) {
        rubi_editor_->UpdateView(cur);
        main_tab_->hide();
        side_tab_->show();
    }
}

void ViewChanger::UpdateTrash_()
{
    QTreeWidgetItem *cur = trash_tree_->currentItem();
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(cur))
        return;

    if (util.IsFolder(cur)) {
        corkboard_->UpdateView(cur);
        main_tab_->show();
        main_editor_->hide();
    } else if (util.IsFile(cur)) {
        main_editor_->UpdateView(cur, true);
        main_tab_->hide();
        main_editor_->show();
    }
}

void ViewChanger::UpdateWorlds_()
{
    QTreeWidgetItem *cur = world_tree_->currentItem();
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(cur))
        return;

    if (util.IsFolder(cur)) {
        worlds_table_->UpdateView(cur);
        main_tab_->show();
        main_editor_->hide();
        side_tab_->hide();
    } else if (util.IsFile(cur)) {
        world_editor_->UpdateView(cur);
        main_editor_->UpdateView(cur);
        main_tab_->hide();
        main_editor_->show();
        side_tab_->show();
    }
}

void ViewChanger::UpdatePreviousPage_(GeneralType::Category category)
{
    previous_cat_ = category;
}
