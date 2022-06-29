#include "drafttree.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"

DraftTree::DraftTree(QWidget *parent)
    : BaseTreeView{Category::Draft, parent}
{

}

// overrides
TreeItem* DraftTree::CreateFileItem_()
{
    TreeItem *data = new TreeItem(ItemType::File, BaseCategoryOf());
    data->SetData(0, "new file");
    data->SetData(1, "synopsys");
    data->SetData(2, "new text");
    data->SetData(3, "note");
    data->SetData(4, "pov");
    data->SetData(5, "stage");
    data->SetData(6, "date");
    data->SetData(7, "time");
    return data;
}
