#include "drafttree.h"

#include "enums/generaltypes.h"

DraftTree::DraftTree(QWidget *parent)
    : BaseTreeView{Category::Draft, parent}
{

}

DraftTree::~DraftTree()
{

}

// overrides
