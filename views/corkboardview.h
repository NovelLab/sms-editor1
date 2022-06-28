#ifndef CORKBOARDVIEW_H
#define CORKBOARDVIEW_H

#include <QTableView>

class QTreeWidgetItem;

class CorkboardView : public QTableView
{
    Q_OBJECT
public:
    explicit CorkboardView(QWidget *parent = nullptr);
    ~CorkboardView();

    void UpdateView(const QTreeWidgetItem *item);
};

#endif // CORKBOARDVIEW_H
