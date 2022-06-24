#ifndef PLOTMODEL_H
#define PLOTMODEL_H

#include "baseviewmodel.h"

class PlotModel : public BaseViewModel
{
    Q_OBJECT
public:
    explicit PlotModel(QObject *parent = nullptr);
};

#endif // PLOTMODEL_H
