#include "personstableview.h"

#include "items/treeitem.h"
#include "models/personsmodel.h"
#include "utils/itemutility.h"

#include <QTreeWidgetItem>

PersonsTableView::PersonsTableView(QWidget *parent)
    : QTableView{parent}
{

}

// methods
void PersonsTableView::UpdateView(const QTreeWidgetItem *item)
{
    PersonsModel *model = static_cast<PersonsModel*>(this->model());
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
