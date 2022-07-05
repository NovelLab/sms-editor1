#include "configmodel.h"

#include "common/appsettings.h"
#include "common/configenums.h"
#include "items/configitem.h"

#include <QApplication>
#include <QFont>

ConfigModel::ConfigModel()
{
    conf_item_ = new ConfigItem();

    SetDefaultValue();
}

ConfigModel::~ConfigModel()
{
    delete conf_item_;
}

// methods
QVariant ConfigModel::DataOf(int column) const
{
    if (!conf_item_)
        return QVariant();
    return conf_item_->DataOf(column);
}

QVariant ConfigModel::DataOf(Config::UI key) const
{
    if (!conf_item_)
        return QVariant();
    return conf_item_->DataOf(key);
}

bool ConfigModel::SetData(int column, const QVariant &value)
{
    if (!conf_item_)
        return false;
    return conf_item_->SetData(column, value);
}

bool ConfigModel::SetData(Config::UI key, const QVariant &value) {
    if (!conf_item_)
        return false;
    return conf_item_->SetData(key, value);
}

void ConfigModel::SetDefaultValue()
{
    // UI
    conf_item_->SetData(Config::UI::FontFamily, qApp->font().defaultFamily());
    conf_item_->SetData(Config::UI::FontSize, DefaultSettings::kFontSize);
    conf_item_->SetData(Config::UI::FontColor, DefaultSettings::kFontColor);
}
