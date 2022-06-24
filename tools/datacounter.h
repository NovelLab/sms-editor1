#ifndef DATACOUNTER_H
#define DATACOUNTER_H

class QTreeWidgetItem;
class ItemData;

class DataCounter
{
public:
    explicit DataCounter();

    int TextCount(const QTreeWidgetItem *item);

private:
    int TextCountOfCategory_(const QTreeWidgetItem *item);
    int TextCountOfFolder_(const QTreeWidgetItem *item);
    int TextCountOfFile_(ItemData *data);
};

#endif // DATACOUNTER_H
