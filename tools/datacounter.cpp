#include "datacounter.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "tools/itemdatareader.h"

#include <QTreeWidgetItem>

#include <QDebug>

DataCounter::DataCounter()
{

}

// methods
int DataCounter::TextCount(const QTreeWidgetItem *item)
{
    if (!item)
        return 0;

    if (!item->data(0, Qt::UserRole).canConvert<ItemData*>())
        return 0;

    ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
    int count = 0;

    if (data->TypeOf() == DataType::Category) {
        count += TextCountOfCategory_(item);
    } else if (data->TypeOf() == DataType::Folder) {
        count += TextCountOfFolder_(item);
    } else if (data->TypeOf() == DataType::File) {
        count += TextCountOfFile_(data);
    }

    return count;
}

// methods (private)
int DataCounter::TextCountOfCategory_(const QTreeWidgetItem *item)
{
    if (!item)
        return 0;
    int count = 0;

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        count += TextCount(child);
    }
    return count;
}

int DataCounter::TextCountOfFile_(ItemData *data)
{
    if (!data)
        return 0;
    int count = 0;
    ItemDataReader reader;
    QStringList strs = reader.ReadText(data).toString().split('\n');
    for (int i = 0; i < strs.count(); ++i) {
        count += strs.at(i).trimmed().simplified().size();
    }
    return count;
}

int DataCounter::TextCountOfFolder_(const QTreeWidgetItem *item)
{
    if (!item)
        return 0;
    int count = 0;
    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        count += TextCount(child);
    }
    return count;
}
