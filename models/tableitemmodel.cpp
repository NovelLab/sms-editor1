#include "tableitemmodel.h"

#include "common/generalenums.h"
#include "models/modeldatafactory.h"
#include "items/treeitem.h"

static const Qt::ItemFlags kItemFlags = Qt::ItemIsEnabled
        | Qt::ItemIsEditable;

TableItemModel::TableItemModel(GeneralType::Category cat, QObject *parent)
    : QAbstractItemModel{parent},
      cat_{cat}
{
    factory_ = new ModelDataFactory(cat_);
    QStringList header_strs = factory_->CreateHeaderStrings();
    for (int i = 0; i < header_strs.count(); ++i)
        setHeaderData(i, Qt::Horizontal, header_strs.at(i));
}

TableItemModel::~TableItemModel()
{
    qDeleteAll(items_);
    delete factory_;
}

// overrides
int TableItemModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
    Q_UNUSED(parent);
    Q_ASSERT(factory_);

    return factory_->ColumnCount();
}

QVariant TableItemModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *data = ItemFromIndex_(index);

    if (!data)
        return QVariant();

    if (data->TypeOf() == GeneralType::ItemType::File) {
        return factory_->FileDataFromItem(data, index.column());
    } else if (data->TypeOf() == GeneralType::ItemType::Folder) {
        return factory_->FolderDataFromItem(data, index.column());
    } else {
        return QVariant();
    }
}

Qt::ItemFlags TableItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return kItemFlags;
}

QVariant TableItemModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
    Q_ASSERT(factory_);
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return factory_->HeaderData(section);

    return QVariant();
}

QModelIndex TableItemModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *data = items_.at(row);
    return createIndex(row, column, data);
}

QModelIndex TableItemModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int TableItemModel::rowCount(const QModelIndex &parent/* QModelIndex() */) const
{
    Q_UNUSED(parent);

    return items_.size();
}

bool TableItemModel::setData(const QModelIndex &index, const QVariant &value, int role /* Qt::EditRole */)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *data = ItemFromIndex_(index);
    if (!data)
        return false;

    bool result;
    if (data->TypeOf() == GeneralType::ItemType::File) {
        result = factory_->SetFileData(data, index.column(), value);
    } else if (data->TypeOf() == GeneralType::ItemType::Folder) {
        result = factory_->SetFolderData(data, index.column(), value);
    } else {
        result = false;
    }

    emit UpdatedItemData(index);

    return result;
}

// methods
void TableItemModel::AppendChild(TreeItem *data)
{
    beginInsertRows(QModelIndex(), items_.size(), items_.size());
    items_.append(data);
    endInsertRows();
}

void TableItemModel::Clear()
{
    beginResetModel();
    items_.clear();
    endResetModel();
}


// methods (protected)
TreeItem* TableItemModel::ItemFromIndex_(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }

    return nullptr;
}
