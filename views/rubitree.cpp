#include "rubitree.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

RubiTree::RubiTree(QWidget *parent)
    : BaseTreeView{Category::Rubi, parent}
{

}

// slots
void RubiTree::UpdateItemData(const QModelIndex &index)
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
TreeItem* RubiTree::CreateFileItem_()
{
    TreeItem *data = new TreeItem(ItemType::File, BaseCategoryOf());
    data->SetData(0, CreateNewFileTitle());
    data->SetData(1, "key");
    data->SetData(2, "converted");
    data->SetData(3, "always");
    data->SetData(4, "exclusions");
    return data;
}

QString RubiTree::CreateNewFileTitle() const
{
    return "new rubi";
}
