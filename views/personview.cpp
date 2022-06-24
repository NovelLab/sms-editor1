#include "personview.h"

#include "items/itemdata.h"
#include "models/personmodel.h"

#include <QTreeWidgetItem>

PersonView::PersonView(QWidget *parent)
    : BaseMainView{parent}
{

}

PersonView::~PersonView()
{

}

// overrides
void PersonView::UpdateView(const QTreeWidgetItem *item)
{
    PersonModel *model = static_cast<PersonModel*>(this->model());
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
