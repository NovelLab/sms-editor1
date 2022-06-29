#ifndef DRAFTTREE_H
#define DRAFTTREE_H

#include "basetreeview.h"

class XmlReader;

class DraftTree : public BaseTreeView
{
    Q_OBJECT
public:
    explicit DraftTree(QWidget *parent = nullptr);
    ~DraftTree() override;

protected:
    friend XmlReader;
    virtual TreeItem* CreateFileItem_() override;
};

#endif // DRAFTTREE_H
