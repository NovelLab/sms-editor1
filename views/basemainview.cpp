#include "basemainview.h"

#include "items/itemdata.h"

#include "models/baseviewmodel.h"

#include <QHeaderView>
#include <QTreeWidgetItem>

BaseMainView::BaseMainView(QWidget *parent)
    : QTableView{parent}
{
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
}

BaseMainView::~BaseMainView()
{

}

// methods
void BaseMainView::UpdateView(const QTreeWidgetItem *item)
{
}
