#include "treeitem.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"

static const int kColumnSize = ItemKeys::kBookInfoTypeCount;

TreeItem::TreeItem(GeneralType::ItemType type, GeneralType::Category category)
    : values_{QVector<QVariant>(kColumnSize, "")},
      type_{type},
      category_{category},
      uuid_{QUuid::createUuid()}
{

}

TreeItem::TreeItem(const TreeItem &item)
{
    values_ = item.values_;
    type_ = item.type_;
    category_ = item.category_;
    uuid_ = QUuid::createUuid();
}

TreeItem::~TreeItem()
{
    values_.clear();
}

// methods
GeneralType::Category TreeItem::CategoryOf() const
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

QVariant TreeItem::DataOf(ItemKeys::CommonKey key) const {return DataOf(static_cast<int>(key));}

QVariant TreeItem::DataOf(ItemKeys::BookInfo key) const {return DataOf(static_cast<int>(key));}

QVariant TreeItem::DataOf(ItemKeys::Draft key) const {return DataOf(static_cast<int>(key));}

QVariant TreeItem::DataOf(ItemKeys::Plot key) const {return DataOf(static_cast<int>(key));}

QVariant TreeItem::DataOf(ItemKeys::Person key) const {return DataOf(static_cast<int>(key));}

QVariant TreeItem::DataOf(ItemKeys::World key) const {return DataOf(static_cast<int>(key));}

QVariant TreeItem::DataOf(ItemKeys::Research key) const {return DataOf(static_cast<int>(key));}

QVariant TreeItem::DataOf(ItemKeys::Note key) const {return DataOf(static_cast<int>(key));}

QVariant TreeItem::DataOf(ItemKeys::Rubi key) const {return DataOf(static_cast<int>(key));}

bool TreeItem::SetData(int column, const QVariant &value)
{
    if (!IsValidColumn_(column))
        return false;
    values_[column] = value;
    return true;
}

bool TreeItem::SetData(ItemKeys::CommonKey key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

bool TreeItem::SetData(ItemKeys::BookInfo key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

bool TreeItem::SetData(ItemKeys::Draft key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

bool TreeItem::SetData(ItemKeys::Plot key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

bool TreeItem::SetData(ItemKeys::Person key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

bool TreeItem::SetData(ItemKeys::World key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

bool TreeItem::SetData(ItemKeys::Research key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

bool TreeItem::SetData(ItemKeys::Note key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

bool TreeItem::SetData(ItemKeys::Rubi key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

GeneralType::ItemType TreeItem::TypeOf() const
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
