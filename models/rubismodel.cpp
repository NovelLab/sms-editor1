#include "rubismodel.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
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
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);

    if (column < 0 || column >= data->ColumnCount())
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

bool RubisModel::SetDataOfFile(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == GeneralType::ItemType::File);
    if (column < 0 || column >= data->ColumnCount())
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
