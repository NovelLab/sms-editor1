#include "outlineview.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "views/itemfactory.h"
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

OutlineView* OutlineView::trash_;

OutlineView::OutlineView(QWidget *parent)
    : QTreeWidget{parent},
      cat_{GeneralType::Category::None}
{
    factory_ = nullptr;

    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setDefaultDropAction(Qt::MoveAction);
    this->setDragDropOverwriteMode(false);

    // NOTE: custom menu using
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &QTreeWidget::itemChanged, this, &OutlineView::OnTitleChanged);
    connect(this, &QTreeWidget::customContextMenuRequested, this, &OutlineView::ContextMenu);
}

OutlineView::~OutlineView()
{
    delete factory_;
}

// overrides
QMimeData* OutlineView::mimeData(const QList<QTreeWidgetItem *> items) const
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

QStringList OutlineView::mimeTypes() const
{
    return kMimeTypes;
}

void OutlineView::dropEvent(QDropEvent *event)
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


// slots
void OutlineView::UpdateItemData(const QModelIndex &index)
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
void OutlineView::AddFile(const QTreeWidgetItem *item)
{
    Q_ASSERT(factory_);
    ItemUtility util;
    if (item && util.IsFile(item))
        return;

    const QTreeWidgetItem *par = GetParentOrRoot_(item);
    QTreeWidgetItem *child = CreateChild_(par, GeneralType::ItemType::File);
    child->setText(0, "new file");

    TreeItem *data = factory_->CreateFileItem();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));
}

void OutlineView::AddFolder(const QTreeWidgetItem *item)
{
    Q_ASSERT(factory_);
    ItemUtility util;
    if (item && util.IsFile(item))
        return;

    const QTreeWidgetItem *par = GetParentOrRoot_(item);
    QTreeWidgetItem *child = CreateChild_(par, GeneralType::ItemType::Folder);

    TreeItem *data = factory_->CreateFolderItem();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));
}

void OutlineView::ClearAllItems()
{
    for (int i = 0; i < this->topLevelItemCount(); ++i) {
        QTreeWidgetItem *par = this->topLevelItem(i);
        for (int j = 0; j < par->childCount(); ++j) {
            QTreeWidgetItem *child = par->child(i);
            par->removeChild(child);
            delete child;
        }
        delete par;
    }
    this->clear();
}

void OutlineView::CopyItem()
{
    QTreeWidgetItem *cur = this->currentItem();
    if (cur) {
        tmp_item_ = cur;
        this->SetGTmp(cur);
    }
}

void OutlineView::PasteItem()
{
    if (!tmp_item_)
        return;

    QTreeWidgetItem *citem = this->CloneItem_(tmp_item_);
    QTreeWidgetItem *cur = this->currentItem();
    if (cur) {
        ItemUtility util;
        if (!util.IsValidTreeWidgetItem(cur))
            return;
        TreeItem *data = util.ItemFromTreeWidgetItem(cur);
        if (data->TypeOf() == GeneralType::ItemType::File)
            return;
        cur->addChild(citem);
    } else {
        this->addTopLevelItem(citem);
    }
}

void OutlineView::GlobalPasteItem()
{
    if (!this->GetGTmp())
        return;
    QTreeWidgetItem *citem = this->ConvertItem_(this->GetGTmp(), cat_);
    QTreeWidgetItem *cur = this->currentItem();
    if (cur) {
        ItemUtility util;
        if (!util.IsValidTreeWidgetItem(cur))
            return;
        TreeItem *data = util.ItemFromTreeWidgetItem(cur);
        if (data->TypeOf() == GeneralType::ItemType::File)
            return;
        cur->addChild(citem);
    } else {
        this->addTopLevelItem(citem);
    }
}

Qt::ItemFlags OutlineView::Flags() const
{
    return kItemFlags;
}

void OutlineView::MoveItem(QTreeWidgetItem *item, OutlineView *view)
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

void OutlineView::RemoveItem(QTreeWidgetItem *item)
{
    if (!item)
        return;

    QTreeWidgetItem *par = item->parent();
    if (par)
        par->removeChild(item);

    delete item;
}

