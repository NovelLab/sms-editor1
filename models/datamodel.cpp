#include "datamodel.h"

static const int kDisplayColumns = 2;

DataModel::DataModel(QObject *parent)
    : BaseViewModel{kDisplayColumns, parent}
{

}
