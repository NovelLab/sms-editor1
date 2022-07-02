#include "drafttree.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"

DraftTree::DraftTree(QWidget *parent)
    : BaseTreeView{GeneralType::Category::Draft, parent}
{

}

// overrides
TreeItem* DraftTree::CreateFileItem_()
{
    TreeItem *data = new TreeItem(GeneralType::ItemType::File, BaseCategoryOf());
    data->SetData(ItemKeys::Draft::Title, "new file");
    data->SetData(ItemKeys::Draft::Synopsys, "synopsys");
    data->SetData(ItemKeys::Draft::Text, "new text");
    data->SetData(ItemKeys::Draft::Note, "note");
    data->SetData(ItemKeys::Draft::POV, "pov");
    data->SetData(ItemKeys::Draft::Stage, "stage");
    data->SetData(ItemKeys::Draft::Date, "date");
    data->SetData(ItemKeys::Draft::Time, "time");
    return data;
}
