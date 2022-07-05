#include "countitem.h"

#include "common/itemkeys.h"

static const int kColumnSize = ItemKeys::kCountSize;

CountItem::CountItem()
    : values_{QVector<QVariant>(kColumnSize, 0)}
{

}

CountItem::~CountItem()
{
    values_.clear();
}

// methods
QVariant CountItem::DataOf(int column) const
{
    if (!IsValidColumn_(column))
        return QVariant();
    return values_.value(column);
}

QVariant CountItem::DataOf(ItemKeys::Count key) const {return DataOf(static_cast<int>(key));}

bool CountItem::SetData(int column, const QVariant &value)
{
    if (!IsValidColumn_(column))
        return false;
    values_[column] = value;
    return true;
}

bool CountItem::SetData(ItemKeys::Count key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

// methods (private)
bool CountItem::IsValidColumn_(int column) const
{
    return !(column < 0 || column >= values_.size());
}
