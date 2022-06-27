#ifndef DRAFTTREE_H
#define DRAFTTREE_H

#include "basetreeview.h"

class DraftTree : public BaseTreeView
{
    Q_OBJECT
public:
    explicit DraftTree(QWidget *parent = nullptr);
    ~DraftTree() override;
};

#endif // DRAFTTREE_H
