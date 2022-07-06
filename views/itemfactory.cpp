#include "itemfactory.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"

ItemFactory::ItemFactory(GeneralType::Category cat)
    : cat_{cat}
{

}

// methods
TreeItem* ItemFactory::CreateFileItem()
{
    switch (cat_) {
      case GeneralType::Category::BookInfo:
        return CreateBookInfo_();
      case GeneralType::Category::Draft:
        return CreateDraft_();
      case GeneralType::Category::Plot:
        return CreatePlot_();
      case GeneralType::Category::Persons:
        return CreatePerson_();
      case GeneralType::Category::Worlds:
        return CreateWorld_();
      case GeneralType::Category::Research:
        return CreateResearch_();
      case GeneralType::Category::Notes:
        return CreateNote_();
      case GeneralType::Category::Rubi:
        return CreateRubi_();
      case GeneralType::Category::Trash:
        return CreateTrash_();
      default:
        break;
    }
    return nullptr;
}

TreeItem* ItemFactory::CreateFolderItem()
{
    return new TreeItem(GeneralType::ItemType::Folder, cat_);
}

// methods (private)
TreeItem* ItemFactory::CreateBookInfo_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::BookInfo);
    for (int i = 0; i < ItemDefVals::kBookInfo.count(); ++i) {
        item->SetData(i, ItemDefVals::kBookInfo.at(i));
    }
    return item;
}

TreeItem* ItemFactory::CreateDraft_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::Draft);
    for (int i = 0; i < ItemDefVals::kDraft.count(); ++i) {
        item->SetData(i, ItemDefVals::kDraft.at(i));
    }
    return item;
}

TreeItem* ItemFactory::CreatePlot_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::Plot);
    for (int i = 0; i < ItemDefVals::kPlot.count(); ++i) {
        item->SetData(i, ItemDefVals::kPlot.at(i));
    }
    return item;
}

TreeItem* ItemFactory::CreatePerson_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::Persons);
    for (int i = 0; i < ItemDefVals::kPerson.count(); ++i) {
        item->SetData(i, ItemDefVals::kPerson.at(i));
    }
    return item;
}

TreeItem* ItemFactory::CreateWorld_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::Worlds);
    for (int i = 0; i < ItemDefVals::kWorld.count(); ++i) {
        item->SetData(i, ItemDefVals::kWorld.at(i));
    }
    return item;
}

TreeItem* ItemFactory::CreateResearch_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::Research);
    for (int i = 0; i < ItemDefVals::kResearch.count(); ++i) {
        item->SetData(i, ItemDefVals::kResearch.at(i));
    }
    return item;
}

TreeItem* ItemFactory::CreateNote_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::Notes);
    for (int i = 0; i < ItemDefVals::kNote.count(); ++i) {
        item->SetData(i, ItemDefVals::kNote.at(i));
    }
    return item;
}

TreeItem* ItemFactory::CreateRubi_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::Rubi);
    for (int i = 0; i < ItemDefVals::kRubi.count(); ++i) {
        item->SetData(i, ItemDefVals::kRubi.at(i));
    }
    return item;
}

TreeItem* ItemFactory::CreateTrash_()
{
    TreeItem *item = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::Trash);
    return item;
}
