#include "persontree.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QDebug>

PersonTree::PersonTree(QWidget *parent)
    : BaseTreeView{GeneralType::Category::Persons, parent}
{

}

// slots
void PersonTree::UpdateItemData(const QModelIndex &index)
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
TreeItem* PersonTree::CreateFileItem_()
{
    TreeItem *data = new TreeItem(GeneralType::ItemType::File, BaseCategoryOf());
    data->SetData(0, CreateNewFileTitle());
    QStringList vals = {
        "person info",
        "new text",
        "note",
        "fullname",
        "age",
        "gender",
        "job",
        "appearance",
    };
    for (int i = 0; i < vals.count(); ++i) {
        data->SetData(i + 1, vals.at(i));
    }
    return data;
}

QString PersonTree::CreateNewFileTitle() const
{
    return "new person";
}
