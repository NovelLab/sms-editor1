#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QVector>

enum class Category;
enum class ItemType;

class TreeItem
{
public:
    explicit TreeItem(ItemType type, Category category);
    ~TreeItem();

    QVariant DataOf(int column) const;
    bool SetData(int column, const QVariant &value);

    ItemType TypeOf() const;
    Category CategoryOf() const;

private:
    bool IsValidColumn_(int column) const;

    QVector<QVariant> values_;
    ItemType type_;
    Category category_;
};

Q_DECLARE_METATYPE(TreeItem*);

#endif // TREEITEM_H
