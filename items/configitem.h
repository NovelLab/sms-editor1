#ifndef CONFIGITEM_H
#define CONFIGITEM_H

#include <QVector>
#include <QVariant>

namespace Config {
enum class UI;
}

class ConfigItem
{
public:
    ConfigItem();

    QVariant DataOf(int column) const;
    QVariant DataOf(Config::UI key) const;

    bool SetData(int column, const QVariant &value);
    bool SetData(Config::UI key, const QVariant &value);

private:
    bool IsValidColumn_(int column) const;

    QVector<QVariant> values_;
};

#endif // CONFIGITEM_H
