#include "basetreeview.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"

#include "utils/itemutility.h"

#include <QMimeData>
#include <QDropEvent>

#include <QDebug>

static const QStringList kMimeTypes = {"text/plain"};
static const Qt::ItemFlags kItemFlags = Qt::ItemIsEnabled
        | Qt::ItemIsEditable
        | Qt::ItemIsDragEnabled
        | Qt::ItemIsDropEnabled;

BaseTreeView::BaseTreeView(Category category, QWidget *parent)
    : QTreeWidget{parent},
      base_category_{category}
{
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setDefaultDropAction(Qt::MoveAction);
    this->setDragDropOverwriteMode(false);

    connect(this, &QTreeWidget::itemChanged, this, &BaseTreeView::OnTitleChanged);
}

BaseTreeView::~BaseTreeView()
{

}

// slots
void BaseTreeView::UpdateItemData(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QTreeWidgetItem *par = this->currentItem();
    if (!par)
        return;

    TreeItem *data = static_cast<TreeItem*>(index.internalPointer());
    if (!data
            || index.column() < 0 || index.column() >= data->ColumnCount()
            || index.row() < 0 || index.row() >= par->childCount())
        return;

    ItemUtility util;
    TreeItem *dst = util.ItemFromTreeWidgetItem(par->child(index.row()));
    if (data->UuidOf() == dst->UuidOf()) {
        par->child(index.row())->setText(index.column(), data->DataOf(index.column()).toString());
    }
}

// methods
void BaseTreeView::AddFile(const QTreeWidgetItem *item)
{
    const QTreeWidgetItem *par = GetParentOrRoot_(item);
    QTreeWidgetItem *child = CreateChild_(par);
    child->setText(0, "new file");

    TreeItem *data = CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));
}

void BaseTreeView::AddFolder(const QTreeWidgetItem *item)
{
    const QTreeWidgetItem *par = GetParentOrRoot_(item);
    QTreeWidgetItem *child = CreateChild_(par);

    TreeItem *data = CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));
}

Qt::ItemFlags BaseTreeView::Flags() const
{
    return kItemFlags;
}

void BaseTreeView::RemoveItem(QTreeWidgetItem *item)
{
    if (!item)
        return;

    QTreeWidgetItem *par = item->parent();
    if (par)
        par->removeChild(item);

    delete item;
}

// methods (protected)
Category BaseTreeView::BaseCategoryOf() const
{
    return base_category_;
}

QTreeWidgetItem* BaseTreeView::CreateChild_(const QTreeWidgetItem *item)
{
    QTreeWidgetItem *child = new QTreeWidgetItem(const_cast<QTreeWidgetItem*>(item));
    child->setText(0, "NEW");
    child->setFlags(child->flags() | Flags());
    return child;
}

TreeItem* BaseTreeView::CreateFileItem_()
{
    TreeItem *data = new TreeItem(ItemType::File, base_category_);
    data->SetData(0, "new file");
    data->SetData(1, "synopsys");
    data->SetData(2, "new text");
    data->SetData(3, "note");
    return data;
}

TreeItem* BaseTreeView::CreateFolderItem_()
{
    TreeItem *data = new TreeItem(ItemType::Folder, base_category_);
    data->SetData(0, "NEW");
    return data;
}

const QTreeWidgetItem* BaseTreeView::GetParentOrRoot_(const QTreeWidgetItem *item) const
{
    return item ? item: this->invisibleRootItem();
}

QMimeData* BaseTreeView::mimeData(const QList<QTreeWidgetItem *> items) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    ItemUtility util;

    for (int i = 0; i < items.count(); ++i) {
        QTreeWidgetItem *child = items.at(i);
        TreeItem *data = util.ItemFromTreeWidgetItem(child);
        if (data) {
            stream << child->text(0) << data;
        }
    }

    mimeData->setData("text/plain", encodedData);
    return mimeData;
}

QStringList BaseTreeView::mimeTypes() const
{
    return kMimeTypes;
}

void BaseTreeView::dropEvent(QDropEvent *event)
{
    if (this->dropIndicatorPosition() == QAbstractItemView::OnItem) {
        // NOTE: checking enable to move, which dst item is file or folder.
        //QTreeWidgetItem *cur = this->currentItem();
        QTreeWidgetItem *dst = this->itemAt(event->pos());
        if (!dst)
            return;
        ItemUtility util;
        TreeItem *data = util.ItemFromTreeWidgetItem(dst);
        if (!data)
            return;
        if (data->TypeOf() == ItemType::File)
            return;
    }
    QTreeWidget::dropEvent(event);
}

// slots (private)
void BaseTreeView::OnTitleChanged(QTreeWidgetItem *item, int column)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;

    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (column < 0 || column >= data->ColumnCount())
        return;

    data->SetData(0, item->text(0));
}
