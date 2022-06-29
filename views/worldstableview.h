#ifndef WORLDSTABLEVIEW_H
#define WORLDSTABLEVIEW_H

#include <QTableView>

class QTreeWidgetItem;

class WorldsTableView : public QTableView
{
    Q_OBJECT
public:
    explicit WorldsTableView(QWidget *parent = nullptr);

    void UpdateView(const QTreeWidgetItem *item);
};

#endif // WORLDSTABLEVIEW_H
