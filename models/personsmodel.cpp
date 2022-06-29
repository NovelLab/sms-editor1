#include "personsmodel.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"

static const QStringList kDisplayElements = {
    "Name", "Age", "Gender", "Job", "Info",
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
    Q_ASSERT(data->TypeOf() == ItemType::File);

    if (column < 0 || column >= data->ColumnCount())
        return QVariant();

    switch (column) {
      case 0:// name
        return data->DataOf(0);
      case 1:// age
        return data->DataOf(4);
      case 2:// gender
        return data->DataOf(5);
      case 3:// job
        return data->DataOf(6);
      case 4:// info
        return data->DataOf(1);
      default:
        return QVariant();
    }
}

bool PersonsModel::SetDataOfFile(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == ItemType::File);
    if (column < 0 || column >= data->ColumnCount())
        return false;

    bool result;
    data->SetData(column, value);
    switch (column) {
      case 0:// name
        data->SetData(0, value);
        result = true;
        break;
      case 1:// age
        data->SetData(4, value);
        result = true;
        break;
      case 2:// gender
        data->SetData(5, value);
        result = true;
        break;
      case 3:// job
        data->SetData(6, value);
        result = true;
        break;
      case 4:// info
        data->SetData(1, value);
        result = true;
        break;
      default:
        result = false;
        break;
    }

    return result;
}
