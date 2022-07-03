#include "rubitree.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

RubiTree::RubiTree(QWidget *parent)
    : BaseTreeView{GeneralType::Category::Rubi, parent}
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
    TreeItem *data = new TreeItem(GeneralType::ItemType::File, BaseCategoryOf());
    data->SetData(ItemKeys::Rubi::Name, CreateNewFileTitle());
    data->SetData(ItemKeys::Rubi::Keyword, "key");
    data->SetData(ItemKeys::Rubi::Converted, "converted");
    data->SetData(ItemKeys::Rubi::Always, "false");
    data->SetData(ItemKeys::Rubi::Exclusions, "exclusions");
    return data;
}

QString RubiTree::CreateNewFileTitle() const
{
    return "new rubi";
}
