#include "cardmodel.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

static const int kColumnSize = 2;

CardModel::CardModel(QObject *parent)
    : BaseTableModel{kColumnSize, parent}
{

}

CardModel::~CardModel()
{

}
