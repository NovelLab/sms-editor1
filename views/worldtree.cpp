#include "worldtree.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QDebug>

WorldTree::WorldTree(QWidget *parent)
    : BaseTreeView{Category::Persons, parent}
{
}

// slots
void WorldTree::UpdateItemData(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QTreeWidgetItem *par = this->currentItem();
    if (!par)
        return;

    TreeItem *data = static_cast<TreeItem*>(index.internalPointer());
    if (!data
            || index.column() < 0 || index.column() >= data->ColumnCount()
            || index.row() < 0 || index.row() >= par->childCount())
        return;

    ItemUtility util;
    TreeItem *dst = util.ItemFromTreeWidgetItem(par->child(index.row()));
    if (data->UuidOf() == dst->UuidOf()) {
        par->child(index.row())->setText(index.column(), data->DataOf(index.column()).toString());
    }
}

// overrides
TreeItem* WorldTree::CreateFileItem_()
{
    TreeItem *data = new TreeItem(ItemType::File, BaseCategoryOf());
    data->SetData(0, CreateNewFileTitle());
    data->SetData(1, "world info");
    data->SetData(2, "new text");
    data->SetData(3, "note");
    data->SetData(4, "other");// category
    return data;
}

QString WorldTree::CreateNewFileTitle() const
{
    return "new element";
}
