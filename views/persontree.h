#ifndef PERSONTREE_H
#define PERSONTREE_H

#include "basetreeview.h"

class XmlReader;

class PersonTree : public BaseTreeView
{
    Q_OBJECT
public:
    explicit PersonTree(QWidget *parent = nullptr);

public slots:
    virtual void UpdateItemData(const QModelIndex &index) override;

protected:
    friend XmlReader;
    virtual TreeItem* CreateFileItem_() override;
    virtual QString CreateNewFileTitle() const override;
};

#endif // PERSONTREE_H
