#ifndef PERSONVIEW_H
#define PERSONVIEW_H

#include "basemainview.h"

class PersonView : public BaseMainView
{
    Q_OBJECT
public:
    explicit PersonView(QWidget *parent = nullptr);
    virtual ~PersonView() override;

    virtual void UpdateView(const QTreeWidgetItem *item) override;
};

#endif // PERSONVIEW_H
