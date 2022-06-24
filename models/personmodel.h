#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include "baseviewmodel.h"

class PersonModel : public BaseViewModel
{
    Q_OBJECT
public:
    explicit PersonModel(QObject *parent = nullptr);
};

#endif // PERSONMODEL_H
