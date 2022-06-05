#include "outlinetree.h"

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

void OutlineTree::removeItem()
{
    QTreeWidgetItem *cur_item = this->currentItem();
    if (!cur_item)
        return;

    qDebug() << "(unimplement) removeItem";
}

void OutlineTree::setDefaultFolder(const QString &title)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);

    item->setText(0, title);
    item->setIcon(0, getItemIcon(ItemType::kFolder));

    this->addTopLevelItem(item);
}

// privates
QTreeWidgetItem* OutlineTree::createFolderItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);

    item->setText(0, "NEW");
    item->setIcon(0, getItemIcon(ItemType::kFolder));
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    return item;
}

QTreeWidgetItem* OutlineTree::createNotepadItem(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);

    item->setText(0, "new text");
    item->setIcon(0, getItemIcon(ItemType::kNotepad));
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    return item;
}

QIcon OutlineTree::getItemIcon(ItemType type)
{
    switch (type) {
      case ItemType::kFolder:
        return QFileIconProvider().icon(QFileIconProvider::Folder);
      case ItemType::kNotepad:
        return QFileIconProvider().icon(QFileIconProvider::File);
      default:
        return QFileIconProvider().icon(QFileIconProvider::File);
    }
}
