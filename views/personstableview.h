#ifndef PERSONSTABLEVIEW_H
#define PERSONSTABLEVIEW_H

#include <QTableView>

class QTreeWidgetItem;

class PersonsTableView : public QTableView
{
    Q_OBJECT
public:
    explicit PersonsTableView(QWidget *parent = nullptr);

    void UpdateView(const QTreeWidgetItem *item);
};

#endif // PERSONSTABLEVIEW_H
