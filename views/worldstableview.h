#ifndef WORLDSTABLEVIEW_H
#define WORLDSTABLEVIEW_H

#include <QTableView>

class QLabel;
class QTreeWidgetItem;

class WorldsTableView : public QTableView
{
    Q_OBJECT
public:
    explicit WorldsTableView(QWidget *parent = nullptr);

    void SetTitleLabel(QLabel *label);
    void UpdateView(const QTreeWidgetItem *item);

private:
    QLabel *title_label_ = nullptr;
};

#endif // WORLDSTABLEVIEW_H
