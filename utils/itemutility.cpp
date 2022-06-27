#include "itemutility.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"

#include <QTreeWidgetItem>

ItemUtility::ItemUtility()
{

}

// methods
TreeItem* ItemUtility::ItemFromTreeWidgetItem(const QTreeWidgetItem *item)
{
    if (!item)
        return nullptr;
    if (!item->data(0, Qt::UserRole).canConvert<TreeItem*>())
        return nullptr;
    return item->data(0, Qt::UserRole).value<TreeItem*>();
}
