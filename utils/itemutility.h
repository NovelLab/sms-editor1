#ifndef ITEMUTILITY_H
#define ITEMUTILITY_H

class QTreeWidgetItem;
class TreeItem;

class ItemUtility
{
public:
    explicit ItemUtility();

    TreeItem* ItemFromTreeWidgetItem(const QTreeWidgetItem *item);

    bool IsFolder(const QTreeWidgetItem *item) const;
    bool IsFile(const QTreeWidgetItem *item) const;

    bool IsValidTreeWidgetItem(const QTreeWidgetItem *item) const;
};

#endif // ITEMUTILITY_H
