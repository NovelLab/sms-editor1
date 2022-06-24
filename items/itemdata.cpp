#include "itemdata.h"

ItemData::ItemData(DataType type, FileType ftype, int size /* kDataSize */)
    : values_{QVector<QVariant>(size)},
      type_{type},
      file_type_{ftype}
{

}

ItemData::~ItemData()
{
    values_.clear();
}

// methods
int ItemData::ColumnCount() const
{
    return values_.size();
}

QVariant ItemData::DataOf(int column) const
{
    if (!ValidColumn_(column))
        return QVariant();

    return values_.value(column);
}

FileType ItemData::FileTypeOf() const
{
    return file_type_;
}

void ItemData::SetData(int column, const QVariant &value)
{
    if (!ValidColumn_(column))
        return;

    values_[column] = value;
}

DataType ItemData::TypeOf() const
{
    return type_;
}

// methods (private)
bool ItemData::ValidColumn_(int column) const
{
    if (column < 0 || column >= values_.size())
        return false;
    return true;
}
