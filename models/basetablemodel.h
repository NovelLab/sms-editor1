#ifndef BASETABLEMODEL_H
#define BASETABLEMODEL_H

#include <QAbstractItemModel>

class TreeItem;

class BaseTableModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit BaseTableModel(int display_columns, QObject *parent = nullptr);
    ~BaseTableModel();

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void Clear();
    void AppendChild(TreeItem *data);

signals:
    void UpdatedItemData(const QModelIndex &index);

protected:
    virtual TreeItem* ItemFromIndex_(const QModelIndex &index) const;
    virtual QVariant DataFromFile(const TreeItem *data, int column) const;
    virtual QVariant DataFromFolder(const TreeItem *data, int column) const;
    virtual bool SetDataOfFile(TreeItem *data, int column, const QVariant &value);
    virtual bool SetDataOfFolder(TreeItem *data, int column, const QVariant &value);

private:
    QVector<TreeItem*> items_;
    const int kDisplayColumnSize_;
};

#endif // BASETABLEMODEL_H
