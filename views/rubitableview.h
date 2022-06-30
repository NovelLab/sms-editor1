#ifndef RUBITABLEVIEW_H
#define RUBITABLEVIEW_H

#include <QTableView>

class QTreeWidgetItem;

class RubiTableView : public QTableView
{
    Q_OBJECT
public:
    explicit RubiTableView(QWidget *parent = nullptr);

    void UpdateView(const QTreeWidgetItem *item);
};

#endif // RUBITABLEVIEW_H
