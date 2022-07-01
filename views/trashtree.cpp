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
void TrashTree::ClearAllItems()
{
    for (int i = 0; i < this->topLevelItemCount(); ++i) {
        QTreeWidgetItem *par = this->topLevelItem(i);
        for (int j = 0; j < par->childCount(); ++j) {
            QTreeWidgetItem *child = par->child(i);
            par->removeChild(child);
            delete child;
        }
        delete par;
    }
    this->clear();
}

void TrashTree::RemoveItemToTrash(QTreeWidgetItem *item)
{
    MoveItem(item, this);
}
