#include "centerboardview.h"

#include "items/treeitem.h"
#include "utils/itemutility.h"

CenterBoardView::CenterBoardView(QWidget *parent)
    : QTableView{parent}
{

}

// methods
void CenterBoardView::SetCategory(GeneralType::Category cat)
{
    cat_ = cat;
}

void CenterBoardView::UpdateView(const QTreeWidgetItem *item)
{

}
