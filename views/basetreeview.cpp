#include "basetreeview.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"

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
}

BaseTreeView::~BaseTreeView()
{

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
QTreeWidgetItem* BaseTreeView::CreateChild_(const QTreeWidgetItem *item)
{
    QTreeWidgetItem *child = new QTreeWidgetItem(const_cast<QTreeWidgetItem*>(item));
    child->setText(0, "NEW");
    child->setFlags(Flags());
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
