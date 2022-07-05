#ifndef COUNTER_H
#define COUNTER_H

class QTreeWidgetItem;

class CountItem;

namespace ItemKeys {
enum class Count;
}

class Counter
{
public:
    explicit Counter();

    CountItem* TextCharCountFrom(const QTreeWidgetItem *item);

private:
    int CountFolder_(const QTreeWidgetItem *item, ItemKeys::Count type);
    int CountFile_(const QTreeWidgetItem *item, ItemKeys::Count type);
};

#endif // COUNTER_H
