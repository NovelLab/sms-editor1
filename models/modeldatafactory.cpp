#include "modeldatafactory.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QDebug>

const QVector<int> kColumnCounts = {
    1,//BookInfo,
    2,//Draft,
    2,//Plot,
    6,//Persons,
    3,//Worlds,
    2,//Research,
    2,//Notes,
    5,//Rubi,
    1,//Trash,
    1,//None
};

const QStringList kHeaderOfBookInfo = {
    "Title",
};

const QStringList kHeaderOfDraft = {
    "Title", "Synopsys",
};

const QStringList kHeaderOfPlot = {
    "Title", "Synopsys",
};

const QStringList kHeaderOfPersons = {
    "Name", "Fullname", "Age", "Gender", "Job", "Info",
};

const QStringList kHeaderOfWorlds = {
    "Name", "Division", "Info",
};

const QStringList kHeaderOfResearch = {
    "Title", "Synopsys",
};

const QStringList kHeaderOfNotes = {
    "Title", "Synopsys",
};

const QStringList kHeaderOfRubi = {
    "Name", "Keyword", "Converted", "Always", "Exclusions",
};

const QStringList kHeaderOfTrash = {
    "Title",
};

const QStringList kHeaderOfNone = {
    "Title",
};

ModelDataFactory::ModelDataFactory(GeneralType::Category cat)
    : cat_{cat}
{

}

// methods
int ModelDataFactory::ColumnCount() const
{
    return kColumnCounts.at(static_cast<int>(cat_));
}

QStringList ModelDataFactory::CreateHeaderStrings() const
{
    QStringList header_strs;
    switch (cat_) {
      case GeneralType::Category::BookInfo:
        header_strs = kHeaderOfBookInfo;
        break;
    case GeneralType::Category::Draft:
        header_strs = kHeaderOfDraft;
        break;
    case GeneralType::Category::Plot:
        header_strs = kHeaderOfPlot;
        break;
    case GeneralType::Category::Persons:
        header_strs = kHeaderOfPersons;
        break;
    case GeneralType::Category::Worlds:
        header_strs = kHeaderOfWorlds;
        break;
    case GeneralType::Category::Research:
        header_strs = kHeaderOfResearch;
        break;
    case GeneralType::Category::Notes:
        header_strs = kHeaderOfNotes;
        break;
    case GeneralType::Category::Rubi:
        header_strs = kHeaderOfRubi;
        break;
    case GeneralType::Category::Trash:
        header_strs = kHeaderOfTrash;
        break;
    case GeneralType::Category::None:
        header_strs = QStringList{""};
        break;
    default:
        header_strs = QStringList{""};
        break;
    }
    return header_strs;
}

QVariant ModelDataFactory::FileDataFromItem(const TreeItem *data, int column) const
{
    switch (cat_) {
      case GeneralType::Category::BookInfo:
        return false;
      case GeneralType::Category::Draft:
        return FileDataOfDraft_(data, column);
      case GeneralType::Category::Plot:
        return FileDataOfPlot_(data, column);
      case GeneralType::Category::Persons:
        return FileDataOfPerson_(data, column);
      case GeneralType::Category::Worlds:
        return FileDataOfWorld_(data, column);
      case GeneralType::Category::Research:
        return FileDataOfResearch_(data, column);
      case GeneralType::Category::Notes:
        return FileDataOfNote_(data, column);
      case GeneralType::Category::Rubi:
        return FileDataOfRubi_(data, column);
      case GeneralType::Category::Trash:
        return FileDataOfTrash_(data, column);
      case GeneralType::Category::None:
        return QVariant();
      default:
        return QVariant();
    }
}

QVariant ModelDataFactory::FolderDataFromItem(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::Folder);

    if (column == 0) {
        // NOTE: title only
        return data->DataOf(0);
    }
    return QVariant();
}

