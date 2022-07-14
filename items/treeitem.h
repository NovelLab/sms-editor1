#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QVector>
#include <QUuid>

namespace ItemKeys {
enum class CommonKey;
enum class BookInfo;
enum class Draft;
enum class Plot;
enum class Person;
enum class World;
enum class Research;
enum class Note;
enum class Rubi;
}

namespace GeneralType {
enum class Category;
enum class ItemType;
}

class TreeItem
{
public:
    explicit TreeItem(const TreeItem *item);
    explicit TreeItem(GeneralType::ItemType type, GeneralType::Category category);
    ~TreeItem();

    TreeItem* clone(TreeItem *item);

    QVariant DataOf(int column) const;
    QVariant DataOf(ItemKeys::CommonKey key) const;
    QVariant DataOf(ItemKeys::BookInfo key) const;
    QVariant DataOf(ItemKeys::Draft key) const;
    QVariant DataOf(ItemKeys::Plot key) const;
    QVariant DataOf(ItemKeys::Person key) const;
    QVariant DataOf(ItemKeys::World key) const;
    QVariant DataOf(ItemKeys::Research key) const;
    QVariant DataOf(ItemKeys::Note key) const;
    QVariant DataOf(ItemKeys::Rubi key) const;

    bool SetData(int column, const QVariant &value);
    bool SetData(ItemKeys::CommonKey key, const QVariant &value);
    bool SetData(ItemKeys::BookInfo key, const QVariant &value);
    bool SetData(ItemKeys::Draft key, const QVariant &value);
    bool SetData(ItemKeys::Plot key, const QVariant &value);
    bool SetData(ItemKeys::Person key, const QVariant &value);
    bool SetData(ItemKeys::World key, const QVariant &value);
    bool SetData(ItemKeys::Research key, const QVariant &value);
    bool SetData(ItemKeys::Note key, const QVariant &value);
    bool SetData(ItemKeys::Rubi key, const QVariant &value);

    GeneralType::ItemType TypeOf() const;
    GeneralType::Category CategoryOf() const;

    int ColumnCount() const;

    QUuid UuidOf() const;

private:
    bool IsValidColumn_(int column) const;

    QVector<QVariant> values_;
    GeneralType::ItemType type_;
    GeneralType::Category category_;
    QUuid uuid_;
};

Q_DECLARE_METATYPE(TreeItem*);

#endif // TREEITEM_H
