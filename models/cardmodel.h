#ifndef CARDMODEL_H
#define CARDMODEL_H

#include "models/basetablemodel.h"

class TreeItem;

class CardModel : public BaseTableModel
{
    Q_OBJECT
public:
    explicit CardModel(QObject *parent = nullptr);
    ~CardModel();
};

#endif // CARDMODEL_H
