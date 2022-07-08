#include "centerboardview.h"

#include "common/appsettings.h"
#include "items/treeitem.h"
#include "models/tableitemmodel.h"
#include "utils/itemutility.h"

#include <QHeaderView>
#include <QLabel>
#include <QSettings>
#include <QTreeWidgetItem>

CenterBoardView::CenterBoardView(QWidget *parent)
    : QTableView{parent}
{
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
}

// slots
void CenterBoardView::UpdateUi(const QSettings *settings)
{
    QString style = "background: url(:CorkBoard.jpg)";
    this->setStyleSheet(style);
}

// methods
void CenterBoardView::SetCategory(GeneralType::Category cat)
{
    cat_ = cat;
}

void CenterBoardView::SetHeaderShow(bool isShownHorizontal, bool isShownVertical)
{
    if (isShownHorizontal)
        this->horizontalHeader()->show();

    if (isShownVertical)
        this->verticalHeader()->show();
}

void CenterBoardView::SetTitleLabel(QLabel *label)
{
    title_label_ = label;
}

void CenterBoardView::UpdateView(const QTreeWidgetItem *item)
{
    TableItemModel *model = static_cast<TableItemModel*>(this->model());
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
