#ifndef PERSONSTABLEVIEW_H
#define PERSONSTABLEVIEW_H

#include <QTableView>

class QLabel;
class QTreeWidgetItem;

class PersonsTableView : public QTableView
{
    Q_OBJECT
public:
    explicit PersonsTableView(QWidget *parent = nullptr);

    void SetTitleLabel(QLabel *label);
    void UpdateView(const QTreeWidgetItem *item);

private:
    QLabel *title_label_ = nullptr;
};

#endif // PERSONSTABLEVIEW_H
