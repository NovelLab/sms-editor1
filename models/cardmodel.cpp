#include "cardmodel.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

static const int kColumnSize = 2;
static const Qt::ItemFlags kItemFlags = Qt::ItemIsEnabled
        | Qt::ItemIsEditable;

CardModel::CardModel(QObject *parent)
    : QAbstractItemModel{parent},
      kDisplayColumnSize_{kColumnSize}
{

}

CardModel::~CardModel()
{

}

// overrides
int CardModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
    Q_UNUSED(parent);

    return kDisplayColumnSize_;
}

QVariant CardModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
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

Qt::ItemFlags CardModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return kItemFlags;
}

QModelIndex CardModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *data = items_.at(row);
    return createIndex(row, column, data);
}

QModelIndex CardModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int CardModel::rowCount(const QModelIndex &parent/* QModelIndex() */) const
{
    Q_UNUSED(parent);

    return items_.size();
}

bool CardModel::setData(const QModelIndex &index, const QVariant &value, int role /* Qt::EditRole */)
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
void CardModel::AppendChild(TreeItem *data)
{
    beginInsertRows(QModelIndex(), items_.size(), items_.size());
    items_.append(data);
    endInsertRows();
}

void CardModel::Clear()
{
    beginResetModel();
    items_.clear();
    endResetModel();
}


// methods (protected)
QVariant CardModel::DataFromFolder(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == ItemType::Folder);

    if (column == 0) {
        // NOTE: title only
        return data->DataOf(0);
    }
    return QVariant();
}

QVariant CardModel::DataFromFile(const TreeItem *data, int column) const
{
    Q_ASSERT(data->TypeOf() == ItemType::File);

    if (column < 0 || column >= data->ColumnCount())
        return QVariant();
    return data->DataOf(column);
}

TreeItem* CardModel::ItemFromIndex_(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }

    return nullptr;
}

bool CardModel::SetDataOfFile(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == ItemType::File);
    if (column < 0 || column >= data->ColumnCount())
        return false;

    data->SetData(column, value);
    return true;
}

bool CardModel::SetDataOfFolder(TreeItem *data, int column, const QVariant &value)
{
    Q_ASSERT(data->TypeOf() == ItemType::Folder);
    if (column == 0) {
        // NOTE: title only
        data->SetData(0, value);
        return true;
    }
    return false;
}
