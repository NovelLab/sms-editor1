#ifndef OUTLINEVIEW_H
#define OUTLINEVIEW_H

#include <QTreeWidget>

class QTreeWidgetItem;
class TreeItem;
class XmlReader;
class ItemFactory;

namespace GeneralType {
enum class Category;
}

class OutlineView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit OutlineView(GeneralType::Category category,
                         QWidget *parent = nullptr);
    ~OutlineView();

    virtual Qt::ItemFlags Flags() const;

    virtual void AddFolder(const QTreeWidgetItem *item);
    virtual void AddFile(const QTreeWidgetItem *item);
    virtual void RemoveItem(QTreeWidgetItem *item);
    virtual void MoveItem(QTreeWidgetItem *item, OutlineView *view);

public slots:
    virtual void UpdateItemData(const QModelIndex &index);

protected:
    virtual QTreeWidgetItem* CreateChild_(const QTreeWidgetItem *item);

    virtual const QTreeWidgetItem* GetParentOrRoot_(const QTreeWidgetItem *item) const;

    virtual QMimeData* mimeData(const QList<QTreeWidgetItem *> items) const override;
    virtual QStringList mimeTypes() const override;
    virtual void dropEvent(QDropEvent *event) override;

private slots:
    void OnTitleChanged(QTreeWidgetItem *item, int column);
    void ContextMenu(const QPoint &pos);

private:
    friend XmlReader;

    ItemFactory *factory_;
    GeneralType::Category cat_;
};

#endif // OUTLINEVIEW_H
