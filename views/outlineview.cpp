#include "outlineview.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "tools/itemdatawriter.h"

#include <QDebug>


OutlineView::OutlineView(QWidget *parent)
    : QTreeWidget{parent}
{

}

OutlineView::~OutlineView()
{

}

// methods
void OutlineView::AddFile(FileType type, QTreeWidgetItem *parent)
{
    if (!parent)
        return;

    if (type == FileType::None)
        return;

    QTreeWidgetItem *item = new QTreeWidgetItem(parent);

    ItemDataWriter writer;

    ItemData *data = new ItemData(DataType::File, type);
    item->setData(0, Qt::UserRole, QVariant::fromValue(data));
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    switch (type) {
      case FileType::General:
        break;
      case FileType::Draft:
        item->setText(0, "タイトル");
        writer.Write(data, KeyDraft::Title, "タイトル");
        writer.Write(data, KeyDraft::Synopsys, "概要");
        writer.Write(data, KeyDraft::Text, "テキスト");
        writer.Write(data, KeyDraft::Note, "note");
        break;
      case FileType::Plot:
        item->setText(0, "タイトル");
        writer.Write(data, KeyPlot::Title, "タイトル");
        writer.Write(data, KeyPlot::Synopsys, "概要");
        writer.Write(data, KeyPlot::Text, "テキスト");
        writer.Write(data, KeyPlot::Note, "note");
        break;
      case FileType::Person:
        item->setText(0, "名前");
        writer.Write(data, KeyPerson::Name, "名前");
        writer.Write(data, KeyPerson::Info, "紹介");
        writer.Write(data, KeyPerson::Text, "テキスト");
        writer.Write(data, KeyPerson::Note, "note");
        writer.Write(data, KeyPerson::Age, "99");
        writer.Write(data, KeyPerson::Gender, "性別");
        writer.Write(data, KeyPerson::Job, "職業");
        break;
      case FileType::Stage:
        item->setText(0, "名前");
        writer.Write(data, KeyStage::Name, "名前");
        writer.Write(data, KeyStage::Info, "紹介");
        writer.Write(data, KeyStage::Text, "テキスト");
        writer.Write(data, KeyStage::Note, "note");
        break;
      case FileType::Item:
        item->setText(0, "名前");
        writer.Write(data, KeyItem::Name, "名前");
        writer.Write(data, KeyItem::Info, "紹介");
        writer.Write(data, KeyItem::Text, "テキスト");
        writer.Write(data, KeyItem::Note, "note");
        writer.Write(data, KeyItem::Category, "カテゴリ");
        break;
      case FileType::Word:
        item->setText(0, "名前");
        writer.Write(data, KeyWord::Name, "名前");
        writer.Write(data, KeyWord::Info, "紹介");
        writer.Write(data, KeyWord::Text, "テキスト");
        writer.Write(data, KeyWord::Note, "note");
        break;
      case FileType::Research:
        item->setText(0, "タイトル");
        writer.Write(data, KeyResearch::Title, "タイトル");
        writer.Write(data, KeyResearch::Synopsys, "概要");
        writer.Write(data, KeyResearch::Text, "テキスト");
        writer.Write(data, KeyResearch::Note, "note");
        break;
      case FileType::Note:
        item->setText(0, "タイトル");
        writer.Write(data, KeyNote::Title, "タイトル");
        writer.Write(data, KeyNote::Synopsys, "概要");
        writer.Write(data, KeyNote::Text, "テキスト");
        writer.Write(data, KeyNote::Note, "note");
        break;
      default:
        break;
    }
}

void OutlineView::AddFolder(QTreeWidgetItem *parent)
{
    if (!parent)
        return;

    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    item->setText(0, "NEW");

    ItemDataWriter writer;

    ItemData *data = new ItemData(DataType::Folder, FileType::None);
    writer.Write(data, KeyFolder::Title, "NEW");
    item->setData(0, Qt::UserRole, QVariant::fromValue(data));
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void OutlineView::AddRootCategory(const QString &title)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setText(0, title);

    ItemDataWriter writer;

    ItemData *data = new ItemData(DataType::Category, FileType::None);
    writer.Write(data, KeyCategory::Title, title);
    item->setData(0, Qt::UserRole, QVariant::fromValue(data));

    if (title == "General") {
        ItemData *gdata = new ItemData(DataType::File, FileType::General);
        writer.Write(gdata, KeyGeneral::BookTitle, "タイトル");
        writer.Write(gdata, KeyGeneral::BookSubtitle, "サブタイトル");
        writer.Write(gdata, KeyGeneral::BookSeries, "シリーズ");
        writer.Write(gdata, KeyGeneral::BookVolume, "巻");
        writer.Write(gdata, KeyGeneral::BookGenre, "ジャンル");
        writer.Write(gdata, KeyGeneral::BookLicense, "ライセンス");
        writer.Write(gdata, KeyGeneral::AuthorName, "著者名");
        writer.Write(gdata, KeyGeneral::AuthorEmail, "メール");
        item->setData(1, Qt::UserRole, QVariant::fromValue(gdata));
    }

    this->addTopLevelItem(item);
}

FileType OutlineView::FileCategoryFrom(const QTreeWidgetItem *item)
{
    if (!item)
        return FileType::None;

    if (!item->data(0, Qt::UserRole).canConvert<ItemData*>())
        return FileType::None;

    ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
    if (data->TypeOf() != DataType::Category)
        return FileType::None;

    if (item->text(0) == "General") {
        return FileType::General;
    } else if (item->text(0) == "Draft") {
        return FileType::Draft;
    } else if (item->text(0) == "Plot") {
        return FileType::Plot;
    } else if (item->text(0) == "Persons") {
        return FileType::Person;
    } else if (item->text(0) == "Stages") {
        return FileType::Stage;
    } else if (item->text(0) == "Items") {
        return FileType::Item;
    } else if (item->text(0) == "Words") {
        return FileType::Word;
    } else if (item->text(0) == "Research") {
        return FileType::Research;
    } else if (item->text(0) == "Notes") {
        return FileType::Note;
    } else {
        return FileType::None;
    }
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

QTreeWidgetItem* OutlineView::ToplevelParentFrom(const QTreeWidgetItem *item)
{
    if (!item)
        return nullptr;

    QTreeWidgetItem *itm = const_cast<QTreeWidgetItem*>(item);
    while (itm->parent())
        itm = itm->parent();

    return itm;
}

// slots
void OutlineView::UpdateItemData(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QTreeWidgetItem *par = this->currentItem();
    if (!par)
        return;

    // NOTE: currently modified title only.
    if (index.column() < 0 || index.column() > 1)
        return;

    ItemData *data = static_cast<ItemData*>(index.internalPointer());
    par->child(index.row())->setText(index.column(), data->DataOf(index.column()).toString());
}
