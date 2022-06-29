#ifndef WORLDSMODEL_H
#define WORLDSMODEL_H

#include "basetablemodel.h"

class WorldsModel : public BaseTableModel
{
    Q_OBJECT
public:
    explicit WorldsModel(QObject *parent = nullptr);

protected:
    virtual QVariant DataFromFile(const TreeItem *data, int column) const override;
    virtual bool SetDataOfFile(TreeItem *data, int column, const QVariant &value) override;
};

#endif // WORLDSMODEL_H
