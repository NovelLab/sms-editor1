#ifndef TRASHTREE_H
#define TRASHTREE_H

#include "basetreeview.h"

class TrashTree : public BaseTreeView
{
    Q_OBJECT
public:
    explicit TrashTree(QWidget *parent = nullptr);
};

#endif // TRASHTREE_H
