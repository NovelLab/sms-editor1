#ifndef PLOTTREE_H
#define PLOTTREE_H

#include "basetreeview.h"

class PlotTree : public BaseTreeView
{
    Q_OBJECT
public:
    explicit PlotTree(QWidget *parent = nullptr);
    ~PlotTree() override;
};

#endif // PLOTTREE_H
