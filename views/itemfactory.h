#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

namespace GeneralType {
enum class Category;
}

class TreeItem;

class ItemFactory
{
public:
    ItemFactory(GeneralType::Category cat);

    TreeItem* CreateFileItem();
    TreeItem* CreateFolderItem();

private:
    TreeItem* CreateBookInfo_();
    TreeItem* CreateDraft_();
    TreeItem* CreatePlot_();
    TreeItem* CreatePerson_();
    TreeItem* CreateWorld_();
    TreeItem* CreateResearch_();
    TreeItem* CreateNote_();
    TreeItem* CreateRubi_();

    GeneralType::Category cat_;
};

#endif // ITEMFACTORY_H
