#ifndef BASETREEVIEW_H
#define BASETREEVIEW_H

#include <QTreeWidget>

class QTreeWidgetItem;
class TreeItem;

enum class Category;

class BaseTreeView : public QTreeWidget
{
    Q_OBJECT
public:
    BaseTreeView(Category category, QWidget *parent = nullptr);
    virtual ~BaseTreeView() override;

    virtual Qt::ItemFlags Flags() const;

    virtual void AddFolder(const QTreeWidgetItem *item);
    virtual void AddFile(const QTreeWidgetItem *item);
    virtual void RemoveItem(QTreeWidgetItem *item);

protected:
    virtual QTreeWidgetItem* CreateChild_(const QTreeWidgetItem *item);
    virtual TreeItem* CreateFolderItem_();
    virtual TreeItem* CreateFileItem_();

    virtual const QTreeWidgetItem* GetParentOrRoot_(const QTreeWidgetItem *item) const;

    virtual QMimeData* mimeData(const QList<QTreeWidgetItem *> items) const override;
    virtual QStringList mimeTypes() const override;
    virtual void dropEvent(QDropEvent *event) override;

private:
    Category base_category_;
};

#endif // BASETREEVIEW_H
