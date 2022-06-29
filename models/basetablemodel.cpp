#include "basetablemodel.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

static const Qt::ItemFlags kItemFlags = Qt::ItemIsEnabled
        | Qt::ItemIsEditable;

BaseTableModel::BaseTableModel(int display_columns, QObject *parent)
    : QAbstractItemModel{parent},
      kDisplayColumnSize_{display_columns}
{

}

BaseTableModel::~BaseTableModel()
{
    qDeleteAll(items_);
}

// overrides
int BaseTableModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
    Q_UNUSED(parent);

    return kDisplayColumnSize_;
}

QVariant BaseTableModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *data = ItemFromIndex_(index);

    if (!data)
        return QVariant();

    if (data->TypeOf() == ItemType::File) {
        return DataFromFile(data, index.column());
    } else if (data->TypeOf() == ItemType::Folder) {
        return DataFromFolder(data, index.column());
    } else {
        return QVariant();
    }
}

Qt::ItemFlags BaseTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return kItemFlags;
}

QModelIndex BaseTableModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *data = items_.at(row);
    return createIndex(row, column, data);
}

QModelIndex BaseTableModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int BaseTableModel::rowCount(const QModelIndex &parent/* QModelIndex() */) const
{
    Q_UNUSED(parent);

    return items_.size();
}

bool BaseTableModel::setData(const QModelIndex &index, const QVariant &value, int role /* Qt::EditRole */)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *data = ItemFromIndex_(index);
    if (!data)
        return false;

    bool result;
    if (data->TypeOf() == ItemType::File) {
        result = SetDataOfFile(data, index.column(), value);
    } else if (data->TypeOf() == ItemType::Folder) {
        result = SetDataOfFolder(data, index.column(), value);
    } else {
        result = false;
    }

    emit UpdatedItemData(index);

    return result;
}

// methods
void BaseTableModel::AppendChild(TreeItem *data)
{
    beginInsertRows(QModelIndex(), items_.size(), items_.size());
    items_.append(data);
    endInsertRows();
}

void BaseTableModel::Clear()
{
    beginResetModel();
    items_.clear();
    endResetModel();
}


// methods (protected)
QVariant BaseTableModel::DataFromFolder(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == ItemType::Folder);

    if (column == 0) {
        // NOTE: title only
        return data->DataOf(0);
    }
    return QVariant();
}

QVariant BaseTableModel::DataFromFile(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == ItemType::File);

    if (column < 0 || column >= data->ColumnCount())
        return QVariant();
    return data->DataOf(column);
}

TreeItem* BaseTableModel::ItemFromIndex_(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }

    return nullptr;
}

bool BaseTableModel::SetDataOfFile(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == ItemType::File);
    if (column < 0 || column >= data->ColumnCount())
        return false;

    data->SetData(column, value);
    return true;
}

bool BaseTableModel::SetDataOfFolder(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == ItemType::Folder);
    if (column == 0) {
        // NOTE: title only
        data->SetData(0, value);
        return true;
    }
    return false;
}
