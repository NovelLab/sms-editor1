#include "basetreeview.h"

#include "common/generalenums.h"
#include "items/treeitem.h"

#include "utils/itemutility.h"

#include <QAction>
#include <QDropEvent>
#include <QFileIconProvider>
#include <QMenu>
#include <QMimeData>

#include <QDebug>

static const QStringList kMimeTypes = {"text/plain"};
static const Qt::ItemFlags kItemFlags = Qt::ItemIsEnabled
        | Qt::ItemIsEditable
        | Qt::ItemIsDragEnabled
        | Qt::ItemIsDropEnabled;

BaseTreeView::BaseTreeView(GeneralType::Category category, QWidget *parent)
    : QTreeWidget{parent},
      base_category_{category}
{
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setDefaultDropAction(Qt::MoveAction);
    this->setDragDropOverwriteMode(false);

    // NOTE: custom menu using
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &QTreeWidget::itemChanged, this, &BaseTreeView::OnTitleChanged);
    connect(this, &QTreeWidget::customContextMenuRequested, this, &BaseTreeView::ContextMenu);
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
    ItemUtility util;
    if (item && util.IsFile(item))
        return;

    const QTreeWidgetItem *par = GetParentOrRoot_(item);
    QTreeWidgetItem *child = CreateChild_(par);
    child->setText(0, CreateNewFileTitle());

    QFileIconProvider provider;
    QIcon icon = provider.icon(QFileIconProvider::File);
    child->setIcon(0, icon);

    TreeItem *data = CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));
}

void BaseTreeView::AddFolder(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (item && util.IsFile(item))
        return;

    const QTreeWidgetItem *par = GetParentOrRoot_(item);
    QTreeWidgetItem *child = CreateChild_(par);

    QFileIconProvider provider;
    QIcon icon = provider.icon(QFileIconProvider::Folder);
    child->setIcon(0, icon);

    TreeItem *data = CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));
}

Qt::ItemFlags BaseTreeView::Flags() const
{
    return kItemFlags;
}

void BaseTreeView::MoveItem(QTreeWidgetItem *item, BaseTreeView *view)
{
    if (!item)
        return;

    QTreeWidgetItem *par = item->parent();
    if (par)
        par->removeChild(item);

    QTreeWidgetItem *new_item = item->clone();
    view->addTopLevelItem(new_item);
    delete item;
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
GeneralType::Category BaseTreeView::BaseCategoryOf() const
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
    TreeItem *data = new TreeItem(GeneralType::ItemType::File, base_category_);
    data->SetData(0, CreateNewFileTitle());
    data->SetData(1, "synopsys");
    data->SetData(2, "new text");
    data->SetData(3, "note");
    return data;
}

TreeItem* BaseTreeView::CreateFolderItem_()
{
    TreeItem *data = new TreeItem(GeneralType::ItemType::Folder, base_category_);
    data->SetData(0, "NEW");
    return data;
}

QString BaseTreeView::CreateNewFileTitle() const
{
    return "new file";
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
        if (data->TypeOf() == GeneralType::ItemType::File)
            return;
    }
    QTreeWidget::dropEvent(event);
}

// slots (private)
void BaseTreeView::ContextMenu(const QPoint &pos)
{
    QMenu menu(this);

    QAction *actAddFolder = new QAction("New folder", this);
    connect(actAddFolder, &QAction::triggered,
            [=](){
        AddFolder(this->currentItem());
    });
    menu.addAction(actAddFolder);

    QAction *actAddFile = new QAction("New file", this);
    connect(actAddFile, &QAction::triggered,
            [=](){
        AddFile(this->currentItem());
    });
    menu.addAction(actAddFile);

    QAction *actDelFile = new QAction("Delete", this);
    connect(actDelFile, &QAction::triggered,
            [=](){
        RemoveItem(this->currentItem());
    });
    menu.addAction(actDelFile);

    menu.exec(mapToGlobal(pos));
}

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
