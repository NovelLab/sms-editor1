#ifndef RUBISMODEL_H
#define RUBISMODEL_H

#include "basetablemodel.h"

class RubisModel : public BaseTableModel
{
    Q_OBJECT
public:
    explicit RubisModel(QObject *parent = nullptr);

protected:
    virtual QVariant DataFromFile(const TreeItem *data, int column) const override;
    virtual bool SetDataOfFile(TreeItem *data, int column, const QVariant &value) override;
};

#endif // RUBISMODEL_H
