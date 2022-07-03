#include "personstableview.h"

#include "items/treeitem.h"
#include "models/personsmodel.h"
#include "utils/itemutility.h"

#include <QHeaderView>
#include <QLabel>
#include <QTreeWidgetItem>

PersonsTableView::PersonsTableView(QWidget *parent)
    : QTableView{parent}
{
    this->verticalHeader()->hide();
}

// methods
void PersonsTableView::SetTitleLabel(QLabel *label)
{
    title_label_ = label;
}

void PersonsTableView::UpdateView(const QTreeWidgetItem *item)
{
    PersonsModel *model = static_cast<PersonsModel*>(this->model());
    model->Clear();

    if (!item)
        return;

    if (title_label_)
        title_label_->setText(item->text(0));

    ItemUtility util;

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        TreeItem *data = util.ItemFromTreeWidgetItem(child);
        if (data) {
            model->AppendChild(data);
        }
    }
}
