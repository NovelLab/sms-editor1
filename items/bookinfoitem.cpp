#include "bookinfoitem.h"

#include "enums/bookinfotypes.h"

BookInfoItem::BookInfoItem()
    : values_{QVector<QVariant>(kBookInfoTypeCount)}
{

}

BookInfoItem::~BookInfoItem()
{
    values_.clear();
}

// methods
int BookInfoItem::ColumnCount() const
{
    return values_.size();
}

QVariant BookInfoItem::DataOf(int column) const
{
    if (!IsValidColumn_(column))
        return QVariant();
    return values_.value(column);
}

bool BookInfoItem::SetData(int column, const QVariant &value)
{
    if (!IsValidColumn_(column))
        return false;
    values_[column] = value;
    return true;
}

// methods (private)
bool BookInfoItem::IsValidColumn_(int column) const
{
    return !(column < 0 || column >= values_.size());
}
