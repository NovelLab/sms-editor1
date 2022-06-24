#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include "baseviewmodel.h"

class PersonModel : public BaseViewModel
{
    Q_OBJECT
public:
    explicit PersonModel(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    QVariant DataFolderOf_(ItemData *data, int column) const;
    QVariant DataFileOf_(ItemData *data, int column) const;
    bool SetFolderData_(ItemData *data, int column, const QVariant &value);
    bool SetFileData_(ItemData *data, int column, const QVariant &value);
};

#endif // PERSONMODEL_H
