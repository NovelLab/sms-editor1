#include "itemutility.h"

#include "common/generalenums.h"
#include "items/treeitem.h"

#include <QTreeWidgetItem>

ItemUtility::ItemUtility()
{

}

// methods
bool ItemUtility::IsFolder(const QTreeWidgetItem *item) const
{
    if (!IsValidTreeWidgetItem(item))
        return false;
    TreeItem *data = item->data(0, Qt::UserRole).value<TreeItem*>();
    return (data->TypeOf() == GeneralType::ItemType::Folder);
}

bool ItemUtility::IsFile(const QTreeWidgetItem *item) const
{
    if (!IsValidTreeWidgetItem(item))
        return false;
    TreeItem *data = item->data(0, Qt::UserRole).value<TreeItem*>();
    return (data->TypeOf() == GeneralType::ItemType::File);
}

bool ItemUtility::IsValidTreeWidgetItem(const QTreeWidgetItem *item) const
{
    if (!item)
        return false;
    if (!item->data(0, Qt::UserRole).canConvert<TreeItem*>())
        return false;
    return true;
}

TreeItem* ItemUtility::ItemFromTreeWidgetItem(const QTreeWidgetItem *item)
{
    if (!IsValidTreeWidgetItem(item))
        return nullptr;
    return item->data(0, Qt::UserRole).value<TreeItem*>();
}
