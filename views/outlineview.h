#ifndef OUTLINEVIEW_H
#define OUTLINEVIEW_H

#include <QTreeWidget>

class ItemData;

enum class FileType;

class OutlineView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit OutlineView(QWidget *parent = nullptr);
    ~OutlineView();

    void AddRootCategory(const QString &title);
    void AddFolder(QTreeWidgetItem *parent);
    void AddFile(FileType type, QTreeWidgetItem *parent);
    void RemoveItem(QTreeWidgetItem *item);

    QTreeWidgetItem* ToplevelParentFrom(const QTreeWidgetItem *item);
    FileType FileCategoryFrom(const QTreeWidgetItem *item);

public slots:
    void UpdateItemData(const QModelIndex &index);
};

#endif // OUTLINEVIEW_H
