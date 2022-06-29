#include "treeitem.h"

#include "enums/generaltypes.h"

static const int kColumnSize = 10;

TreeItem::TreeItem(ItemType type, Category category)
    : values_{QVector<QVariant>(kColumnSize, "")},
      type_{type},
      category_{category},
      uuid_{QUuid::createUuid()}
{

}

TreeItem::~TreeItem()
{
    values_.clear();
}

// methods
Category TreeItem::CategoryOf() const
{
    return category_;
}

int TreeItem::ColumnCount() const
{
    return values_.size();
}

QVariant TreeItem::DataOf(int column) const
{
    if (!IsValidColumn_(column))
        return QVariant();
    return values_.value(column);
}

bool TreeItem::SetData(int column, const QVariant &value)
{
    if (!IsValidColumn_(column))
        return false;
    values_[column] = value;
    return true;
}

ItemType TreeItem::TypeOf() const
{
    return type_;
}

QUuid TreeItem::UuidOf() const
{
    return uuid_;
}

// methods (private)
bool TreeItem::IsValidColumn_(int column) const
{
    return !(column < 0 || column >= values_.size());
}