QVariant ModelDataFactory::HeaderData(int section) const
{
    Q_ASSERT(section >= 0);

    switch (cat_) {
      case GeneralType::Category::BookInfo:
        return section < kHeaderOfBookInfo.count() ? kHeaderOfBookInfo.at(section): QVariant();
      case GeneralType::Category::Draft:
        return section < kHeaderOfDraft.count() ? kHeaderOfDraft.at(section): QVariant();
      case GeneralType::Category::Plot:
        return section < kHeaderOfPlot.count() ? kHeaderOfPlot.at(section): QVariant();
      case GeneralType::Category::Persons:
        return section < kHeaderOfPersons.count() ? kHeaderOfPersons.at(section): QVariant();
      case GeneralType::Category::Worlds:
        return section < kHeaderOfWorlds.count() ? kHeaderOfWorlds.at(section): QVariant();
      case GeneralType::Category::Research:
        return section < kHeaderOfResearch.count() ? kHeaderOfResearch.at(section): QVariant();
      case GeneralType::Category::Notes:
        return section < kHeaderOfNotes.count() ? kHeaderOfNotes.at(section): QVariant();
      case GeneralType::Category::Rubi:
        return section < kHeaderOfRubi.count() ? kHeaderOfRubi.at(section): QVariant();
      case GeneralType::Category::Trash:
        return section < kHeaderOfTrash.count() ? kHeaderOfTrash.at(section): QVariant();
      case GeneralType::Category::None:
        return section < kHeaderOfNone.count() ? kHeaderOfNone.at(section): QVariant();
      default:
        return QVariant();
    }
}

bool ModelDataFactory::SetFileData(TreeItem *data, int column, const QVariant &value)
{
    switch (cat_) {
      case GeneralType::Category::BookInfo:
        return false;
      case GeneralType::Category::Draft:
        return SetFileDataOfDraft_(data, column, value);
      case GeneralType::Category::Plot:
        return SetFileDataOfPlot_(data, column, value);
      case GeneralType::Category::Persons:
        return SetFileDataOfPerson_(data, column, value);
      case GeneralType::Category::Worlds:
        return SetFileDataOfWorld_(data, column, value);
      case GeneralType::Category::Research:
        return SetFileDataOfResearch_(data, column, value);
      case GeneralType::Category::Notes:
        return SetFileDataOfNote_(data, column, value);
      case GeneralType::Category::Rubi:
        return SetFileDataOfRubi_(data, column, value);
      case GeneralType::Category::Trash:
        return false;
      case GeneralType::Category::None:
        return false;
      default:
        return false;
    }
}

bool ModelDataFactory::SetFolderData(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::Folder);
    if (column == 0) {
        // NOTE: title only
        data->SetData(0, value);
        return true;
    }
    return false;
}

// methods (private)
QVariant ModelDataFactory::FileDataOfDraft_(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (!IsValidColumn_(column, GeneralType::Category::Draft))
        return QVariant();
    return data->DataOf(column);
}

QVariant ModelDataFactory::FileDataOfPlot_(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (!IsValidColumn_(column, GeneralType::Category::Plot))
        return QVariant();
    return data->DataOf(column);
}

QVariant ModelDataFactory::FileDataOfPerson_(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (!IsValidColumn_(column, GeneralType::Category::Persons))
        return QVariant();
    switch (column) {
      case 0:// name
        return data->DataOf(ItemKeys::Person::Name);
      case 1:// fullname
        return data->DataOf(ItemKeys::Person::Fullname);
      case 2:// age
        return data->DataOf(ItemKeys::Person::Age);
      case 3:// gender
        return data->DataOf(ItemKeys::Person::Gender);
      case 4:// job
        return data->DataOf(ItemKeys::Person::Job);
      case 5:// info
        return data->DataOf(ItemKeys::Person::Info);
      default:
        return QVariant();
    }
}

QVariant ModelDataFactory::FileDataOfWorld_(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (!IsValidColumn_(column, GeneralType::Category::Worlds))
        return QVariant();
    switch (column) {
      case 0:// name
        return data->DataOf(ItemKeys::World::Name);
      case 1:// division
        return data->DataOf(ItemKeys::World::Division);
      case 2:// info
        return data->DataOf(ItemKeys::World::Info);
      default:
        return QVariant();
    }
}

QVariant ModelDataFactory::FileDataOfResearch_(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (!IsValidColumn_(column, GeneralType::Category::Research))
        return QVariant();
    return data->DataOf(column);
}

QVariant ModelDataFactory::FileDataOfNote_(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (!IsValidColumn_(column, GeneralType::Category::Notes))
        return QVariant();
    return data->DataOf(column);
}

QVariant ModelDataFactory::FileDataOfRubi_(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (!IsValidColumn_(column, GeneralType::Category::Rubi))
        return QVariant();
    switch (column) {
      case 0:// name
        return data->DataOf(ItemKeys::Rubi::Name);
      case 1:// key
        return data->DataOf(ItemKeys::Rubi::Keyword);
      case 2:// converted
        return data->DataOf(ItemKeys::Rubi::Converted);
      case 3:// always
        return data->DataOf(ItemKeys::Rubi::Always);
      case 4:// exclusions
        return data->DataOf(ItemKeys::Rubi::Exclusions);
      default:
        return QVariant();
    }
}