void OutlineView::RemoveToTrash(QTreeWidgetItem *item)
{
    OutlineView *trash = OutlineView::GetTrashBox();
    if (trash)
        MoveItem(item, trash);
}

void OutlineView::SetCategory(GeneralType::Category cat)
{
    cat_ = cat;
    factory_ = new ItemFactory(cat);
}

// slots (private)
void OutlineView::ContextMenu(const QPoint &pos)
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

    QAction *actCopyFile = new QAction("Copy", this);
    connect(actCopyFile, &QAction::triggered,
            [=](){
        CopyItem();
    });
    menu.addAction(actCopyFile);

    QAction *actPasteFile = new QAction("Paste", this);
    connect(actPasteFile, &QAction::triggered,
            [=](){
        PasteItem();
    });
    menu.addAction(actPasteFile);

    if (cat_ == GeneralType::Category::Draft
            || cat_ == GeneralType::Category::Plot
            || cat_ == GeneralType::Category::Notes) {

        QAction *actGPasteFile = new QAction("GPaste", this);
        connect(actGPasteFile, &QAction::triggered,
                [=](){
            GlobalPasteItem();
        });
        menu.addAction(actGPasteFile);
    }

    QAction *actDelFile = new QAction("Delete", this);
    connect(actDelFile, &QAction::triggered,
            [=](){
        RemoveToTrash(this->currentItem());
    });
    menu.addAction(actDelFile);

    menu.exec(mapToGlobal(pos));
}

void OutlineView::OnTitleChanged(QTreeWidgetItem *item, int column)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;

    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (column < 0 || column >= data->ColumnCount())
        return;

    data->SetData(ItemKeys::CommonKey::Title, item->text(0));
}

// methods (private)
QTreeWidgetItem* OutlineView::CreateChild_(const QTreeWidgetItem *item, GeneralType::ItemType type)
{
    QTreeWidgetItem *child = new QTreeWidgetItem(const_cast<QTreeWidgetItem*>(item));
    child->setText(0, "NEW");
    child->setFlags(child->flags() | Flags());
    child->setIcon(0, GetItemIcon_(type));
    return child;
}

QTreeWidgetItem* OutlineView::CloneItem_(const QTreeWidgetItem *item)
{
    QTreeWidgetItem *clone_item = item->clone();
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(clone_item);
    TreeItem *c_data = new TreeItem(data);
    clone_item->setData(0, Qt::UserRole, QVariant::fromValue(c_data));
    for (int i = 0; i < clone_item->childCount(); ++i) {
        QTreeWidgetItem *child = this->CloneItem_(clone_item->child(i));
        QTreeWidgetItem *old = clone_item->takeChild(i);
        clone_item->insertChild(i, child);
        delete old;
    }
    return clone_item;
}

QTreeWidgetItem* OutlineView::ConvertItem_(const QTreeWidgetItem *item, GeneralType::Category dst_cat)
{
    QTreeWidgetItem *clone_item = item->clone();
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(clone_item);
    TreeItem *c_data = new TreeItem(data, dst_cat);
    clone_item->setData(0, Qt::UserRole, QVariant::fromValue(c_data));
    for (int i = 0; i < clone_item->childCount(); ++i) {
        QTreeWidgetItem *child = this->ConvertItem_(clone_item->child(i), dst_cat);
        QTreeWidgetItem *old = clone_item->takeChild(i);
        clone_item->insertChild(i, child);
        delete old;
    }
    return clone_item;
}

QIcon OutlineView::GetItemIcon_(GeneralType::ItemType type)
{
    QFileIconProvider provider;
    QIcon icon;
    if (type == GeneralType::ItemType::Folder) {
        icon = provider.icon(QFileIconProvider::Folder);
    } else if (type == GeneralType::ItemType::File) {
        icon = provider.icon(QFileIconProvider::File);
    }
    return icon;
}

const QTreeWidgetItem* OutlineView::GetParentOrRoot_(const QTreeWidgetItem *item) const
{
    return item ? item: this->invisibleRootItem();
}
