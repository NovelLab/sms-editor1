#ifndef PERSONSMODEL_H
#define PERSONSMODEL_H

#include "basetablemodel.h"

class PersonsModel : public BaseTableModel
{
    Q_OBJECT
public:
    explicit PersonsModel(QObject *parent = nullptr);

protected:
    virtual QVariant DataFromFile(const TreeItem *data, int column) const override;
    virtual bool SetDataOfFile(TreeItem *data, int column, const QVariant &value) override;
};

#endif // PERSONSMODEL_H
