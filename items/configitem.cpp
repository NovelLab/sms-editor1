#include "configitem.h"

#include "common/configenums.h"

ConfigItem::ConfigItem()
    : values_{QVector<QVariant>(Config::kConfigDataCount)}
{

}

ConfigItem::~ConfigItem()
{
    values_.clear();
}

// methods
int ConfigItem::ColumnCount() const
{
    return values_.size();
}

QVariant ConfigItem::DataOf(int column) const
{
    if (!IsValidColumn_(column))
        return QVariant();
    return values_.value(column);
}

QVariant ConfigItem::DataOf(Config::UI key) const {return DataOf(static_cast<int>(key));}

bool ConfigItem::SetData(int column, const QVariant &value)
{
    if (!IsValidColumn_(column))
        return false;
    values_[column] = value;
    return true;
}

bool ConfigItem::SetData(Config::UI key, const QVariant &value) {return SetData(static_cast<int>(key), value);}

// methods (private)
bool ConfigItem::IsValidColumn_(int column) const
{
    return !(column < 0 || column >= values_.size());
}
