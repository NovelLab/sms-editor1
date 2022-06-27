#include "viewchanger.h"

#include "ui_mainwindow.h"

#include "enums/generaltypes.h"

#include <QDebug>

ViewChanger::ViewChanger(Ui::MainWindow *ui)
{
    // set ui widgets
    outline_tab_ = ui->outlineTab;
    main_tab_ = ui->mainViewTab;
    main_editor_ = ui->mainEditor;
    side_tab_ = ui->sideTab;
}

ViewChanger::~ViewChanger()
{
    delete outline_tab_;
    delete main_tab_;
    delete main_editor_;
    delete side_tab_;
}

// methods
void ViewChanger::Change(Category category)
{
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

// methods (private)
void ViewChanger::ChangeBookInfo_()
{
    ShowHideViews_(ViewDisp::OFF, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
}

void ViewChanger::ChangeDraft_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::ON);
}

void ViewChanger::ChangePlot_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::ON);
}

void ViewChanger::ChangePersons_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::ON);
}

void ViewChanger::ChangeWorlds_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::ON);
}

void ViewChanger::ChangeResearch_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
}

void ViewChanger::ChangeNotes_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
}

void ViewChanger::ChangeRubi_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
}

void ViewChanger::ChangeTrash_()
{
    ShowHideViews_(ViewDisp::ON, ViewDisp::ON, ViewDisp::OFF, ViewDisp::OFF);
}

void ViewChanger::ShowHideViews_(ViewDisp outline, ViewDisp mtab, ViewDisp editor, ViewDisp side)
{
    outline_tab_->setVisible(static_cast<bool>(outline));
    main_tab_->setVisible(static_cast<bool>(mtab));
    main_editor_->setVisible(static_cast<bool>(editor));
    side_tab_->setVisible(static_cast<bool>(side));
}
