#ifndef BASEMAINVIEW_H
#define BASEMAINVIEW_H

#include <QTableView>

class QTreeWidgetItem;

class BaseMainView : public QTableView
{
    Q_OBJECT
public:
    explicit BaseMainView(QWidget *parent = nullptr);
    virtual ~BaseMainView() override;

    virtual void UpdateView(const QTreeWidgetItem *item) = 0;
};

#endif // BASEMAINVIEW_H
