#ifndef OUTLINEVIEW_H
#define OUTLINEVIEW_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

class TreeItem;
class XmlReader;
class ItemFactory;

namespace GeneralType {
enum class Category;
enum class ItemType;
}

class XmlReader;

static QTreeWidgetItem* g_tmp_;

class OutlineView : public QTreeWidget
{
    Q_OBJECT
public:
    static OutlineView* trash_;
    static OutlineView* GetTrashBox() {return trash_;}
    static void SetTrashBox(OutlineView *trash) {trash_ = trash;}
    static inline QTreeWidgetItem* GetGTmp() {return g_tmp_;}
    static inline void SetGTmp(QTreeWidgetItem *item) {g_tmp_ = item;}

    explicit OutlineView(QWidget *parent = nullptr);
    ~OutlineView();

    void SetCategory(GeneralType::Category cat);

    virtual Qt::ItemFlags Flags() const;

    virtual void AddFolder(const QTreeWidgetItem *item);
    virtual void AddFile(const QTreeWidgetItem *item);
    virtual void RemoveItem(QTreeWidgetItem *item);
    virtual void MoveItem(QTreeWidgetItem *item, OutlineView *view);
    virtual void RemoveToTrash(QTreeWidgetItem *item);

    virtual void CopyItem();
    virtual void PasteItem();

    virtual void GlobalPasteItem();

    virtual void ClearAllItems();

public slots:
    virtual void UpdateItemData(const QModelIndex &index);

protected:
    virtual QTreeWidgetItem* CreateChild_(const QTreeWidgetItem *item, GeneralType::ItemType type);

    virtual const QTreeWidgetItem* GetParentOrRoot_(const QTreeWidgetItem *item) const;

    virtual QMimeData* mimeData(const QList<QTreeWidgetItem *> items) const override;
    virtual QStringList mimeTypes() const override;
    virtual void dropEvent(QDropEvent *event) override;

private slots:
    void OnTitleChanged(QTreeWidgetItem *item, int column);
    void ContextMenu(const QPoint &pos);

private:
    friend XmlReader;
    QIcon GetItemIcon_(GeneralType::ItemType type);
    QTreeWidgetItem* CloneItem_(const QTreeWidgetItem *item);
    QTreeWidgetItem* ConvertItem_(const QTreeWidgetItem *item, GeneralType::Category dst_cat);

    ItemFactory *factory_;
    GeneralType::Category cat_;
    QTreeWidgetItem *tmp_item_ = nullptr;
};

#endif // OUTLINEVIEW_H
