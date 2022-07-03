#include "worldstableview.h"

#include "items/treeitem.h"
#include "models/worldsmodel.h"
#include "utils/itemutility.h"

#include <QHeaderView>
#include <QLabel>
#include <QTreeWidgetItem>

WorldsTableView::WorldsTableView(QWidget *parent)
    : QTableView{parent}
{
    this->verticalHeader()->hide();
}

// methods
void WorldsTableView::SetTitleLabel(QLabel *label)
{
    title_label_ = label;
}

void WorldsTableView::UpdateView(const QTreeWidgetItem *item)
{
    WorldsModel *model = static_cast<WorldsModel*>(this->model());
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
