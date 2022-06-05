#ifndef OUTLINETREE_H
#define OUTLINETREE_H

#include <QTreeWidget>

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

private:
    QTreeWidgetItem* createFolderItem(QTreeWidgetItem *parent);
    QTreeWidgetItem* createNotepadItem(QTreeWidgetItem *parent);
};

#endif // OUTLINETREE_H
