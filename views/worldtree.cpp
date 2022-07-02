#include "worldtree.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QDebug>

WorldTree::WorldTree(QWidget *parent)
    : BaseTreeView{GeneralType::Category::Persons, parent}
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
    TreeItem *data = new TreeItem(GeneralType::ItemType::File, BaseCategoryOf());
    data->SetData(ItemKeys::World::Name, CreateNewFileTitle());
    data->SetData(ItemKeys::World::Info, "world info");
    data->SetData(ItemKeys::World::Text, "new text");
    data->SetData(ItemKeys::World::Note, "note");
    data->SetData(ItemKeys::World::Division, "other");// division
    return data;
}

QString WorldTree::CreateNewFileTitle() const
{
    return "new element";
}
