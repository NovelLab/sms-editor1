#ifndef ITEMCHECKER_H
#define ITEMCHECKER_H

class QTreeWidgetItem;
class ItemData;
enum class DataType;

class ItemChecker
{
public:
    explicit ItemChecker();

    bool IsCategory(const QTreeWidgetItem *item);
    bool IsFolder(const QTreeWidgetItem *item);
    bool IsFile(const QTreeWidgetItem *item);

    bool IsGenerel(const QTreeWidgetItem *item);
    bool IsTrash(const QTreeWidgetItem *item);

    bool IsValidItem(const QTreeWidgetItem *item);

private:
    ItemData* DataFrom_(const QTreeWidgetItem *item);
    bool IsDataType_(const QTreeWidgetItem *item, DataType type);
};

#endif // ITEMCHECKER_H
