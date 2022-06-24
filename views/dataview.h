#ifndef DATAVIEW_H
#define DATAVIEW_H

#include "basemainview.h"

class DataView : public BaseMainView
{
    Q_OBJECT
public:
    explicit DataView(QWidget *parent);
    virtual ~DataView() override;

    virtual void UpdateView(const QTreeWidgetItem *item) override;
};

#endif // DATAVIEW_H