QVariant ModelDataFactory::FileDataOfTrash_(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (!IsValidColumn_(column, GeneralType::Category::Trash))
        return QVariant();
    return data->DataOf(column);
}

bool ModelDataFactory::SetFileDataOfDraft_(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (!IsValidColumn_(column, GeneralType::Category::Draft))
        return false;

    data->SetData(column, value);
    return true;
}

bool ModelDataFactory::SetFileDataOfPlot_(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (!IsValidColumn_(column, GeneralType::Category::Plot))
        return false;

    data->SetData(column, value);
    return true;
}

bool ModelDataFactory::SetFileDataOfPerson_(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (!IsValidColumn_(column, GeneralType::Category::Persons))
        return false;

    bool result;
    switch (column) {
      case 0:// name
        data->SetData(ItemKeys::Person::Name, value);
        result = true;
        break;
      case 1:// fullname
        data->SetData(ItemKeys::Person::Fullname, value);
        result = true;
      break;
      case 2:// age
        data->SetData(ItemKeys::Person::Age, value);
        result = true;
        break;
      case 3:// gender
        data->SetData(ItemKeys::Person::Gender, value);
        result = true;
        break;
      case 4:// job
        data->SetData(ItemKeys::Person::Job, value);
        result = true;
        break;
      case 5:// info
        data->SetData(ItemKeys::Person::Info, value);
        result = true;
        break;
      default:
        result = false;
        break;
    }

    return result;
}

bool ModelDataFactory::SetFileDataOfWorld_(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (!IsValidColumn_(column, GeneralType::Category::Worlds))
        return false;

    bool result;
    switch (column) {
      case 0:// name
        data->SetData(ItemKeys::World::Name, value);
        result = true;
        break;
      case 1:// division
        data->SetData(ItemKeys::World::Division, value);
        result = true;
        break;
      case 2:// info
        data->SetData(ItemKeys::World::Info, value);
        result = true;
        break;
      default:
        result = false;
        break;
    }

    return result;
}

bool ModelDataFactory::SetFileDataOfResearch_(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (!IsValidColumn_(column, GeneralType::Category::Research))
        return false;

    data->SetData(column, value);
    return true;
}

bool ModelDataFactory::SetFileDataOfNote_(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (!IsValidColumn_(column, GeneralType::Category::Notes))
        return false;

    data->SetData(column, value);
    return true;
}

bool ModelDataFactory::SetFileDataOfRubi_(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (!IsValidColumn_(column, GeneralType::Category::Rubi))
        return false;

    bool result;
    switch (column) {
      case 0:// name
        data->SetData(ItemKeys::Rubi::Name, value);
        result = true;
        break;
      case 1:// key
        data->SetData(ItemKeys::Rubi::Keyword, value);
        result = true;
        break;
      case 2:// converted
        data->SetData(ItemKeys::Rubi::Converted, value);
        result = true;
        break;
      case 3:// always
        data->SetData(ItemKeys::Rubi::Always, value);
        result = true;
        break;
      case 4:// exclusions
        data->SetData(ItemKeys::Rubi::Exclusions, value);
        result = true;
        break;
      default:
        result = false;
        break;
    }

    return result;
}

bool ModelDataFactory::IsValidColumn_(int column, GeneralType::Category cat) const
{
    if (column < 0)
        return false;
    switch (cat) {
      case GeneralType::Category::BookInfo:
        return column < kHeaderOfBookInfo.count();
      case GeneralType::Category::Draft:
        return column < kHeaderOfDraft.count();
      case GeneralType::Category::Plot:
        return column < kHeaderOfPlot.count();
      case GeneralType::Category::Persons:
        return column < kHeaderOfPersons.count();
      case GeneralType::Category::Worlds:
        return column < kHeaderOfWorlds.count();
      case GeneralType::Category::Research:
        return column < kHeaderOfResearch.count();
      case GeneralType::Category::Notes:
        return column < kHeaderOfNotes.count();
      case GeneralType::Category::Rubi:
        return column < kHeaderOfRubi.count();
      case GeneralType::Category::Trash:
        return column < kHeaderOfTrash.count();
      case GeneralType::Category::None:
        return column < kHeaderOfNone.count();
      default:
        return false;
    }
}
