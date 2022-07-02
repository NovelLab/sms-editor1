#include "cardmodel.h"

static const int kColumnSize = 2;

CardModel::CardModel(QObject *parent)
    : BaseTableModel{kColumnSize, parent}
{

}
