#ifndef ITEMUTILITY_H
#define ITEMUTILITY_H

class QTreeWidgetItem;
class TreeItem;

class ItemUtility
{
public:
    explicit ItemUtility();

    TreeItem* ItemFromTreeWidgetItem(const QTreeWidgetItem *item);
};

#endif // ITEMUTILITY_H
