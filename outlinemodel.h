#ifndef OUTLINEMODEL_H
#define OUTLINEMODEL_H

#include <QAbstractItemModel>

class OutlineModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit OutlineModel(QObject *parent = nullptr);
    ~OutlineModel() override;
};

#endif // OUTLINEMODEL_H
