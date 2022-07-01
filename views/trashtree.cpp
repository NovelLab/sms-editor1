#include "trashtree.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QDebug>

TrashTree::TrashTree(QWidget *parent)
    : BaseTreeView{Category::Trash, parent}
{

}

// methods
void TrashTree::RemoveItemToTrash(QTreeWidgetItem *item)
{
    MoveItem(item, this);
}
