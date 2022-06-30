#include "rubismodel.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"

#include <QDebug>

static const QStringList kDisplayElements = {
    "Name", "Key", "Converted", "Always", "Exclusions",
};
static const int kColumnSize = kDisplayElements.count();

RubisModel::RubisModel(QObject *parent)
    : BaseTableModel{kColumnSize, parent}
{
    // set header
    for (int i = 0; i < kDisplayElements.count(); ++i)
        setHeaderData(i, Qt::Horizontal, kDisplayElements.at(i));
}

// overrides (protected)
QVariant RubisModel::DataFromFile(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == ItemType::File);

    if (column < 0 || column >= data->ColumnCount())
        return QVariant();

    switch (column) {
      case 0:// name
        return data->DataOf(0);
      case 1:// key
        return data->DataOf(1);
      case 2:// converted
        return data->DataOf(2);
      case 3:// always
        return data->DataOf(3);
      case 4:// exclusions
        return data->DataOf(4);
      default:
        return QVariant();
    }
}

bool RubisModel::SetDataOfFile(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == ItemType::File);
    if (column < 0 || column >= data->ColumnCount())
        return false;

    bool result;
    switch (column) {
      case 0:// name
        data->SetData(0, value);
        result = true;
        break;
      case 1:// key
        data->SetData(1, value);
        result = true;
        break;
      case 2:// converted
        data->SetData(2, value);
        result = true;
        break;
      case 3:// always
        data->SetData(3, value);
        result = true;
        break;
      case 4:// exclusions
        data->SetData(4, value);
        result = true;
        break;
      default:
        result = false;
        break;
    }

    return result;
}
