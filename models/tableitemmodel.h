#ifndef TABLEITEMMODEL_H
#define TABLEITEMMODEL_H

#include <QAbstractItemModel>

class TreeItem;
class ModelDataFactory;

namespace GeneralType {
enum class Category;
}

class TableItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TableItemModel(GeneralType::Category cat, QObject *parent = nullptr);
    ~TableItemModel();

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void Clear();
    void AppendChild(TreeItem *data);

signals:
    void UpdatedItemData(const QModelIndex &index);

protected:
    virtual TreeItem* ItemFromIndex_(const QModelIndex &index) const;

private:
    QVector<TreeItem*> items_;
    ModelDataFactory *factory_;
    GeneralType::Category cat_;
};

#endif // TABLEITEMMODEL_H
