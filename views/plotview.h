#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include "basemainview.h"

class PlotModel;

class PlotView : public BaseMainView
{
    Q_OBJECT
public:
    explicit PlotView(QWidget *parent = nullptr);
    virtual ~PlotView() override;

    virtual void UpdateView(const QTreeWidgetItem *item) override;
};

#endif // PLOTVIEW_H
