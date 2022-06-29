#include "worldsmodel.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"

#include <QDebug>

static const QStringList kDisplayElements = {
    "Name", "Category", "Info",
};
static const int kColumnSize = kDisplayElements.count();

WorldsModel::WorldsModel(QObject *parent)
    : BaseTableModel{kColumnSize, parent}
{
    // set header
    for (int i = 0; i < kDisplayElements.count(); ++i)
        setHeaderData(i, Qt::Horizontal, kDisplayElements.at(i));
}

// overrides (protected)
QVariant WorldsModel::DataFromFile(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == ItemType::File);

    if (column < 0 || column >= data->ColumnCount())
        return QVariant();

    switch (column) {
      case 0:// name
        return data->DataOf(0);
      case 1:// category
        return data->DataOf(4);
      case 2:// info
        return data->DataOf(1);
      default:
        return QVariant();
    }
}

bool WorldsModel::SetDataOfFile(TreeItem *data, int column, const QVariant &value)
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
      case 1:// category
        data->SetData(4, value);
        result = true;
        break;
      case 2:// info
        data->SetData(1, value);
        result = true;
        break;
      default:
        result = false;
        break;
    }

    return result;
}
