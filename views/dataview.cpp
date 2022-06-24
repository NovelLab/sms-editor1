#include "dataview.h"

#include "items/itemdata.h"
#include "models/datamodel.h"

#include <QTreeWidgetItem>

DataView::DataView(QWidget *parent)
    : BaseMainView{parent}
{

}

DataView::~DataView()
{

}

// overrides
void DataView::UpdateView(const QTreeWidgetItem *item)
{
    DataModel *model = static_cast<DataModel*>(this->model());
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
