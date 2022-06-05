#include "outlinetree.h"
#include "notepaditem.h"

#include <QFileIconProvider>

#include <QDebug>

OutlineTree::OutlineTree(QWidget *parent)
    : QTreeWidget{parent}
{
    // constructor
}

OutlineTree::~OutlineTree()
{
    // destructor
}

// my methods
void OutlineTree::addNewFolder()
{
    QTreeWidgetItem *cur_item = this->currentItem();
    if (!cur_item)
        return;

    this->addTopLevelItem(createFolderItem(cur_item));
}

void OutlineTree::addNewNotepad()
{
    QTreeWidgetItem *cur_item = this->currentItem();
    if (!cur_item)
        return;

    this->addTopLevelItem(createNotepadItem(cur_item));
}

CategoryType OutlineTree::getCategoryType()
{
    QTreeWidgetItem *cur_item = this->currentItem();
    NotepadItem *note = qvariant_cast<NotepadItem*>(cur_item->data(0, Qt::UserRole));

    const QString title = note->getTitle();
    if (title == "General") {
        return CategoryType::kGeneral;
    } else if (title == "Draft") {
        return CategoryType::kDraft;
    } else {
        return CategoryType::kGeneral;
    }
}

ItemType OutlineTree::getItemType()
{
    QTreeWidgetItem *cur_item = this->currentItem();
    NotepadItem *note = qvariant_cast<NotepadItem*>(cur_item->data(0, Qt::UserRole));

    return note->getType();
}

void OutlineTree::removeItem()
{
    QTreeWidgetItem *cur_item = this->currentItem();
    if (!cur_item)
        return;

    qDebug() << "(unimplement) removeItem";
}

void OutlineTree::setDefaultCategory(const QString &title)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);

    item->setText(0, title);
    item->setIcon(0, getItemIcon(ItemType::kCategory));
    NotepadItem *note = new NotepadItem(title, ItemType::kCategory);
    item->setData(0, Qt::UserRole, QVariant::fromValue(note));

    this->addTopLevelItem(item);
}

// privates
QTreeWidgetItem* OutlineTree::createFolderItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);

    item->setText(0, "NEW");
    item->setIcon(0, getItemIcon(ItemType::kFolder));
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    NotepadItem *note = new NotepadItem("NEW", ItemType::kFolder);
    item->setData(0, Qt::UserRole, QVariant::fromValue(note));

    return item;
}

QTreeWidgetItem* OutlineTree::createNotepadItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);

    item->setText(0, "new text");
    item->setIcon(0, getItemIcon(ItemType::kNotepad));
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    NotepadItem *note = new NotepadItem("new text", ItemType::kNotepad);
    item->setData(0, Qt::UserRole, QVariant::fromValue(note));

    return item;
}

QIcon OutlineTree::getItemIcon(ItemType type)
{
    switch (type) {
      case ItemType::kCategory:
        return QFileIconProvider().icon(QFileIconProvider::Drive);
      case ItemType::kFolder:
        return QFileIconProvider().icon(QFileIconProvider::Folder);
      case ItemType::kNotepad:
        return QFileIconProvider().icon(QFileIconProvider::File);
      default:
        return QFileIconProvider().icon(QFileIconProvider::File);
    }
}
