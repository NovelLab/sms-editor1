#include "plotmodel.h"

static const int kDisplayColumns = 2;

PlotModel::PlotModel(QObject *parent)
    : BaseViewModel{kDisplayColumns, parent}
{

}
