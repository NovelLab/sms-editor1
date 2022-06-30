#include "rubitableview.h"

#include "items/treeitem.h"
#include "models/rubismodel.h"
#include "utils/itemutility.h"

#include <QHeaderView>
#include <QTreeWidgetItem>

RubiTableView::RubiTableView(QWidget *parent)
    : QTableView{parent}
{
    this->verticalHeader()->hide();
}

// methods
void RubiTableView::UpdateView(const QTreeWidgetItem *item)
{
    RubisModel *model = static_cast<RubisModel*>(this->model());
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
