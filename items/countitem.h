#ifndef COUNTITEM_H
#define COUNTITEM_H

#include <QVector>
#include <QVariant>

namespace ItemKeys {
enum class Count;
}

class CountItem
{
public:
    explicit CountItem();
    ~CountItem();

    QVariant DataOf(int column) const;
    QVariant DataOf(ItemKeys::Count key) const;
    bool SetData(int column, const QVariant &value);
    bool SetData(ItemKeys::Count key, const QVariant &value);

private:
    bool IsValidColumn_(int column) const;

    QVector<QVariant> values_;
};

#endif // COUNTITEM_H
