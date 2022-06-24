#include "plotview.h"

#include "items/itemdata.h"

#include "models/plotmodel.h"

#include <QTreeWidgetItem>

PlotView::PlotView(QWidget *parent)
    : BaseMainView{parent}
{

}

PlotView::~PlotView()
{

}

// overrides
void PlotView::UpdateView(const QTreeWidgetItem *item)
{
    PlotModel *model = static_cast<PlotModel*>(this->model());
    model->Clear();

    if (!item)
        return;

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (child->data(0, Qt::UserRole).canConvert<ItemData*>()) {
            ItemData *data = child->data(0, Qt::UserRole).value<ItemData*>();
            model->AppendChild(data);
        }
    }
}
