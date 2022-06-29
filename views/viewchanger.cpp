#include "viewchanger.h"

#include "ui_mainwindow.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "views/bookinfoview.h"
#include "utils/itemutility.h"

#include <QTreeWidgetItem>

#include <QDebug>

ViewChanger::ViewChanger(Ui::MainWindow *ui)
    :previous_cat_{Category::None}
{
    // set ui widgets
    outline_tab_ = ui->outlineTab;
    main_tab_ = ui->mainViewTab;
    main_editor_ = ui->mainEditor;
    side_tab_ = ui->sideTab;

    bookinfo_view_ = new BookInfoView(ui);
    draft_tree_ = ui->draftTreeView;
    corkboard_ = ui->corkboardView;
}

ViewChanger::~ViewChanger()
{
    delete bookinfo_view_;
    delete draft_tree_;
    delete corkboard_;

    delete outline_tab_;
    delete main_tab_;
    delete main_editor_;
    delete side_tab_;
}

// methods
void ViewChanger::Change(Category category)
{
    SavePreviousPageData_(category);

    switch (category) {
      case Category::BookInfo:
        ChangeBookInfo_();
        break;
      case Category::Draft:
        ChangeDraft_();
        break;
      case Category::Plot:
        ChangePlot_();
        break;
      case Category::Persons:
        ChangePersons_();
        break;
      case Category::Worlds:
        ChangeWorlds_();
        break;
      case Category::Research:
        ChangeResearch_();
        break;
      case Category::Notes:
        ChangeNotes_();
        break;
      case Category::Rubi:
        ChangeRubi_();
        break;
      case Category::Trash:
        ChangeTrash_();
        break;
      default:
        qWarning() << "unreachable in change view: Category is: " << static_cast<int>(category);
        break;
    }
}

/*
 * NOTE: ここではdata→viewという反映のみ行うこと
 * */
void ViewChanger::Update(Category category)
{
    switch (category) {
      case Category::BookInfo:
        UpdateBookInfo_();
        break;
      case Category::Draft:
        UpdateDraft_();
        break;
      case Category::Plot:
        qDebug() << "(unimp) update plot";
        break;
      case Category::Persons:
        qDebug() << "(unimp) update persons";
        break;
      case Category::Worlds:
        qDebug() << "(unimp) update worlds";
        break;
      case Category::Research:
        qDebug() << "(unimp) update research";
        break;
      case Category::Notes:
        qDebug() << "(unimp) update notes";
        break;
      case Category::Rubi:
        qDebug() << "(unimp) update rubi";
        break;
      case Category::Trash:
        qDebug() << "(unimp) update trash";
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
    UpdatePreviousPage_(Category::BookInfo);
}

void ViewChanger::ChangeDraft_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::ON);
    ChangeOutlineTree_(OutlineCat::Draft);
    ChangeMainTab_(MainTabCat::Corkboard);
    ChangeSideTab_(SideTabCat::Draft);
    UpdatePreviousPage_(Category::Draft);
}

void ViewChanger::ChangePlot_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::ON);
    ChangeOutlineTree_(OutlineCat::Plot);
    ChangeMainTab_(MainTabCat::Corkboard);
    ChangeSideTab_(SideTabCat::Plot);
    UpdatePreviousPage_(Category::Plot);
}

void ViewChanger::ChangePersons_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::ON);
    ChangeOutlineTree_(OutlineCat::Persons);
    ChangeMainTab_(MainTabCat::PersonsTable);
    ChangeSideTab_(SideTabCat::Persons);
    UpdatePreviousPage_(Category::Persons);
}

void ViewChanger::ChangeWorlds_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::ON);
    ChangeOutlineTree_(OutlineCat::Worlds);
    ChangeMainTab_(MainTabCat::WorldsTable);
    ChangeSideTab_(SideTabCat::Worlds);
    UpdatePreviousPage_(Category::Worlds);
}

void ViewChanger::ChangeResearch_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Research);
    ChangeMainTab_(MainTabCat::Corkboard);
    UpdatePreviousPage_(Category::Research);
}

void ViewChanger::ChangeNotes_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Notes);
    ChangeMainTab_(MainTabCat::Corkboard);
    UpdatePreviousPage_(Category::Notes);
}

void ViewChanger::ChangeRubi_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Rubi);
    ChangeMainTab_(MainTabCat::RubiTable);
    UpdatePreviousPage_(Category::Rubi);
}

void ViewChanger::ChangeTrash_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
    ChangeOutlineTree_(OutlineCat::Trash);
    ChangeMainTab_(MainTabCat::Corkboard);
    UpdatePreviousPage_(Category::Trash);
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

void ViewChanger::UpdateBookInfo_()
{
    bookinfo_view_->UpdateView();
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
    } else if (util.IsFile(cur)) {
        main_editor_->UpdateView(cur);
        main_tab_->hide();
        main_editor_->show();
    }
}

void ViewChanger::UpdatePreviousPage_(Category category)
{
    previous_cat_ = category;
}

void ViewChanger::SavePreviousPageData_(Category category)
{
    if (previous_cat_ != category) {
        switch (previous_cat_) {
          case Category::BookInfo:
            bookinfo_view_->SaveData();
            break;
          case Category::Draft:
            main_editor_->SaveCurrentItem();
            break;
          case Category::Plot:
            main_editor_->SaveCurrentItem();
            break;
          case Category::Persons:
            break;
          case Category::Worlds:
            break;
          case Category::Research:
            break;
          case Category::Notes:
            break;
          case Category::Rubi:
            break;
          case Category::Trash:
            break;
          default:
            qWarning() << "unreachable in change view: Category is: " << static_cast<int>(category);
            break;
        }
    }
}

void ViewChanger::ShowHideViews_(ViewDisp outline, ViewDisp mtab, ViewDisp editor, ViewDisp side)
{
    outline_tab_->setVisible(static_cast<bool>(outline));
    main_tab_->setVisible(static_cast<bool>(mtab));
    main_editor_->setVisible(static_cast<bool>(editor));
    side_tab_->setVisible(static_cast<bool>(side));
}
