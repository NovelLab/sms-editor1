#include "viewchanger.h"

#include "enums/generaltypes.h"

#include <QDebug>

ViewChanger::ViewChanger()
{

}

ViewChanger::~ViewChanger()
{

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
    qDebug() << "(unimp) change to book info.";
}

void ViewChanger::ChangeDraft_()
{
    qDebug() << "(unimp) change to draft.";
}

void ViewChanger::ChangePlot_()
{
    qDebug() << "(unimp) change to plot.";
}

void ViewChanger::ChangePersons_()
{
    qDebug() << "(unimp) change to persons.";
}

void ViewChanger::ChangeWorlds_()
{
    qDebug() << "(unimp) change to worlds.";
}

void ViewChanger::ChangeResearch_()
{
    qDebug() << "(unimp) change to research.";
}

void ViewChanger::ChangeNotes_()
{
    qDebug() << "(unimp) change to note.";
}

void ViewChanger::ChangeRubi_()
{
    qDebug() << "(unimp) change to rubi.";
}

void ViewChanger::ChangeTrash_()
{
    qDebug() << "(unimp) change to trash.";
}
