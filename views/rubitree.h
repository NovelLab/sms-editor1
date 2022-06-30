#ifndef RUBITREE_H
#define RUBITREE_H

#include "basetreeview.h"

class XmlReader;

class RubiTree : public BaseTreeView
{
    Q_OBJECT
public:
    explicit RubiTree(QWidget *parent = nullptr);

public slots:
    virtual void UpdateItemData(const QModelIndex &index) override;

protected:
    friend XmlReader;
    virtual TreeItem* CreateFileItem_() override;
    virtual QString CreateNewFileTitle() const override;
};

#endif // RUBITREE_H
