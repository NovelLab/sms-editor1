#ifndef BASEVIEWMODEL_H
#define BASEVIEWMODEL_H

#include <QAbstractItemModel>

class ItemData;

class BaseViewModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit BaseViewModel(int display_columns = 1, QObject *parent = nullptr);
    virtual ~BaseViewModel() override;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void Clear();
    void AppendChild(ItemData *data);

signals:
    void UpdatedItemData(const QModelIndex &index);

protected:
    ItemData* ItemFrom_(const QModelIndex &index) const;

private:
    QVector<ItemData*> items_;
    int kDisplayColumnSize_;
};


#endif // BASEVIEWMODEL_H
