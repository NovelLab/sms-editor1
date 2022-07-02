#include "worldsmodel.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"

#include <QDebug>

static const QStringList kDisplayElements = {
    "Name", "Division", "Info",
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
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (column < 0 || column >= data->ColumnCount())
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

bool WorldsModel::SetDataOfFile(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (column < 0 || column >= data->ColumnCount())
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
