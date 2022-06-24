#ifndef DATAMODEL_H
#define DATAMODEL_H

#include "baseviewmodel.h"

class DataModel : public BaseViewModel
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);
};

#endif // DATAMODEL_H
