#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QVector>
#include <QUuid>

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

    int ColumnCount() const;

    QUuid UuidOf() const;

private:
    bool IsValidColumn_(int column) const;

    QVector<QVariant> values_;
    ItemType type_;
    Category category_;
    QUuid uuid_;
};

Q_DECLARE_METATYPE(TreeItem*);

#endif // TREEITEM_H
