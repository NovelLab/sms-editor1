#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H

#include <QVariant>

namespace Config {
enum class UI;
}
class ConfigItem;

class ConfigModel
{
public:
    explicit ConfigModel();
    ~ConfigModel();

    void SetDefaultValue();

    QVariant DataOf(int column) const;
    QVariant DataOf(Config::UI key) const;

    bool SetData(int column, const QVariant &value);
    bool SetData(Config::UI key, const QVariant &value);

private:
    ConfigItem *conf_item_;
};

#endif // CONFIGMODEL_H
