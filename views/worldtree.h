#ifndef WORLDTREE_H
#define WORLDTREE_H

#include "basetreeview.h"

class XmlReader;

class WorldTree : public BaseTreeView
{
    Q_OBJECT
public:
    explicit WorldTree(QWidget *parent = nullptr);

public slots:
    virtual void UpdateItemData(const QModelIndex &index) override;

protected:
    friend XmlReader;
    virtual TreeItem* CreateFileItem_() override;
    virtual QString CreateNewFileTitle() const override;
};

#endif // WORLDTREE_H
