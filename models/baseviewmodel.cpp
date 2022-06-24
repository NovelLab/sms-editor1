#include "baseviewmodel.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "tools/itemdatareader.h"
#include "tools/itemdatawriter.h"


BaseViewModel::BaseViewModel(int display_columns, QObject *parent)
    : QAbstractItemModel{parent},
      kDisplayColumnSize_{display_columns}
{
    items_.clear();
}

BaseViewModel::~BaseViewModel()
{
    qDeleteAll(items_);
}

// overrides
int BaseViewModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
    Q_UNUSED(parent);

    return kDisplayColumnSize_;
}

QVariant BaseViewModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    ItemData *data = ItemFrom_(index);

    if (!data)
        return QVariant();

    ItemDataReader reader;

    switch (index.column()) {
      case 0:// Title
        return reader.ReadTitleOrName(data);
      case 1:// Synopsys
        return reader.ReadSynopsysOrInfo(data);
      default:
        return QVariant();
    }
    return QVariant();
}

Qt::ItemFlags BaseViewModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QModelIndex BaseViewModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ItemData *data = items_.at(row);
    return createIndex(row, column, data);
}

QModelIndex BaseViewModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int BaseViewModel::rowCount(const QModelIndex &parent/* QModelIndex() */) const
{
    Q_UNUSED(parent);

    return items_.size();
}

bool BaseViewModel::setData(const QModelIndex &index, const QVariant &value, int role /* Qt::EditRole */)
{
    if (role != Qt::EditRole)
        return false;

    ItemData *data = ItemFrom_(index);
    if (!data)
        return false;

    bool result;
    ItemDataWriter writer;

    switch (index.column()) {
      case 0:// title
        writer.WriteTitleOrName(data, value.toString());
        result = true;
        break;
      case 1:// synopsys
        writer.WriteSynopsysOrInfo(data, value.toString());
        result = true;
        break;
      default:
        result = false;
        break;
    }

    emit UpdatedItemData(index);

    return result;
}

// methods
void BaseViewModel::AppendChild(ItemData *data)
{
    beginInsertRows(QModelIndex(), items_.size(), items_.size());
    items_.append(data);
    endInsertRows();
}

void BaseViewModel::Clear()
{
    beginResetModel();
    items_.clear();
    endResetModel();
}


// methods (private)
ItemData* BaseViewModel::ItemFrom_(const QModelIndex &index) const
{
    if (index.isValid()) {
        ItemData *item = static_cast<ItemData*>(index.internalPointer());
        if (item)
            return item;
    }

    return nullptr;
}
