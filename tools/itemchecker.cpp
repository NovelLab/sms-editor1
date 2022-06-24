#include "itemchecker.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "tools/itemdatareader.h"

#include <QTreeWidgetItem>

#include <QDebug>


ItemChecker::ItemChecker()
{
}

// methods
bool ItemChecker::IsCategory(const QTreeWidgetItem *item)
{
    return IsDataType_(item, DataType::Category);
}

bool ItemChecker::IsFile(const QTreeWidgetItem *item)
{
    return IsDataType_(item, DataType::File);
}

bool ItemChecker::IsFolder(const QTreeWidgetItem *item)
{
    return IsDataType_(item, DataType::Folder);
}

bool ItemChecker::IsGenerel(const QTreeWidgetItem *item)
{
    if (!IsValidItem(item))
        return false;

    ItemData *data = DataFrom_(item);
    ItemDataReader reader;
    if (data->TypeOf() == DataType::Category
            && data->FileTypeOf() == FileType::None
            && reader.ReadTitleOfName(data) == "General"
            && item->data(1, Qt::UserRole).canConvert<ItemData*>()) {
        return true;
    }
    return false;
}

bool ItemChecker::IsTrash(const QTreeWidgetItem *item)
{
    if (!IsValidItem(item))
        return false;

    ItemData *data = DataFrom_(item);
    ItemDataReader reader;
    if (data->TypeOf() == DataType::Category
            && data->FileTypeOf() == FileType::None
            && reader.ReadTitleOfName(data) == "Trash") {
        return true;
    }
    return false;
}

bool ItemChecker::IsValidItem(const QTreeWidgetItem *item)
{
    if (!item)
        return false;

    if (!item->data(0, Qt::UserRole).canConvert<ItemData*>())
        return false;

    return true;
}

// methods (privete)
ItemData* ItemChecker::DataFrom_(const QTreeWidgetItem *item)
{
    return item->data(0, Qt::UserRole).value<ItemData*>();
}

bool ItemChecker::IsDataType_(const QTreeWidgetItem *item, DataType type)
{
    if (!IsValidItem(item))
        return false;
    ItemData *data = DataFrom_(item);
    if (data->TypeOf() == type)
        return true;
    return false;
}
