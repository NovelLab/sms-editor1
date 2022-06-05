#ifndef OUTLINETREE_H
#define OUTLINETREE_H

#include <QTreeWidget>

enum class ItemType {
    kCategory,
    kFolder,
    kNotepad,
};

enum class CategoryType {
    kGeneral,
    kDraft,
};

class OutlineTree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit OutlineTree(QWidget *parent = nullptr);
    ~OutlineTree() override;

    // my methods
    void addNewFolder();
    void addNewNotepad();
    void removeItem();
    void setDefaultCategory(const QString &title);
    ItemType getItemType();
    CategoryType getCategoryType();

private:
    QTreeWidgetItem* createFolderItem(QTreeWidgetItem *parent);
    QTreeWidgetItem* createNotepadItem(QTreeWidgetItem *parent);
    QIcon getItemIcon(ItemType type);
};

#endif // OUTLINETREE_H
