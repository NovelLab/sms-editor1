#include "personsmodel.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"

#include <QDebug>

static const QStringList kDisplayElements = {
    "Name", "Fullname", "Age", "Gender", "Job", "Info",
};
static const int kColumnSize = kDisplayElements.count();

PersonsModel::PersonsModel(QObject *parent)
    : BaseTableModel{kColumnSize, parent}
{
    // set header
    for (int i = 0; i < kDisplayElements.count(); ++i)
        setHeaderData(i, Qt::Horizontal, kDisplayElements.at(i));
}

// overrides (protected)
QVariant PersonsModel::DataFromFile(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (column < 0 || column >= data->ColumnCount())
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

bool PersonsModel::SetDataOfFile(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (column < 0 || column >= data->ColumnCount())
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
