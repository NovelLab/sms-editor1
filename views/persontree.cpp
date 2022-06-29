#include "persontree.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"

PersonTree::PersonTree(QWidget *parent)
    : BaseTreeView{Category::Persons, parent}
{

}

// overrides
TreeItem* PersonTree::CreateFileItem_()
{
    TreeItem *data = new TreeItem(ItemType::File, BaseCategoryOf());
    data->SetData(0, CreateNewFileTitle());
    data->SetData(1, "person info");
    data->SetData(2, "new text");
    data->SetData(3, "note");
    data->SetData(4, "age");
    data->SetData(5, "gender");
    data->SetData(6, "job");
    data->SetData(7, "appearance");
    return data;
}

QString PersonTree::CreateNewFileTitle() const
{
    return "new person";
}
