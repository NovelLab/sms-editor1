#include "corkboardview.h"

#include "items/treeitem.h"
#include "models/cardmodel.h"
#include "utils/itemutility.h"

#include <QHeaderView>
#include <QTreeWidgetItem>

CorkboardView::CorkboardView(QWidget *parent)
    : QTableView{parent}
{
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
}

CorkboardView::~CorkboardView()
{

}

// methods
void CorkboardView::UpdateView(const QTreeWidgetItem *item)
{
    CardModel *model = static_cast<CardModel*>(this->model());
    model->Clear();

    if (!item)
        return;

    ItemUtility util;

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        TreeItem *data = util.ItemFromTreeWidgetItem(child);
        if (data) {
            model->AppendChild(data);
        }
    }
}
